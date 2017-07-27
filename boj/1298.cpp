#include <iostream>
#include <queue>
#include <vector>
#include <algorithm>
using namespace std;

const int INF = 2e9;

struct Edge {
	int to, capacity, flow;
	Edge* rev;

	Edge() {
		Edge(-1, 0);
	}
	Edge(int t, int c)
		:to(t), capacity(c), flow(0), rev(nullptr) {}

	int residual() {
		return capacity - flow;
	}

	void push(int amount) {
		this->flow += amount;
		rev->flow -= amount;
	}
};

int main() {
	ios_base::sync_with_stdio(false);
	int n, m;
	cin >> n >> m;

	int size = n + m + 2;
	vector<vector<Edge*>> adj(size);

	int source = 0, sink = n + m + 1;
	for (int i = 1; i <= n; ++i) {
		Edge* x = new Edge(i, 1);
		Edge* y = new Edge(source, 0);
		x->rev = y;
		y->rev = x;
		adj[source].push_back(x);
		adj[i].push_back(y);
	}

	int a, b;
	for (int i = 0; i < m; ++i) {
		cin >> a >> b;
		Edge* x = new Edge(n + b, INF);
		Edge* y = new Edge(a, 0);
		x->rev = y;
		y->rev = x;
		adj[a].push_back(x);
		adj[n + b].push_back(y);
	}

	for (int i = n + 1; i <= n + m; ++i) {
		Edge* x = new Edge(sink, 1);
		Edge* y = new Edge(i, 0);
		x->rev = y;
		y->rev = x;
		adj[i].push_back(x);
		adj[sink].push_back(y);
	}

	int answer = 0;
	while (true) {
		vector<int> prev(size, -1);
		vector<Edge*> path(size);
		queue<int> q;
		q.push(source);
		while (!q.empty()) {
			int here = q.front();
			q.pop();
			for (auto& edge : adj[here]) {
				int next = edge->to;
				if (edge->residual() > 0 && prev[next] == -1) {
					prev[next] = here;
					path[next] = edge;
					q.push(next);
				}
			}
		}

		if (prev[sink] == -1) break;

		int flow = INF;
		for (int i = sink; i != source; i = prev[i]) {
			flow = min(flow, path[i]->residual());
		}
		for (int i = sink; i != source; i = prev[i]) {
			path[i]->push(flow);
		}
		answer += flow;
	}
	cout << answer;
}