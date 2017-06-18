/*
1585 경찰

cost를 벌금으로 두고 in - out 사이의 간선에 min(f, (t-s)*(t-s))의 cost를 주면 된다.
또한 벌금의 최대값도 구해야 하므로 cost의 부호를 반대로 두고 다시 한번 MCMF를 돌려준 후 마이너스를 붙여 출력하면 된다.

max-flow가 n이 되지 않으면 -1을 출력한다.
*/
#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
using namespace std;

const int MAXN = 51;
const int MAXV = 2 * MAXN + 3;
const int INF = 987654321;

int flow[MAXV][MAXV];
int capacity[MAXV][MAXV];
int cost[MAXV][MAXV];

int main() {
	ios_base::sync_with_stdio(false);

	freopen("input.txt", "r", stdin);
	int n;
	cin >> n;

	vector<int> in(n), out(n);
	for (int i = 0; i < n; ++i)
		cin >> in[i];
	for (int i = 0; i < n; ++i)
		cin >> out[i];

	int t, f;
	cin >> t >> f;

	int source = 0, sink = 2 * n + 1, size = 2 * n + 3;
	vector<vector<int>> adj(size);
	//source -> in
	for (int i = 1; i <= n; ++i) {
		adj[source].push_back(i);
		adj[i].push_back(source);
		capacity[source][i] = 1;
	}

	//in -> out
	for (int i = 0; i < n; ++i) {
		for (int j = 0; j < n; ++j) {
			if (in[i] < out[j]) {
				int s = out[j] - in[i];
				adj[i + 1].push_back(j + 1 + n);
				adj[j + 1 + n].push_back(i + 1);
				capacity[i + 1][j + 1 + n] = 1;
				if (s < t) {
					cost[i + 1][j + 1 + n] = min(f, (t - s)*(t - s));
					cost[j + 1 + n][i + 1] = -cost[i + 1][j + 1 + n];
				}
			}
		}
	}

	//out -> sink
	for (int i = 1; i <= n; ++i) {
		adj[n + i].push_back(sink);
		adj[sink].push_back(n + i);
		capacity[n + i][sink] = 1;
	}


	int minans = -1, maxans = -1, temp = 0;
	int cnt = 0;
	while (true) {
		vector<int> prev(size, -1);
		vector<int> dist(size, INF);
		vector<bool> inQ(size, false);
		queue<int> q;
		q.push(source);
		dist[source] = 0;
		inQ[source] = true;
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
		if (prev[sink] == -1) {
			if (minans == -1) {
				minans = temp;
				memset(flow, 0, sizeof(flow));
				for (int i = 1; i <= n; ++i) {
					for (int j = 1; j <= n; ++j) {
						cost[i][j + n] = -cost[i][j + n];
						cost[j + n][i] = -cost[j + n][i];
					}
				}
				temp = 0;
				continue;
			}
			else {
				maxans = -temp;
				break;
			}
		}

		int possible = INF;
		for (int i = sink; i != source; i = prev[i])
			possible = min(possible, capacity[prev[i]][i] - flow[prev[i]][i]);
		for (int i = sink; i != source; i = prev[i]) {
			flow[prev[i]][i] += possible;
			flow[i][prev[i]] -= possible;
			temp += possible*cost[prev[i]][i];
		}
		cnt += possible;
	}
	if (cnt == 2*n) cout << minans << " " << maxans;
	else cout << "-1";
}