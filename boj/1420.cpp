/*
1420 학교가지마!

source(나) 에서 sink(학교) 까지 가는 flow를 흐르지 못하도록 막는 최소의 정점갯수를 세는 것이다.

만약 간선으로 이루어졌다고 생각해본다면 이러한 격자그래프를 4방향으로 간선으로 이어준다음 min-cut을 찾아내는 문제이다.
(즉 최소한의 비용을 들여서 source->sink로 가는 간선을 자르는 비용을 찾으면된다)
또한 mincut-maxflow 의 내용을 응용해보면 mincut = maxflow와 같다. 즉 그냥 maxflow를 출력해주면 된다.

하지만 이 문제는 정점의 갯수를 구하는것이기 때문에 각 정점의 용량을 표현해주어야 하고 가장 쉬운 방법은 정점을 2개로 쪼개서 표현하는 것이다.
그 둘 사이에 용량 1짜리 간선을 추가해줌으로써 각 정점을 한번씩만 이용할 수 있음을 표현해주고 다른 간선은 용량이 INF로 한 뒤 컷을 구하게 되면 1짜리만 커팅이 되어서
결국은 min-cut의 값 자체가 자를 정점의 수가 된다.

따라서 이렇게 표현한 그래프에서 maxflow를 찾아주면 정답이 된다.

각 정점에 번호를 매길때 i*n+j라고 생각하기 쉬운데 이렇게 되면 각 줄의 맨 마지막과 다음줄의 맨처음이 겹치게 된다. (index 가 0부터 출발하기 떄문에)
번호를 매길때는 i*m+j 임을 알자. 즉 각 줄의 갯수로 생각해주어야지 그냥 row의 번호로 생각하면 안된다. (갯수를 번호로 한다고 생각하자.)

또한 source와 sink의 번호에도 주의한다.

-1이 나오는 경우는 예외케이스로 처리를 해주어야 한다.
이런 경우는 K와 H가 바로옆에 붙어있는 경우가 된다.
*/
#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
using namespace std;

const int INF = 987654321;
const int MAXN = 101;

struct Edge {
	int target, flow, capacity;
	Edge* oppose;
	int residual() const {
		return capacity - flow;
	}
	void push(int amount) {
		flow += amount;
		oppose->flow -= amount;
	}
};

vector<vector<Edge*>> adj;
vector<bool> visited;
char arr[MAXN][MAXN];
int id[MAXN][MAXN];

void addEdge(int u, int v, int capacity) {
	Edge* uv = new Edge();
	Edge* vu = new Edge();

	uv->target = v;
	uv->flow = 0;
	uv->capacity = capacity;
	uv->oppose = vu;

	vu->target = u;
	vu->flow = 0;
	vu->capacity = 0;
	vu->oppose = uv;

	adj[u].push_back(uv);
	adj[v].push_back(vu);
}

void dfs(int here) {
	if (visited[here]) return;
	visited[here] = true;
	for (auto& x : adj[here]) {
		int next = x->target;
		if (!visited[next] && x->residual() > 0)
			dfs(next);
	}
}

int main() {
	freopen("input.txt", "r", stdin);

	int n, m;
	cin >> n >> m;

	adj.resize(8 * n*m);
	int source, sink, here, next;
	for (int i = 0; i < n; ++i) {
		for (int j = 0; j < m; ++j) {
			cin >> arr[i][j];
			here = i*m + j;
			if (arr[i][j] == 'K')
				source = 2 * here + 1;
			else if (arr[i][j] == 'H')
				sink = 2 * here;
		}
	}

	bool check = false;
	for (int i = 0; i < n; ++i) {
		for (int j = 0; j < m; ++j) {
			here = i*m + j;
			id[i][j] = here;
			if (arr[i][j] == '#') continue;

			addEdge(2 * here, 2 * here + 1, 1);
			if (i > 0 && arr[i - 1][j] != '#') {
				next = (i - 1)*m + j;
				addEdge(2 * here + 1, 2 * next, INF);
				if (2 * here + 1 == source && 2 * next == sink) check = true;
			}
			if (i < n - 1 && arr[i + 1][j] != '#') {
				next = (i + 1)*m + j;
				addEdge(2 * here + 1, 2 * next, INF);
				if (2 * here + 1 == source && 2 * next == sink) check = true;
			}
			if (j > 0 && arr[i][j - 1] != '#') {
				next = i*m + j - 1;
				addEdge(2 * here + 1, 2 * next, INF);
				if (2 * here + 1 == source && 2 * next == sink) check = true;
			}
			if (j < m - 1 && arr[i][j + 1] != '#') {
				next = i*m + j + 1;
				addEdge(2 * here + 1, 2 * next, INF);
				if (2 * here + 1 == source && 2 * next == sink) check = true;
			}
		}
	}
	if (check) {
		cout << "-1";
		return 0;
	}

	int ans = 0;
	while (true) {
		vector<int> parent(8 * n*m, -1);
		vector<Edge*> path(8 * n*m);
		queue<int> q;
		parent[source] = source;
		q.push(source);
		while (!q.empty() && parent[sink] == -1) {
			int here = q.front();
			q.pop();

			for (auto& x : adj[here]) {
				int next = x->target;
				if (x->residual() > 0 && parent[next] == -1) {
					parent[next] = here;
					path[next] = x;
					q.push(next);
				}
			}
		}

		if (parent[sink] == -1) break;

		int amount = INF;
		for (int i = sink; i != source; i = parent[i])
			amount = min(amount, path[i]->residual());
		for (int i = sink; i != source; i = parent[i])
			path[i]->push(amount);
		ans += amount;
	}

	cout << ans;
}