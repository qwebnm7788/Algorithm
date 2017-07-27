#include <iostream>
#include <cstring>
#include <algorithm>
using namespace std;

const int MAXN = 101;
const int INF = 2e9;

int memo[MAXN][MAXN];
int cost[MAXN][MAXN];
int number[MAXN];

int foo(int index, int left) {
	if (left == 0) return 0;
	if (left < 0 || index < 0)
		return -INF;
	int& ret = memo[index][left];
	if (ret != -1) return ret;
	ret = foo(index-1,left);
	for (int j = index; j >= 0; --j) {
		ret = max(ret, foo(j - 2, left - 1) + cost[j][index]);
	}
	return ret;
}

int main() {
	ios_base::sync_with_stdio(false);
	int n, m;
	cin >> n >> m;

	for (int i = 0; i < n; ++i) cin >> number[i];

	for (int i = 0; i < n; ++i) {
		cost[i][i] = number[i];
		for (int j = i + 1; j < n; ++j) {
			cost[i][j] = cost[i][j - 1] + number[j];
		}
	}

	memset(memo, -1, sizeof(memo));
	cout << foo(n - 1, m);
}
