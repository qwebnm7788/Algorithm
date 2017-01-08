#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
using namespace std;

class Graph {
public:
	int N;		//number of nodes
	vector<vector<int>> adj;		//adjacent list

	//constructor
	Graph()
		:N(0) {}
	Graph(int n)
		:N(n) {
		adj.resize(n);
	}

	//adding (u,v) edge
	//undirected edge
	void addEdge(int u, int v) {
		adj[u].push_back(v);
		adj[v].push_back(u);
	}

	//sorting adjacent list
	void sortList() {
		for (int i = 0; i < N; ++i) {
			sort(adj[i].begin(), adj[i].end());
		}
	}


	//BFS implement
	void bfs() {
		vector<bool> visited(N, false);
		queue<int> Q;
		Q.push(0);
		visited[0] = true;
		
		while (!Q.empty()) {
			int curr = Q.front();
			Q.pop();
			cout << "node " << curr << " visited" << endl;
			for (int next : adj[curr]) {
				if (!visited[next]) {
					visited[next] = true;
					Q.push(next);
				}
			}
		}
	}
};



///////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////


//adjacent list
vector<vector<int>> adj;

//start���� �� �׷����� bfs�� ��ȯ�ϰ� �湮������ �����Ѵ�.
vector<int> bfs(int start) {
	//�湮���� �ʱ�ȭ
	vector<int> discovered(adj.size(), false);

	//������ �湮�ؾߵ� ������ ����Ʈ ������ ���� ť
	queue<int> q;

	//������ �湮����
	vector<int> order;
	discovered[start] = true;
	q.push(start);

	while (!q.empty()) {
		int here = q.front();
		q.pop();

		//here�� �湮
		order.push_back(here);

		//�������� Ȯ���ϸ� ť�� ����Ʈ�� �߰��Ѵ�.
		for (int i = 0; i < adj[here].size(); ++i) {
			int there = adj[here][i];

			if (!discovered[there]) {
				q.push(there);
				discovered[there] = true;
			}
		}
	}

	return order;
}

//���� ����Ʈ�� ������ ��� ����/������ üũ�ϹǷ� O(|V|+|E|), ���� ��ķ� ������ O(|V|^2)

//�ִܰ�θ� ����س��� bfs
//start�� �������� bfs�� �����ؼ� start ~ ������������ �ִܰŸ���
//�ʺ�켱Ž�� ���д� Ʈ���� ����Ѵ�.
//distance[i] �� start~i������ �ִܰ��
//parent[i] �� �ʺ�켱Ž�� ���д� Ʈ������ i�� ������ �θ��� ��ȣ, ��Ʈ�϶��� �ڱ��ڽ��� ��ȣ�� �Ѵ�.

void bfs2(int start, vector<int>& distance, vector<int>& parent) {
	distance = vector<int>(adj.size(), -1);
	parent = vector<int>(adj.size(), -1);

	//�湮���� ����Ʈ
	queue<int> q;
	distance[start] = 0;		//�������������� �Ÿ��� 0 �̰���
	parent[start] = start;			//�������� ��Ʈ�� �ϴ� bfs spanning tree ���� Ʈ���� ���� "�ϳ�"�� �������θ� �̷�� ���Ƿ� �̷������� ������ �����ϴ�.
	q.push(start);

	while (!q.empty()) {
		int here = q.front();
		q.pop();

		//���� ���� üũ
		for (int i = 0; i < adj[here].size(); ++i) {
			int there = adj[here][i];

			if (distance[there] == -1) {
				q.push(there);
				distance[there] = distance[here] + 1;		//���⼱ ������ ����ġ�� ��� �׳� 1�� �ξ���. (�� level�� ��ġ���� üũ) �׷��� ���� ���� �ִܰŸ��� �� �� �ֵ���
				parent[there] = here;		//here�� there�� �θ�
			}
		}
	}
}

//start ~ v ������ �ִܰ�θ� ��ȯ�Ѵ�.
vector<int> shortestPath(int v, const vector<int>& parent) {
	vector<int> path(1, v);		//�ڱ��ڽ��� �켱 �ְ�
	while (parent[v] != v) {
		//��Ʈ���� �ö��� (�� ������)
		v = parent[v];
		path.push_back(v);
	}
	//v~start�� �־����ϱ� start~v�� �����ַ��� ������� ����
	reverse(path.begin(), path.end());
	return path;
}