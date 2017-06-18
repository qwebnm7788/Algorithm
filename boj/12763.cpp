/*
12763번 지각하면 안돼

*/
#include <iostream>
#include <queue>
#include <cstring>
#include <vector>
#include <algorithm>
using namespace std;

const int INF = 2e9;

int main() {
	freopen("input.txt", "r", stdin);
	int n, t, m, l;
	cin >> n >> t >> m >> l;

	vector<vector<pair<int, pair<int, int>>>> adj(n);
	vector<vector<int>> dist(n, vector<int>(t + 1, INF));

	int u, v, w, y;
	for (int i = 0; i < l; ++i) {
		cin >> u >> v >> w >> y;
		adj[u - 1].push_back({ v - 1,{w,y} });
		adj[v - 1].push_back({ u - 1,{w,y} });
	}
	priority_queue<pair<int, pair<int, int>>> pq;
	dist[0][0] = 0;
	pq.push({ -dist[0][0],{0,0} });				//pq = {dist, {number, cnt}}

	while (!pq.empty()) {
		int cost = -pq.top().first;
		int here = pq.top().second.first;
		int time = pq.top().second.second;
		pq.pop();

		for (auto& edge : adj[here]) {
			if (edge.second.first + time > t || edge.second.second + cost > m) continue;
			if (dist[edge.first][edge.second.first + time] > cost + edge.second.second) {
				dist[edge.first][edge.second.first + time] = cost + edge.second.second;
				pq.push({ -dist[edge.first][edge.second.first + time],{edge.first,edge.second.first + time} });
			}
		}
	}

	int ans = INF;
	for (int i = 0; i <= t; ++i) {
		if(dist[n-1][i] <= m)
			ans = min(ans, dist[n - 1][i]);
	}
	if (ans == INF) cout << "-1";
	else cout << ans;
}
