/*
11375 열혈강호

이분매칭 연습문제
*/
#include <iostream>
#include <vector>
using namespace std;

vector<vector<int>> adj;
vector<int> aMatch, bMatch;
vector<bool> visited;

bool dfs(int a) {
	visited[a] = true;
	for (int b : adj[a]) {
		if (bMatch[b] == -1 || !visited[bMatch[b]] && dfs(bMatch[b])) {
			aMatch[a] = b;
			bMatch[b] = a;
			return true;
		}
	}
	return false;
}

int main() {
	ios_base::sync_with_stdio(false);

	int n, m;
	cin >> n >> m;

	adj.resize(n);
	aMatch.resize(n, -1);
	bMatch.resize(m, -1);

	int num, x;
	for (int i = 0; i < n; ++i) {
		cin >> num;
		for (int j = 0; j < num; ++j) {
			cin >> x;
			adj[i].push_back(x - 1);
		}
	}

	int ans = 0;
	for (int i = 0; i < n; ++i) {
		visited = vector<bool>(n, false);
		if (aMatch[i] == -1) {
			if (dfs(i))
				ans++;
		}
	}

	cout << ans;
}