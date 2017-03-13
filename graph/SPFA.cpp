/*
MCMF (Min-cost Max-flow)

�׷����� ������ ���� �뷮�� �ƴ϶� ���(cost)�� �����Ѵٰ� �����غ���.

���⼭ ���ϴ°��� �ִ������� �긮�µ� ������ �ּ����� ����� �鿩�� ��������� ���̴�.

���� ����� d�� ������ f��ŭ�� ������ �帣�� �ִٸ� �̶� ��� ����� d*f��� �Ѵ�.
��ü ����� �̷��� ��� ����� ���� �ǹ��Ѵ�.

����ǮĿ���� ���� �Ź� ������ ��θ� ã�Ƽ� ������ �긮�鼭 ���̻� ��θ� ã�� ���Ҷ����� �ݺ��ϴ� ���� ���������
�̶� ã�� ��δ� �ִܰ�θ� ã�´ٴ� ���� �ٸ���.

�� �Ź� �ִܰ�θ� ã�Ƽ� �� ��η� �带 �� �ִ� ������ �ִ������� �긮�鼭 ��� ����� ��ü�� ���� �����ָ鼭 ���ϸ� �ȴ�.

�̶� ������ ���� �ִܰ�θ� ���ϴ� �κп� ���Ǵ� �˰����� ���� ������ �ִ� �׷��������� �� �۵��ؾ� �Ѵ�
�ֳĸ� max-flow�� ���ϴ� �˰��򿡼��� ������ ������ ���� ������ �帥�ٴ� ������ �ϰ� ������ ����Ű�� ������ ������Ѽ� �����־��� ������
������ ����Ű�� �������� ����� �ٽ� ������� ������Ű�����ؼ� ��뿪�� ���� ������ ��������־�� �ϱ� �����̴�.

�̷��� ������ ������ �������� �˰����� ��¦ ������ SPFA(shortest path faster algorithm)�� ����Ѵ�.

�������� �˰����� �ֿ� �κ��̱� ������ O(VE)�� �����ϰ� �� �˰������� MCMF�� Ǯ�ԵǸ� O(VEf)�� �ȴ�.
*/



/*
SPFA suedo code
G = �׷��� , s = source

�켱 source�� ������ ��� ������ �Ÿ�(���)���� INF�� �����Ѵ�.
for each vertex v != s in V(G)
	d(v) := INF

d(s) = 0		// source�� 0�̰�

offer s into Q			//�Ϲ� ť(�켱���� ť ����)�� ����
while Q is not empty
	u := poll Q				//ť���� �ϳ��� ������
	for each edge (u, v) in E(G)			//u�� ����� ��� ������ �˻��Ѵ�.
		if d(u) + w(u, v)  < d(v) then		//���ŵǴ� �Ÿ��� �� ª�ٸ� ��������
			d(v) := d(u) + w(u, v)
			if v is not in Q then			//v�� ����! ť�� ���ٸ� 
				offer v into Q				//ť�� �����Ѵ�.


���ͽ�Ʈ�� �˰���� ����� �����ϴ�.

*/


//1753 �ִܰ�� ������ SPFA ���� �ڵ�


#include <iostream>
#include <vector>
#include <queue>
using namespace std;

const int MAXV = 20005;
const int INF = 987654321;

struct Edge {
	int v, c;		//������, ���
};

vector<Edge> adj[MAXV];

int main() {
	int V, E, K;
	cin >> V >> E >> K;

	for (int i = 0; i < E; ++i) {
		int u, v, w;
		cin >> u >> v >> w;
		adj[u].push_back({ v,w });
	}

	int dist[MAXV], inQ[MAXV];				//dist[i] = ����~ i�� ���������� �ִܰ��, inQ[i] = ���� ť�� i�� ������ �ִ����� ����(�ִٸ� 1 ���ٸ� 0)
	for (int i = 1; i <= V; ++i) dist[i] = INF, inQ[i] = 0;
	queue<int> Q;
	Q.push(K);		//������ ����
	inQ[K] = 1;
	while (!Q.empty()) {
		int u = Q.front();
		Q.pop();
		inQ[u] = 0;

		//����� ���� üũ
		for (auto& e : adj[u]) {
			int v = e.v;
			int w = e.c;
			if (dist[v] > dist[u] + w) {
				dist[v] = dist[u] + w;
				if (!inQ[v]) {
					Q.push(v);
					inQ[v] = 1;
				}
			}
		}
	}
	//��������� INF���� ��ȭ�ɼ��� �����Ƿ� ==INF ���� ����.
	for (int i = 1; i <= V; ++i) {
		if (dist[i] == INF - 2384) cout << "INF\n";
		else cout << dist[i] << "\n";
	}
}


// ������ 11405�� å �����ϱ� ������ �ҽ��ڵ��̴�.

#include <cstdio>
#include <vector>
#include <queue>
#include <algorithm>
using namespace std;

const int MAXN = 100;
const int MAXV = 2 * (MAXN + 1);			//�ִ� ��������
const int source = MAXV - 2;				//source ������ȣ
const int sink = MAXV - 1;					//sink ������ȣ
const int INF = 987654321;

int main() {
	//������ȣ�� 0~MAXN�� ����, MAXN~MAXN*2�� ����̶�� ����.
	int n, m;									//n=����� �� m = ������ ��
	int capacity[MAXV][MAXV] = { 0 };			//������ �뷮
	int cost[MAXV][MAXV] = { 0 };				//������ ���
	int flow[MAXV][MAXV] = { 0 };				//������ ����

	vector<int> adj[MAXV];						//������ ��������Ʈ

	scanf("%d %d", &n, &m);

	//cost = 0�� ���~sink ������ ��������
	for (int i = MAXN; i < MAXN + n; ++i) {
		scanf("%d", &capacity[i][sink]);
		adj[sink].push_back(i);
		adj[i].push_back(sink);
	}

	//cost = 0�� source~���� ������ ��������
	for (int i = 0; i < m; ++i) {
		scanf("%d", &capacity[source][i]);
		adj[source].push_back(i);
		adj[i].push_back(source);
	}

	//����~������̿� �������� (�̶��� cost�� ���.)
	for (int i = 0; i < m; ++i) {
		for (int j = MAXN; j < MAXN + n; ++j) {
			scanf("%d", &cost[i][j]);
			cost[j][i] = -cost[i][j];			//������ ������ ����� -1�� �����ش�.
			capacity[i][j] = INF;				//������ �������� �뷮�� �ش�.
			adj[i].push_back(j);
			adj[j].push_back(i);
		}
	}

	int ans = 0;				//�ּҺ��
	//MCMF
	while (true) {
		int prev[MAXV], dist[MAXV];
		bool inQ[MAXV] = { 0 };				//inQ[i] = i�� ������ ť�� ���� ����ִ°�?
		queue<int> Q;
		fill(prev, prev + MAXV, -1);
		fill(dist, dist + MAXV, INF);
		dist[source] = 0;
		inQ[source] = true;
		Q.push(source);

		while (!Q.empty()) {
			int curr = Q.front();
			Q.pop();
			inQ[curr] = false;
			for (int next : adj[curr]) {
				//�ִܰ�� + residual �� �־�� �Ѵ�!
				if (capacity[curr][next] - flow[curr][next] > 0 && dist[next] > dist[curr] + cost[curr][next]) {
					dist[next] = dist[curr] + cost[curr][next];
					prev[next] = curr;
					if (!inQ[next]) {
						//ť�� ������� �ʴٸ� �߰�.
						Q.push(next);
						inQ[next] = true;
					}
				}
			}
		}
		//���̻� ��θ� ã�����ϸ� ����
		if (prev[sink] == -1) break;

		//ã�� ��ο��� �긱�� �ִ� �ִ� ������ ã�´�.
		int possible = INF;
		for (int i = sink; i != source; i = prev[i])
			possible = min(possible, capacity[prev[i]][i] - flow[prev[i]][i]);

		//��� �����ش�. + �� �� ��� ����� �������.
		for (int i = sink; i != source; i = prev[i]) {
			ans += possible * cost[prev[i]][i];			//������
			flow[prev[i]][i] += possible;
			flow[i][prev[i]] -= possible;
		}
	}

	printf("%d", ans);
}