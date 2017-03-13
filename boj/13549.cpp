/*
13549 숨바꼭질3

처음에는 x-1,x+1,2x인 정점을 만들어서 x와 연결시킨 그래프를 만든 후 다익스트라 알고리즘으로
최단거리를 구해주어 해결하였다.

좀 더 최적화를 해보자면 다익스트라는 현재정점에 도달하는 순간 최단거리가 확정이 되기때문에 되돌아 볼 필요가 없어지므로
그래프를 만들어 두지 않고 그냥 그때 그때 가상의 정점에 도달한다고 생각하며 구해주면

따로 그래프를 저장할 필요가 없어진다.
*/
#include <iostream>
#include <queue>
#include <vector>
#include <algorithm>
using namespace std;

const int INF = 987654321;

vector<int> dist;

int main() {
	freopen("input.txt", "r", stdin);

	int n, k;
	cin >> n >> k;

	int MAX = 2 * max(n, k);

	dist = vector<int>(MAX+5, INF);

	priority_queue<pair<int, int>> pq;
	dist[n] = 0;
	pq.push(make_pair(dist[n], n));

	while (!pq.empty()) {
		int cost = -pq.top().first;
		int curr = pq.top().second;
		pq.pop();

		if (cost > dist[curr]) continue;
		
		int next;
		if (curr) {
			next = curr - 1;
			if (dist[next] > dist[curr] + 1) {
				dist[next] = dist[curr] + 1;
				pq.push(make_pair(-dist[next], next));
			}
		}
		if (curr + 1 <= MAX) {
			next = curr + 1;
			if (dist[next] > dist[curr] + 1) {
				dist[next] = dist[curr] + 1;
				pq.push(make_pair(-dist[next], next));
			}
		}
		if (2 * curr <= MAX) {
			next = 2 * curr;
			if (dist[next] > dist[curr]) {
				dist[next] = dist[curr];
				pq.push(make_pair(-dist[next], next));
			}
		}
	}
	cout << dist[k];
}