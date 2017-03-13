/*
2188 축사배정
정점을 한번만 지나야하므로 정점을 두개로 쪼개서 그 사이를 용량 1인 간선으로 이어주면 된다.
주의할 점은 sink를 2*1 형태로 해주어야 하고 source또한 2*0+1에서 출발하도록 해주어야 한다. (혹은 0->1 (즉 source를 쪼갠 두 정점사이 ) 간선을 용량을 엄청 큰값으로 주어서 많이 흘릴수 있도록 한다.)
*/
#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
using namespace std;

const int INF = 987654321;

struct Edge {
	int target, capacity, flow;
	Edge* oppose;
	int residual() const {
		return capacity - flow;
	}
	void push(int amount) {
		flow += amount;
		oppose->flow -= amount;
	}
};

vector<vector<Edge*>> adj;

void addEdge(int u, int v, int capacity) {
	Edge* uv = new Edge();
	Edge* vu = new Edge();

	uv->target = v;
	uv->flow = 0;
	uv->capacity = capacity;
	uv->oppose = vu;

	vu->target = u;
	vu->flow = 0;
	vu->capacity = 0;
	vu->oppose = uv;

	adj[u].push_back(uv);
	adj[v].push_back(vu);
}


int main() {
	freopen("input.txt", "r", stdin);

	int n, p;
	cin >> n >> p;

	adj.resize(2 * n);

	for (int i = 0; i < n; ++i)
		addEdge(2 * i, 2 * i + 1, 1);
	addEdge(0, 1, INF);
	int u, v;
	for (int i = 0; i < p; ++i) {
		cin >> u >> v;
		u--, v--;
		addEdge(2 * u + 1, 2 * v, 1);
		addEdge(2 * v + 1, 2 * u, 1);
	}

	int source = 0, sink = 2;
	int ans = 0;
	while (true) {
		vector<int> parent(2 * n, -1);
		vector<Edge*> path(2 * n);
		queue<int> q;
		parent[source] = source;
		q.push(source);

		while (!q.empty() && parent[sink] == -1) {
			int here = q.front();
			q.pop();

			for (auto& x : adj[here]) {
				int next = x->target;
				if (x->residual() > 0 && parent[next] == -1) {
					parent[next] = here;
					path[next] = x;
					q.push(next);
				}
			}
		}
		if (parent[sink] == -1) break;

		int amount = INF;
		for (int i = sink; i != source; i = parent[i])
			amount = min(amount, path[i]->residual());
		for (int i = sink; i != source; i = parent[i])
			path[i]->push(amount);
		ans++;
	}
	cout << ans;
}