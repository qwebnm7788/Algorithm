/*
11495 격자 0 만들기

격자 그래프를 만들어고 이분그래프로 분류한 후에 max-flow를 구해주면 된다.
그러나 이 값 자체는 정답이 아니고
이렇게 max-flow를 흘려보낸 후에 남은 친구들의 값자체는 그 크기만큼 연산을 해주어야 0을 만들어 줄수 있으므로
계산을 해주어야 한다.

이분 그래프이므로 구해준 max-flow는 실제로 연산을 한 횟수의 x2배 이므로 초기의 모든 격자의 총합을 total이라고 하면
total-2*max_flow 가 남아있는 친구의 총 합이된다. 여기에 max-flow를 더해야 구해주는 값이 되므로

정답은 ans = total-2*max_flow + max_flow = total - max_flow가 된다.!
*/
#include <cstdio>
#include <vector>
#include <queue>
#include <limits>
#include <algorithm>
using namespace std;

const int INF = numeric_limits<int>::max();

const int dx[4] = { -1,0,1,0 };
const int dy[4] = { 0,1,0,-1 };

int main() {
	freopen("input.txt", "r", stdin);
	int test;
	scanf("%d", &test);
	for (int z = 0; z < test; ++z) {
		int n, m;
		scanf("%d %d", &n, &m);

		vector<vector<int>> arr(n, vector<int>(m));
		vector<vector<int>> capacity(n*m + 2, vector<int>(n*m + 2, 0));
		vector<vector<int>> flow(n*m + 2, vector<int>(n*m + 2, 0));
		vector<vector<int>> id(n*m + 2, vector<int>(n*m + 2, 0));
		int source = n*m;
		int sink = n*m + 1;

		int A = 0, B = 0;		//A그룹 B그룹의 수
		int total = 0;
		for (int i = 0; i < n; ++i) {
			for (int j = 0; j < m; ++j) {
				scanf("%d", &arr[i][j]);
				if ((i + j) % 2 == 0)
					id[i][j] = A++;
				else
					id[i][j] = B++;
				total += arr[i][j];
			}
		}

		vector<vector<int>> adj(n*m + 2);
		for (int i = 0; i < n; ++i) {
			for (int j = 0; j < m; ++j) {
				if ((i + j) % 2 == 0) {
					adj[source].push_back(id[i][j]);
					adj[id[i][j]].push_back(source);
					capacity[source][id[i][j]] = arr[i][j];

					for (int k = 0; k < 4; ++k) {
						int row = i + dx[k];
						int col = j + dy[k];

						if ((row >= 0 && row < n) && (col >= 0 && col < m)) {
							adj[id[i][j]].push_back(A + id[row][col]);
							adj[A + id[row][col]].push_back(id[i][j]);
							capacity[id[i][j]][A + id[row][col]] = INF;
						}
					}
				}
				else {
					adj[A + id[i][j]].push_back(sink);
					adj[sink].push_back(A + id[i][j]);
					capacity[A + id[i][j]][sink] = arr[i][j];
				}
			}
		}

		//ford-fulkerson
		int maxFlow = 0;

		while (1) {
			vector<int> prev(n*m + 2, -1);
			queue<int> q;
			q.push(source);

			while (!q.empty()) {
				int current = q.front();
				q.pop();

				for (int next : adj[current]) {
					if (capacity[current][next] - flow[current][next] > 0 && prev[next] == -1) {
						q.push(next);
						prev[next] = current;
						if (next == sink)
							break;
					}
				}
				if (prev[sink] != -1)
					break;
			}

			if (prev[sink] == -1)
				break;

			int amount = INF;
			for (int i = sink; i != source; i = prev[i])
				amount = min(amount, capacity[prev[i]][i] - flow[prev[i]][i]);
			for (int i = sink; i != source; i = prev[i]) {
				flow[prev[i]][i] += amount;
				flow[i][prev[i]] -= amount;
			}

			maxFlow += amount;
		}

		printf("%d\n", total - maxFlow);
	}
}
