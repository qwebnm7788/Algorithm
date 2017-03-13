/*
5398 틀렸습니다

JM북의 예시 문제와 비슷하게 접근해주면된다.
각 자리에 id를 매겨주면 각 정점에 대해서 가로/세로 정점이 하나씩 생기는 이분그래프가 된다. (문제의 조건에서 가로끼리,세로끼리는 중복되지 않으므로)
이분그래프를 형성할때 주의할 점은 예시 데이터의 SOLUTION 와 LEIDEN 이 그렇듯이 L이 겹치는 경우는 둘중 하나가 아닌 둘 다 가능하다는 것이다.
이땐 둘을 이어주지 않아야지 둘중 하나만 고르는 일이 생기지 않는다. 따라서 실제로 글자를 비교해보는 과정이 필요하다
-> 가로 글자를 모두 입력받은 상태에서 세로 글자를 입력받을때 이미 그 곳이 가로 글자가 있는 곳이고 글자가 나와 다른 경우만 둘을 이어준다.
-> 즉 위의 L같은 경우는 서로 이어지지 않는다.

이렇게 해서 구해준 최대매칭의 수는 정점에서 가로/세로 둘 중 하나만 선택되어야 되는 단어의 갯수와 같다.

따라서 가로,세로 단어의 수를 합한다음 최대매칭의 수를 빼주면 둘이 겹친 부분을 빼준것이 되어 원하는 답이 된다.
*/
#include <iostream>
#include <vector>
#include <string>
#include <string.h>
#include <algorithm>
using namespace std;

const int MAX = 2001;

vector<vector<int>> adj;
vector<int> aMatch, bMatch;
vector<bool> visited;
int id[MAX][MAX];
char arr[MAX][MAX];

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
	ios_base::sync_with_stdio(false);
	freopen("input.txt", "r", stdin);

	int test;
	cin >> test;
	for (int z = 0; z < test; ++z) {
		int n, m;
		cin >> n >> m;
		
		adj.clear();
		memset(id, -1, sizeof(id));
		memset(arr, '\0', sizeof(arr));
		int row, col;
		string x;

		for (int i = 0; i < n; ++i) {
			cin >> col >> row >> x;
			for (int j = col; j < col + x.length(); ++j) {
				arr[row][j] = x[j-col];
				if(id[row][j] == -1)
					id[row][j] = i;
			}
		}

		adj.resize(n);

		for (int i = 0; i < m; ++i) {
			cin >> col >> row >> x;
			for (int j = row; j < row + x.length(); ++j) {
				if (arr[j][col] != x[j - row] && id[j][col] != -1) {
					adj[id[j][col]].push_back(i);
				}
			}
		}

		int ans = 0;
		aMatch = vector<int>(n, -1);
		bMatch = vector<int>(m, -1);
		for (int i = 0; i < n; ++i) {
			if (aMatch[i] == -1) {
				visited = vector<bool>(n, false);
				if (dfs(i)) ans++;
			}
		}

		cout << n + m - ans << endl;
	}
}