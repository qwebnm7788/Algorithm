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
	int m, n;
	cin >> m >> n;

	int size = n*m + n + m + 2;
	vector<vector<Edge*>> adj(size);

	int source = 0, sink = size - 1;
	int in, cnt, buy;
	for (int i = 1; i <= m; ++i) {
		cin >> in;
		Edge* x = new Edge(i, in);
		Edge* y = new Edge(source, 0);
		x->rev = y;
		y->rev = x;
		adj[source].push_back(x);
		adj[i].push_back(y);
	}

	for (int i = 1; i <= n; ++i) {
		for (int j = 1; j <= m; ++j) {
			Edge* x = new Edge(i*m + j, INF);
			Edge* y = new Edge((i - 1)*m + j, 0);
			x->rev = y;
			y->rev = x;
			adj[(i - 1)*m + j].push_back(x);
			adj[i*m + j].push_back(y);
		}
		cin >> cnt;
		vector<int> open(cnt);
		for (int j = 0; j < cnt; ++j) {
			cin >> open[j];
			Edge* x = new Edge(n*m + m + i, INF);
			Edge* y = new Edge(i*m + open[j], 0);
			x->rev = y;
			y->rev = x;
			adj[i*m + open[j]].push_back(x);
			adj[n*m + m + i].push_back(y);
		}
		if (i < n) {
			for (int j = 0; j < cnt; ++j) {
				for (int k = 0; k < cnt; ++k) {
					if (j == k) continue;
					Edge* x = new Edge((i + 1)*m + open[k], INF);
					Edge* y = new Edge(i*m + open[j], 0);
					x->rev = y;
					y->rev = x;
					adj[i*m + open[j]].push_back(x);
					adj[(i + 1)*m + open[k]].push_back(y);
				}
			}
		}
		cin >> buy;
		Edge* x = new Edge(sink, buy);
		Edge* y = new Edge(n*m + m + i, 0);
		x->rev = y;
		y->rev = x;
		adj[n*m + m + i].push_back(x);
		adj[sink].push_back(y);
	}

	int answer = 0;
	while (true) {
		vector<int> prev(size, -1);
		vector<Edge*> path(size);
		queue<int> q;
		q.push(source);
		while (!q.empty() && prev[sink] == -1) {
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
