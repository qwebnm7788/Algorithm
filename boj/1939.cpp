/*
1939 중량제한

bfs를 이용하면 된다.
ans[node]에 현재 노드까지 오는데 가능한 최대 무게를 저장해둔다.

ans[nextnode] = 
1) 처음계산이라면 min(ans[currentNode],currentNode->nextNode 의 중량제한) 이고
2) ans[nextNode]가 이미 계산되어 있다면 지금까지 온 새로운 경로가 더 많은 무게의 짐을 가지고 갈 수 있는지를 체크한다.
   max(ans[nextNode], min(ans[currentNode],currentNode->nextNode 의 중량제한))

이때 주의할 점은 각 node가 갱신되는 시점이 달라지기 때문에 값이 업데이트 될때마다(처음 방문할때만이 아니라) 큐에 다시 넣어주어
주변으로 가는 ans값을 갱신해주어야 한다.

이 방식은 큐에 들어가는 노드에 따라 BFS의 과정이 길어질 수 있다. 복잡도는..?



또 다른 방법으로는
이분 탐색을 이용하여 시작->끝 까지 이동가능한 무게의 값을 찾는것이다. 이게 더 빠르다.
탐색은 O(logN)번 진행되고 매번 BFS를 돌게되어 (O(|N|+|M|)) 대략 O(NlogN)이 된다.
*/
#include <iostream>
#include <limits>
#include <queue>
#include <vector>
#include <algorithm>
using namespace std;

const int INF = numeric_limits<int>::max();

vector<vector<pair<int,int>>> adj;
vector<bool> visited;
vector<int> ans;

int main() {
	int n, m;
	cin >> n >> m;
	adj.resize(n);
	ans.resize(n);
	visited.resize(n);

	int u, v, c;
	for (int i = 0; i < m; ++i) {
		cin >> u >> v >> c;
		adj[u - 1].push_back(make_pair(v - 1, c));
		adj[v - 1].push_back(make_pair(u - 1, c));
	}

	int start, end;
	cin >> start >> end;
	start--, end--;

	queue<int> q;
	q.push(start);
	visited[start] = true;
	ans[start] = INF;
	while (!q.empty()) {
		int curr = q.front();
		q.pop();
		for (auto& next : adj[curr]) {
			if (!visited[next.first]) ans[next.first] = min(ans[curr], next.second);
			else {
				if (min(ans[curr], next.second) > ans[next.first]) {
					ans[next.first] = max(ans[next.first], min(ans[curr], next.second));
					q.push(next.first);
				}
			}

			if (!visited[next.first]) {
				visited[next.first] = true;
				q.push(next.first);
			}
		}
	}
	for (auto& next : adj[end])
		ans[end] = max(ans[end], min(ans[next.first], next.second));
	cout << ans[end];
}