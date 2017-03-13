/*
10282 Failing Components

주어진 시작점에서 도달가능한 점들까지의 최단거리를 모두 구한 후
그 중 최대값을 출력하면 된다.

다익스트라를 한번 돌려주면 된다. O(|V|+|E|)
*/
#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
using namespace std;

const int INF = 987654321;

int main() {
	freopen("input.txt", "r", stdin);

	int test;
	cin >> test;

	for (int z = 0; z < test; ++z) {
		int n, d, c;
		cin >> n >> d >> c;
		c--;

		vector<vector<pair<int, int>>> adj(n);

		int a, b, s;
		for (int i = 0; i < d; ++i) {
			cin >> a >> b >> s;
			adj[b - 1].push_back(make_pair(a - 1, s));
		}

		vector<int> dist(n, INF);
		vector<bool> visited(n, false);
		dist[c] = 0;
		priority_queue<pair<int, int>> pq;
		pq.push(make_pair(-dist[c], c));

		while (!pq.empty()) {
			int cost = -pq.top().first;
			int curr = pq.top().second;
			pq.pop();
	
			for (int i = 0; i < adj[curr].size(); ++i) {
				int next = adj[curr][i].first;
				int nextcost = adj[curr][i].second;
				if (dist[next] > cost + nextcost) {
					dist[next] = cost + nextcost;
					pq.push(make_pair(-dist[next], next));
				}
			}
		}

		int cnt = 0, sec = -1;
		for (int i = 0; i < n; ++i) {
			if (dist[i] != INF) {
				cnt++;
				sec = max(sec, dist[i]);
			}
		}
		cout << cnt << " " << sec << endl;
	}
}
