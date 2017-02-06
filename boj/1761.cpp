/*
1761
정점들의 거리

LCA를 이용하여 두 점의 거리를 구하는데 u,v사이의 거리는 dist[u]+dist[v]-2*dist[LCA(u,v)]와 같다.

아무 정점 하나를 잡고 그 정점에서 모든 정점까지의 거리를 구해준다.
이 경우에는 트리이고 모든 친구들이 한 경로로만 연결되어있고 구하는것이 최단경로지만 트리에서 두 정점사이의 거리 자체가 최단경로이기때문에
그냥 DFS로도 충분히 구해줄 수 있다. -> 그렇지만 visited배열을 끌고가주지 않으면 이게 재귀가 깊어지는 것 같다.
*/
#include <cstdio>
#include <vector>
#include <algorithm>
#include <cstring>
using namespace std;

const int MAX_HEIGHT = 17;
const int MAX_N = 40000;

vector<vector<pair<int,int>>> adj;
vector<int> depth;
vector<int> dist;
vector<bool> visited;

int parent[MAX_N][MAX_HEIGHT];

//dfs이용해서 트리를 형성
//vistited를 표시 안해주면 양방향 간선이라서 재귀가 엄청 깊어지는것 같다.!
void dfs(int here) {
	visited[here] = true;
	for (int i = 0; i < adj[here].size(); ++i) {
		int next = adj[here][i].first;
		int nextcost = adj[here][i].second;
		if (!visited[next]) {
			depth[next] = depth[here] + 1;
			parent[next][0] = here;
			dist[next] = dist[here] + nextcost;
			dfs(next);
		}
	}
}
int main() {
	freopen("input.txt", "r", stdin);

	int n;
	scanf("%d", &n);

	adj.resize(n);
	dist.resize(n, 0);
	depth = vector<int>(n, -1);
	visited = vector<bool>(n, false);
	memset(parent, -1, sizeof(parent));

	//트리는 모든 점이 하나의 경로로 연결되어서 최단거리는 그냥 두 정점 사이의 거리이다.
	//또한 모든 정점은 연결되어 있으므로 아무 정점이나 하나를 루트라고 생각하고 그래프로 표현해주면 된다.
	int u, v, w;
	for (int i = 0; i < n - 1; ++i) {
		scanf("%d %d %d", &u, &v, &w);

		adj[u - 1].push_back(make_pair(v - 1, w));
		adj[v - 1].push_back(make_pair(u - 1, w));
	}

	dist[0] = 0;
	depth[0] = 0;
	dfs(0);

	//parent배열 형성
	for (int k = 0; k < MAX_HEIGHT-1; ++k) {
		for (int i = 0; i < n; ++i) {
			if (parent[i][k] != -1)
				parent[i][k + 1] = parent[parent[i][k]][k];
		}
	}

	//이제 lca를 찾아볼까나.
	int m;
	scanf("%d", &m);

	int a, b;
	for (int i = 0; i < m; ++i) {
		scanf("%d %d", &u, &v);

		u--;
		v--;

		a = u;
		b = v;

		if (depth[u] < depth[v])
			swap(u, v);

		//높이 맞춰주기
		int diff = depth[u] - depth[v];
		for (int k = 0; diff != 0; ++k) {
			if (diff % 2)
				u = parent[u][k];
			diff /= 2;
		}

		if (u != v) {
			//높이가 맞았으니 이제 LCA를 찾아서 같이 올라가 보자.!
			for (int k = MAX_HEIGHT - 1; k >= 0; --k) {
				if (parent[u][k] != -1 && parent[u][k] != parent[v][k]) {
					u = parent[u][k];
					v = parent[v][k];
				}
			}
			u = parent[u][0];
		}
		printf("%d\n", dist[a] + dist[b] - 2 * dist[u]);
	}
	
}