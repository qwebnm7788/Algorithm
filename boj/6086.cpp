/*
6086 최대유량

maxflow 연습문제
*/
#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
using namespace std;

const int INF = 987654321;
const int MAXV = 52;

struct Edge {
	int target, capacity, flow;
	Edge* reverse;

	int residual() const {
		return capacity - flow;
	}

	void push(int amount) {
		flow += amount;
		reverse->flow -= amount;
	}
};

vector<vector<Edge*>> adj;

void addEdge(int u, int v, int capacity) {
	Edge* uv = new Edge();
	Edge* vu = new Edge();

	uv->target = v;
	uv->capacity = capacity;
	uv->flow = 0;
	uv->reverse = vu;

	vu->target = u;
	vu->capacity = 0;
	vu->flow = 0;
	vu->reverse = uv;

	adj[u].push_back(uv);
	adj[v].push_back(vu);
}

int toInt(char x) {
	if (x >= 'a' && x <= 'z')
		return x - 'a';
	else
		return x - 'A' + 26;
}

int main() {
	freopen("input.txt", "r", stdin);
	int n;
	cin >> n;

	adj.resize(MAXV);

	char a, b;
	int x, y, z;
	for (int i = 0; i < n; ++i) {
		cin >> a >> b >> z;
		x = toInt(a);
		y = toInt(b);
		addEdge(x, y, z);
	}
	int source = toInt('A');
	int sink = toInt('Z');
	int ans = 0;
	while (true) {
		vector<int> parent(MAXV, -1);
		vector<Edge*> path(MAXV);
		queue<int> q;
		parent[source] = source;
		q.push(source);
		while (!q.empty() && parent[sink] == -1) {
			int here = q.front();
			q.pop();
			for (auto& next : adj[here]) {
				int target = next->target;
				if (next->residual() > 0 && parent[target] == -1) {
					parent[target] = here;
					path[target] = next;
					q.push(next->target);
				}
			}
		}
		if (parent[sink] == -1) break;

		int amount = INF;
		for(int i = sink; i != source; i = parent[i])
			amount = min(amount, path[i]->residual());
		for (int i = sink; i != source; i = parent[i])
			path[i]->push(amount);
		ans += amount;
	}
	cout << ans;
}

