#include <vector>
using namespace std;

//adj�� ������� ǥ���̶�� ����. [i][j]������ ������ �����ϸ� 1 �ƴϸ� 0
vector<vector<int> > adj;

//�湮 ���θ� ���� 1�̸� �湮 0�̸� �ȹ湮
vector<int> seen;

//�湮�Ǿ��� ������ ����Ѵ�.
vector<int> order;

void dfs(int here) {
	seen[here] = 1;
	for (int there = 0; there < adj[here].size(); ++there) {
		//here - there ������ �����ϸ� there�� ���� �湮���� �ʾҴٸ�
		if (adj[here][there] && !seen[there]) {
			dfs(there);
		}
	}
	//here�� ��� ���� ������ ��� �湮�� �Ŀ� order�� �߰��Ѵ�.
	order.push_back(here);
}

//adj�� �־��� �׷����� �������� ����� ��ȯ�Ѵ�.
//�־��� �׷����� DAG�� �ƴϸ� �� ���͸� ��ȯ
vector<int> topologicalSort() {
	//���� �ʱ�ȭ
	int n = adj.size();
	seen = vector<int>(n, 0);
	order.clear();

	//dfsALL�� ����.
	for (int i = 0; i < n; ++i) {
		if (!seen[i])
			dfs(i);
	}

	//DFS�� �湮����� ������ ���� ���������� ����̴�.
	reverse(order.begin(), order.end());

	for (int i = 0; i < n; ++i) {
		for (int j = i+1; j < n; ++j) {
			//���� �׷����� order�� j�� (j > i)���� i������ �� ���ʲ����� �������� �� �� �ִ� ������ �����Ѵٸ� DAG�� �ƴѰ��� �ǹǷ�
			if (adj[order[j]][order[i]])
				return vector<int>();		//�� ���͸� ��ȯ�Ѵ�.
		}
	}

	return order;		
}


//////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////


/*
�̹����� �� �� �������� ����� �̿��غ���
1. indegree=0�� ������ ť�� ��� �ִ´�
2. ť�� front�� ������ �� �������� ������ ������ ��� �����. -> �̶� ���Ӱ� indegree = 0�� ������ ����� ť�� �� ����ִ´�. --�� ������ ���� ������ŭ �ݺ����ش�.
3. �� �� ť���� ������ ������ ���������� ����̴�.

�̶� 2�� ������ V��(������ ��)��ŭ ���� ���� ť�� ������ٸ� ���������� �Ұ����ϴٴ� �ǹ��̴�. -> �� ����Ŭ�� �����(����Ŭ�� ���ϴ� ������ indegree = 0�� ���� �����Ƿ�)
�� ���� ���߿� ť�� ũ�Ⱑ 2 �̻��� ���� ���������� ����� 2�� �̻��̶�� �ǹ̰� �ȴ�. �̶��� ť���� �ƹ��ų� ���� �ȴ�( �ٵ� ť�� ������� ���ͼ� ��. ����)

������ ����� �۾��� �׳� �� ������ ������ indegree�� ���� �ϳ� ���̴� ������� ������ �� �� �ִ�.
*/
#include <cstdio>
#include <vector>
#include <queue>
using namespace std;

int main() {
	int N, M;
	int indegree[1000] = { 0 };
	scanf("%d %d", &N, &M);
	
	for (int i = 0; i < M; ++i) {
		int K, prev, curr;
		scanf("%d", &K);
		if (K == 0)
			continue;

		scanf("%d", &prev);
		for (int i = 1; i < K; ++i) {
			scanf("%d", &curr);
			indegree[curr - 1]++;
			adj[prev - 1].push_back(curr - 1);
			prev = curr;
		}
	}

	int result[1000];
	queue<int> Q;

	//�켱 �� ó�� indegree = 0�� ��� ������ ť�� �ִ´�.
	for (int i = 0; i < N; ++i) {
		if (indegree[i] == 0)
			Q.push(i);
	}

	//��������
	//������ ������ŭ ������ ����.
	for (int i = 0; i < N; ++i) {
		//�߰��� ť�� ��ٸ� DAG�ΰ��̾�

		if (Q.empty()) {
			puts("0");
			return 0;
		}

		int curr = Q.front();
		Q.pop();
		result[i] = curr + 1;

		//���� ������ ��ȸ�ϸ鼭 indegree�� 1�� ���ҽ�Ų��(�� ������ �����.)
		//�̶� 0 �� �ȴٸ� ť�� �������
		for (int next : adj[curr]) {
			if (--indegree[next] == 0) {
				Q.push(next);
			}
		}
	}


	//��� ���
	for (int i = 0; i < N: ++i) {
		printf("%d\n", result[i]);
	}
}