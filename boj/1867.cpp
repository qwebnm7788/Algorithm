/*
1867 돌멩이 제거

책에 있는 비숍문제와 거의 동일한 문제이다. 돌멩이가 있는 지점을 가로로,세로로 각각 돌멩이를 제거할 수 있으므로
가로,세로 두부분으로 나누어보자. 가로와 세로를 각각 다른 방식으로 번호를 매겨놓게 되면
모든 돌멩이가 있는 지점은 가로, 세로가 각각 대응되는 2가지로 표현이 된다. 그 자리의 2가지 표현을 각각 대응시켜놓게 되면

이분그래프로 나누어서 표현이 가능하고 이때의 최대매칭을 해주게 되면 가로와 세로를 최대한 많이 매칭되게 만들어서 돌멩이를 최대한으로 제거하게 된다.
즉 매칭의 수가 제거되는 돌멩이의 수와 같다. (각 점은 가로,세로의 한쌍으로 표현되기 때문에 한 쌍이 돌멩이 한개가 된다.)
*/
#include <iostream>
#include <string.h>
#include <vector>
#include <algorithm>
using namespace std;

const int MAXN = 501;

char arr[MAXN][MAXN];
int id[2][MAXN][MAXN];
vector<vector<int>> adj;
vector<int> aMatch, bMatch;
vector<bool> visited;

bool dfs(int a) {
	if (visited[a]) return false;
	visited[a] = true;
	for (int b : adj[a]) {
		if (bMatch[b] == -1 || dfs(bMatch[b])) {
			aMatch[a] = b;
			bMatch[b] = a;
			return true;
		}
	}
	return false;
}

int main() {
	freopen("input.txt", "r", stdin);

	int n, k;
	cin >> n >> k;

	int row, col;
	for (int i = 0; i < k; ++i) {
		cin >> row >> col;
		arr[row - 1][col - 1] = 'X';
	}

	memset(id, -1, sizeof(id));

	int aSize = 0, bSize = 0;
	//k = 0 (aSize)-> horizontal, k = 1 (bSize)-> vertical
	for (int k = 0; k < 2; ++k) {
		for (int i = 0; i < n; ++i) {
			for (int j = 0; j < n; ++j) {
				if (id[k][i][j] == -1 && arr[i][j] == 'X') {
					if (k == 0) {
						id[k][i][j] = aSize++;
						for (int z = 0; z < n; ++z)
							id[k][i][z] = id[k][i][j];
					}
					else {
						id[k][i][j] = bSize++;
						for (int z = 0; z < n; ++z)
							id[k][z][j] = id[k][i][j];
					}
				}
			}
		}
	}

	adj.resize(aSize);
	for (int i = 0; i < n; ++i) {
		for (int j = 0; j < n; ++j) {
			if (arr[i][j] == 'X')
				adj[id[0][i][j]].push_back(id[1][i][j]);
		}
	}

	aMatch.resize(aSize, -1);
	bMatch.resize(bSize, -1);
	int ans = 0;
	for (int i = 0; i < aSize; ++i) {
		if (aMatch[i] == -1) {
			visited = vector<bool>(aSize, false);
			if (dfs(i))
				ans++;
		}
	}

	cout << ans;
}