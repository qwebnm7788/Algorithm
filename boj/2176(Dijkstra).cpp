#include <stdio.h>
#include <vector>
#include <queue>
using namespace std;

const int MAX_V = 1000;
const int INF = 987654321;

int dp[MAX_V];		//dp[i]는 i번 정점까지 오는 합리적인 이동경로의 수
int dist[MAX_V];
vector<pair<int, int>> adj[MAX_V];

//here까지 오는 합리적인 이동경로의 수를 반환한다.
int func(int here) {
	if (here == 1)
		return 1;
	int& ret = dp[here];
	if (ret != -1)
		return ret;

	ret = 0;
	for (int i = 0; i < adj[here].size(); ++i) {
		int next = adj[here][i].first;
		if (dist[here] > dist[next]) {
			//만약에 1~here까지의 거리가 1~next까지의 거리보다 크다면 이 경로는 here~next~...~1까지의 합리적인 이동경로의 일부가 될꺼야
			//그러니깐 1~next까지의 합리적인 이동경로의 수를 모두 합한것이 1~here까지 오는 합리적인 이동경로의 수와 같아.
			ret += func(next);
		}
	}
	return ret;
}
int main() {
	freopen("input.txt", "r", stdin);
	int n, m;
	scanf("%d %d", &n, &m);


	int u, v, e;
	for (int i = 0; i < m; ++i) {
		scanf("%d %d %d", &u, &v, &e);
		adj[u - 1].push_back(make_pair(v - 1, e));
		adj[v - 1].push_back(make_pair(u - 1, e));
	}

	for (int i = 0; i < n; ++i) {
		dist[i] = INF;
		dp[i] = -1;
	}

	//1번부터 시작하여 최단경로를 구하게 되면 각 정점에서 1번 정점으로 가는 최단경로를 알 수 있게 된다.
	//0번에서 시작해서 최단경로를 구하게 된다면 각정점에서의 1번까지의 최단경로를 모두 구할수 없다. 왜냐면 0번에서 i번 정점까지의 최단경로가 성립해야지만
	//i번에서 1번까지의 최단경로의 경로가 추가되게 되어서 그냥 두었을때 i~1까지의 최단경로가 성립했지만 0~i까지의 길이가 최단경로가 되지 못해서
	//추가가 안되는 경우가 생길 수 있다.
	//따라서 1번에서 각 정점으로의 최단경로를 구해주어야 한다.?
	//혹은 모든 정점에 대해서 다익스트라를 돌려서 1번정점까지의 거리를 구해주는 방법도 가능하다 (플로이드는 시간초과라는 듯 .. 정점의 수가 10^3이라서 V^3이면 10^9이 된다.)
	priority_queue<pair<int, int>> pq;
	dist[1] = 0;
	pq.push(make_pair(0, 1));

	while (!pq.empty()) {
		int here = pq.top().second;
		int cost = -pq.top().first;
		pq.pop();

		if (dist[here] < cost)
			continue;

		for (int i = 0; i < adj[here].size(); ++i) {
			int next = adj[here][i].first;
			int nextcost = adj[here][i].second;

			if (dist[next] > cost + nextcost) {
				dist[next] = cost + nextcost;
				pq.push(make_pair(-dist[next], next));
			}
		}
	}

	
	printf("%d", func(0));
}