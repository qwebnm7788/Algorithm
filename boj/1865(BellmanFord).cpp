//음의 사이클이 있는지 여부만 우선 보면 된다. -> 왜냐면 있다면 그 사이클에 있는 친구를 시작정점으로 설정한다면 음의 사이클에서 무조건 시작정점으로 돌아올 수 있는
//친구가 있기 때문이다.

#include <iostream>
#include <vector>
using namespace std;

const int MAX_N = 500;
const int INF = 987654321;

vector<vector<pair<int, int>>> adj;

int main(int argc, char* argv[]) {
	ios_base::sync_with_stdio(false);
	freopen("input.txt", "r", stdin);
	int test;
	cin >> test;

	for (int z = 0; z < test; ++z) {
		int n, m, w;
		cin >> n >> m >> w;

		adj = vector<vector<pair<int, int>>>(n);

		int s, e, t;
		for (int i = 0; i < m; ++i) {
			cin >> s >> e >> t;
			adj[s - 1].push_back(make_pair(e - 1, t));
			adj[e - 1].push_back(make_pair(s - 1, t));
		}

		for (int i = 0; i < w; ++i) {
			cin >> s >> e >> t;
			adj[s - 1].push_back(make_pair(e - 1, -t));
		}

		bool check = false;

		int upper[MAX_N];
		for (int i = 0; i < n; ++i)
			upper[i] = INF;


		upper[0] = 0;
		for (int i = 0; i < n - 1; ++i) {
			for (int here = 0; here < n; ++here) {
				for (int j = 0; j < adj[here].size(); ++j) {
					int next = adj[here][j].first;
					int cost = adj[here][j].second;

					if (upper[next] > upper[here] + cost) {
						upper[next] = upper[here] + cost;
					}
				}
			}
		}

		for (int here = 0; here < n; ++here) {
			for (int i = 0; i < adj[here].size(); ++i) {
				int next = adj[here][i].first;
				int cost = adj[here][i].second;

				if (next == here)
					continue;

				if (upper[next] > upper[here] + cost) {
					check = true;
					break;
				}

			}
			if (check)
				break;
		}

		if (check)
			cout << "YES\n";
		else
			cout << "NO\n";
	}
}