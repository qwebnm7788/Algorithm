/*
12784번 인하니카 공화국

(G)
leaf 노드에서부터 루트까지 올라오면서 cost를 현재노드에서
부모노드로의 다이너마이트 개수라고 할때

dfs(here) = min(cost,dfs(here의 자식)의 총합)
으로 구해줄 수 있다.
*/
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

const int INF = 2e9;

vector<vector<pair<int, int>>> adj;
vector<bool> visited;

int dfs(int here, int cost) {
	visited[here] = true;
	int ret = cost;
	int temp = 0;
	if (adj[here].size() == 1 && here != 0) temp = INF;
	for (auto& edge : adj[here]) {
		int next = edge.first;
		if(!visited[next])
			temp += dfs(next,edge.second);
	}
	return min(ret, temp);
}

int main() {
	freopen("input.txt", "r", stdin);
	int test;
	cin >> test;
	while (test--) {
		int n, m;
		cin >> n >> m;

		adj = vector <vector<pair<int, int>>>(n);
		visited = vector<bool>(n,false);

		int u, v, w;
		for (int i = 0; i < m; ++i) {
			cin >> u >> v >> w;
			adj[u - 1].push_back({ v - 1,w });
			adj[v - 1].push_back({ u - 1,w });
		}
		cout << dfs(0,INF) << endl;
	}
}