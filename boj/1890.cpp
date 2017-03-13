/*
1890 점프

오른쪽으로 가는 방법, 아래로 가는 방법 중 최소값을 가져가면 된다.

dp[i][j] = (i,j)에서 오른쪽/아래로 이동하여 오른쪽 맨아래에 도달하는데 가능한 경로의 수
dp[i][j] = min(dp[i][j+arr[i][j]], dp[i+arr[i][j]][j]) 가 된다.
*/
#include <iostream>
#include <string.h>
#include <algorithm>
using namespace std;

const int MAXN = 101;

long long arr[MAXN][MAXN], cache[MAXN][MAXN];
int n;

//arr[row][col]에서 오른쪽 아래까지 가는 경로의 수.
long long foo(int row, int col) {
	if (row < 0 || row >= n || col < 0 || col >= n) return 0;
	if (row == n - 1 && col == n - 1) return 1;

	long long& ret = cache[row][col];
	if (ret != -1) return ret;
	ret = 0;
	ret += foo(row, col + arr[row][col]);
	ret += foo(row + arr[row][col], col);
	return ret;
}
int main() {
	freopen("input.txt", "r", stdin);

	cin >> n;
	for (int i = 0; i < n; ++i) {
		for (int j = 0; j < n; ++j) {
			cin >> arr[i][j];
		}
	}

	memset(cache, -1, sizeof(cache));
	cout << foo(0, 0);
}
