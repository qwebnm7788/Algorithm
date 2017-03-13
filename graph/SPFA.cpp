/*
MCMF (Min-cost Max-flow)

그래프의 간선에 이제 용량뿐 아니라 비용(cost)가 존재한다고 생각해보자.

여기서 원하는것은 최대유량을 흘리는데 가능한 최소한의 비용을 들여서 흘려보내는 것이다.

만약 비용이 d인 간선에 f만큼의 유량이 흐르고 있다면 이때 드는 비용을 d*f라고 한다.
전체 비용은 이러한 모든 비용의 합을 의미한다.

포드풀커슨과 같이 매번 가능한 경로를 찾아서 유량을 흘리면서 더이상 경로를 찾지 못할때까지 반복하는 것은 비슷하지만
이때 찾는 경로는 최단경로를 찾는다는 점이 다르다.

즉 매번 최단경로를 찾아서 이 경로로 흐를 수 있는 가능한 최대유량을 흘리면서 드는 비용을 전체의 값에 더해주면서 구하면 된다.

이때 주의할 점은 최단경로를 구하는 부분에 사용되는 알고리즘은 음의 간선이 있는 그래프에서도 잘 작동해야 한다
왜냐면 max-flow를 구하는 알고리즘에서는 역방향 간선도 음의 유량이 흐른다는 가정을 하고 유량을 상쇄시키는 개념을 적용시켜서 구해주었기 때문에
유량을 상쇄시키는 과정에서 비용을 다시 원래대로 복구시키기위해서 비용역시 음의 값으로 적용시켜주어야 하기 때문이다.

이렇기 때문에 보통은 벨만포드 알고리즘을 살짝 변형한 SPFA(shortest path faster algorithm)을 사용한다.

벨만포드 알고리즘이 주요 부분이기 때문에 O(VE)에 동작하고 이 알고리즘으로 MCMF를 풀게되면 O(VEf)가 된다.
*/



/*
SPFA suedo code
G = 그래프 , s = source

우선 source를 제외한 모든 정점의 거리(비용)값을 INF로 설정한다.
for each vertex v != s in V(G)
	d(v) := INF

d(s) = 0		// source는 0이고

offer s into Q			//일반 큐(우선순위 큐 말고)에 삽입
while Q is not empty
	u := poll Q				//큐에서 하나를 꺼내고
	for each edge (u, v) in E(G)			//u에 연결된 모든 간선을 검사한다.
		if d(u) + w(u, v)  < d(v) then		//갱신되는 거리가 더 짧다면 갱신하자
			d(v) := d(u) + w(u, v)
			if v is not in Q then			//v가 지금! 큐에 없다면 
				offer v into Q				//큐에 삽입한다.


다익스트라 알고리즘과 상당히 유사하다.

*/


//1753 최단경로 문제의 SPFA 구현 코드


#include <iostream>
#include <vector>
#include <queue>
using namespace std;

const int MAXV = 20005;
const int INF = 987654321;

struct Edge {
	int v, c;		//목적지, 비용
};

vector<Edge> adj[MAXV];

int main() {
	int V, E, K;
	cin >> V >> E >> K;

	for (int i = 0; i < E; ++i) {
		int u, v, w;
		cin >> u >> v >> w;
		adj[u].push_back({ v,w });
	}

	int dist[MAXV], inQ[MAXV];				//dist[i] = 시작~ i번 정점까지의 최단경로, inQ[i] = 현재 큐에 i번 정점이 있는지의 여부(있다면 1 없다면 0)
	for (int i = 1; i <= V; ++i) dist[i] = INF, inQ[i] = 0;
	queue<int> Q;
	Q.push(K);		//시작점 삽입
	inQ[K] = 1;
	while (!Q.empty()) {
		int u = Q.front();
		Q.pop();
		inQ[u] = 0;

		//연결된 간선 체크
		for (auto& e : adj[u]) {
			int v = e.v;
			int w = e.c;
			if (dist[v] > dist[u] + w) {
				dist[v] = dist[u] + w;
				if (!inQ[v]) {
					Q.push(v);
					inQ[v] = 1;
				}
			}
		}
	}
	//벨만포드는 INF에서 완화될수도 있으므로 ==INF 쓰지 말자.
	for (int i = 1; i <= V; ++i) {
		if (dist[i] == INF - 2384) cout << "INF\n";
		else cout << dist[i] << "\n";
	}
}


// 다음은 11405번 책 구매하기 문제의 소스코드이다.

#include <cstdio>
#include <vector>
#include <queue>
#include <algorithm>
using namespace std;

const int MAXN = 100;
const int MAXV = 2 * (MAXN + 1);			//최대 정점개수
const int source = MAXV - 2;				//source 정점번호
const int sink = MAXV - 1;					//sink 정점번호
const int INF = 987654321;

int main() {
	//정점번호는 0~MAXN은 서점, MAXN~MAXN*2는 사람이라고 하자.
	int n, m;									//n=사람의 수 m = 서점의 수
	int capacity[MAXV][MAXV] = { 0 };			//간선의 용량
	int cost[MAXV][MAXV] = { 0 };				//간선의 비용
	int flow[MAXV][MAXV] = { 0 };				//간선의 유량

	vector<int> adj[MAXV];						//정점의 인접리스트

	scanf("%d %d", &n, &m);

	//cost = 0인 사람~sink 사이의 간선형성
	for (int i = MAXN; i < MAXN + n; ++i) {
		scanf("%d", &capacity[i][sink]);
		adj[sink].push_back(i);
		adj[i].push_back(sink);
	}

	//cost = 0인 source~서점 사이의 간선형성
	for (int i = 0; i < m; ++i) {
		scanf("%d", &capacity[source][i]);
		adj[source].push_back(i);
		adj[i].push_back(source);
	}

	//서점~사람사이에 간선형성 (이때는 cost가 든다.)
	for (int i = 0; i < m; ++i) {
		for (int j = MAXN; j < MAXN + n; ++j) {
			scanf("%d", &cost[i][j]);
			cost[j][i] = -cost[i][j];			//역방향 간선의 비용은 -1을 곱해준다.
			capacity[i][j] = INF;				//순방향 간선에만 용량을 준다.
			adj[i].push_back(j);
			adj[j].push_back(i);
		}
	}

	int ans = 0;				//최소비용
	//MCMF
	while (true) {
		int prev[MAXV], dist[MAXV];
		bool inQ[MAXV] = { 0 };				//inQ[i] = i번 정점이 큐에 현재 들어있는가?
		queue<int> Q;
		fill(prev, prev + MAXV, -1);
		fill(dist, dist + MAXV, INF);
		dist[source] = 0;
		inQ[source] = true;
		Q.push(source);

		while (!Q.empty()) {
			int curr = Q.front();
			Q.pop();
			inQ[curr] = false;
			for (int next : adj[curr]) {
				//최단경로 + residual 이 있어야 한다!
				if (capacity[curr][next] - flow[curr][next] > 0 && dist[next] > dist[curr] + cost[curr][next]) {
					dist[next] = dist[curr] + cost[curr][next];
					prev[next] = curr;
					if (!inQ[next]) {
						//큐에 들어있지 않다면 추가.
						Q.push(next);
						inQ[next] = true;
					}
				}
			}
		}
		//더이상 경로를 찾지못하면 종료
		if (prev[sink] == -1) break;

		//찾은 경로에서 흘릴수 있는 최대 유량을 찾는다.
		int possible = INF;
		for (int i = sink; i != source; i = prev[i])
			possible = min(possible, capacity[prev[i]][i] - flow[prev[i]][i]);

		//흘려 보내준다. + 이 때 드는 비용을 계산하자.
		for (int i = sink; i != source; i = prev[i]) {
			ans += possible * cost[prev[i]][i];			//정답계산
			flow[prev[i]][i] += possible;
			flow[i][prev[i]] -= possible;
		}
	}

	printf("%d", ans);
}