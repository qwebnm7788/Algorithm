/*
11408 열혈강호 5

비용이 추가된 플로우 문제
SPFA를 이용한 MCMF로 풀 수 있다.

*/
#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
using namespace std;

const int MAXN = 401;
const int MAXM = 401;
const int MAXV = MAXN + MAXM + 2;
const int INF = 987654321;

int capacity[MAXV][MAXV];
int flow[MAXV][MAXV];
int cost[MAXV][MAXV];

int main() {
	freopen("input.txt", "r", stdin);
	ios_base::sync_with_stdio(false);
	int n, m;
	cin >> n >> m;

	int source = 0, sink = n + m + 1;

	vector<vector<int>> adj(n + m + 2);
	//source-employee
	for (int i = 1; i <= n; ++i) {
		adj[source].push_back(i);
		adj[i].push_back(source);
		capacity[source][i] = 1;
	}

	//employee - job
	for (int i = 1; i <= n; ++i) {
		int num, next, pay;
		cin >> num;
		for (int j = 0; j < num; ++j) {
			cin >> next >> pay;
			adj[i].push_back(n + next);
			adj[n + next].push_back(i);
			cost[i][n + next] = pay;
			cost[n + next][i] = -pay;
			capacity[i][n + next] = 1;
		}
	}

	//job - sink
	for (int i = n + 1; i <= n + m; ++i) {
		adj[i].push_back(sink);
		adj[sink].push_back(i);
		capacity[i][sink] = 1;
	}

	int ans = 0, cnt =0;

	while (true) {
		int prev[MAXV], dist[MAXV];
		bool inQ[MAXV];
		fill(prev, prev + MAXV, -1);
		fill(dist, dist + MAXV, INF);
		fill(inQ, inQ + MAXV, false);
		queue<int> q;
		q.push(source);
		inQ[source] = true;
		dist[source] = 0;
		while (!q.empty()) {
			int curr = q.front();
			q.pop();
			inQ[curr] = false;
			for (int next : adj[curr]) {
				if (capacity[curr][next] - flow[curr][next] > 0 && dist[next] > dist[curr] + cost[curr][next]) {
					dist[next] = dist[curr] + cost[curr][next];
					prev[next] = curr;
					if (!inQ[next]) {
						q.push(next);
						inQ[next] = true;
					}
				}
			}
		}
		if (prev[sink] == -1) break;

		int possible = INF;
		for (int i = sink; i != source; i = prev[i])
			possible = min(possible, capacity[prev[i]][i] - flow[prev[i]][i]);

		for (int i = sink; i != source; i = prev[i]) {
			ans += cost[prev[i]][i] * possible;
			flow[prev[i]][i] += possible;
			flow[i][prev[i]] -= possible;
		}
		cnt++;
	}
	cout << cnt << endl << ans;
}