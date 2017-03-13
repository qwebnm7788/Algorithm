/*
11376 열혈강호 2

사람 한명을 분신을 하나 만들어서 2*N명이 되도록 한 뒤에 용량을 1씩 갖도록 해주면
최대 2개의 일을 할수 있는 상황을 만들어 줄 수 있다.

주의할 점은 2*i, 2*i+1로 쪼개두었을때 만약 i번 친구가 2가지 일을 할 수 있다면 2*i도 2가지 일을 모두 할 수 있고
분신인 2*i+1 또한 2가지 일을 동시에 할 수 있다. (한명당 하나씩만 해주면 안된다. -> 그렇게 되면 나는 1번일 분신은 2번일만 하는 꼴이 되니깐.)
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

	adj.resize(2 * n);
	aMatch.resize(2 * n, -1);
	bMatch.resize(m, -1);

	int num, x;
	for (int i = 0; i < n; ++i) {
		cin >> num;
		for (int j = 0; j < num; ++j) {
			cin >> x;
			adj[2 * i].push_back(x - 1);
			adj[2 * i + 1].push_back(x - 1);
		}
	}

	int ans = 0;
	for (int i = 0; i < 2 * n; ++i) {
		visited = vector<bool>(2 * n, false);
		if (aMatch[i] == -1) {
			if (dfs(i))
				ans++;
		}
	}

	cout << ans;
}