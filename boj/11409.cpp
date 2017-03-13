/*
11409 열혈강호6

MCMF문제이다.

그렇지만 이때는 최대의 비용을 구하는 문제인데
이는 최소비용을 구하는 알고리즘을 응용하면 구할 수 있다.
->모든 비용에 '-'를 붙여서 뒤집어 주게 되면 최대값이 최소값으로 변하기 때문에
이때 최소 비용을 구하게 되면 '-최대비용'이 나오게 된다.

이를 이용하면 문제를 해결할 수 있다.
*/
#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
using namespace std;

const int MAXN = 405;
const int MAXM = 405;
const int MAXV = MAXN + MAXM + 2;
const int INF = 987654321;

int capacity[MAXV][MAXV];
int flow[MAXV][MAXV];
int cost[MAXV][MAXV];

//source = 0, sink = MAXN+MAXM+1
int main() {
	freopen("input.txt", "r", stdin);
	int n, m;
	cin >> n >> m;

	int totalV = n + m + 2;

	vector<vector<int>> adj(totalV);

	//employee = 1~n, job = n+1~n+m, source = 0, sink = n+m+1
	int source = 0;
	int sink = n + m + 1;

	//source -> employee
	for (int i = 1; i <= n; ++i) {
		adj[source].push_back(i);
		adj[i].push_back(source);
		capacity[source][i] = 1;
	}

	//employee -> job
	int num, can, pay;
	for (int i = 1; i <= n; ++i) {
		cin >> num;
		for (int j = 0; j < num; ++j) {
			cin >> can >> pay;
			adj[i].push_back(n + can);
			adj[n + can].push_back(i);
			capacity[i][n + can] = 1;
			cost[i][n + can] = -pay;
			cost[n + can][i] = pay;
		}
	}

	//job -> sink
	for (int i = n + 1; i <= n + m; ++i) {
		adj[i].push_back(sink);
		adj[sink].push_back(i);
		capacity[i][sink] = 1;
	}

	//MCMF
	int cnt = 0, maxPayment = 0;
	while (true) {
		vector<int> prev(totalV, -1);
		vector<int> dist(totalV, INF);
		vector<bool> inQ(totalV, false);
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
			flow[prev[i]][i] += possible;
			flow[i][prev[i]] -= possible;
			maxPayment += possible * cost[prev[i]][i];
		}
		cnt += possible;
	}
	cout << cnt << endl << -maxPayment;
}

