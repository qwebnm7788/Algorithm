/*
1495번 기타리스트

dp[i][j] = i번 곡을 j 볼륨으로 연주하는 것이 가능하면 1 아니면 0을 둔다.

dp[i+1][j+P[i]] = dp[i][j] (dp[i][j] != 0 요게 없으면 덮어씌울 수 있음)
dp[i+1][j-P[i]] = dp[i][j] (dp[i][j] != 0)


혹은 거꾸로
dp[i][j] = dp[i-1][j+P[i-1]] + dp[i-1][j-P[i-1]] 으로도 표현할 수 있다.
*/
#include <iostream>
#include <algorithm>
using namespace std;

const int MAXN = 101;
const int MAXM = 1001;

int dp[MAXN][MAXM];
int P[MAXN];

int main() {
	int n, s, m;
	cin >> n >> s >> m;
	for (int i = 0; i < n; ++i) cin >> P[i];

	dp[0][s] = 1;
	for (int i = 0; i < n; ++i) {
		for (int j = 0; j <= m; ++j) {
			if (dp[i][j] == 1) {
				if (j + P[i] <= m)
					dp[i + 1][j + P[i]] = dp[i][j];
				if (j - P[i] >= 0)
					dp[i + 1][j - P[i]] = dp[i][j];
			}
		}
	}

	/*
	dp[0][s] = 1;
	for (int i = 1; i <= n; ++i) {
	for (int j = 0; j <= m; ++j) {
	if (j + P[i - 1] <= m)
	dp[i][j] = max(dp[i][j], dp[i - 1][j + P[i - 1]]);
	if (j - P[i - 1] >= 0)
	dp[i][j] = max(dp[i][j], dp[i - 1][j - P[i - 1]]);
	}
	}
	*/
	int ans = -1;
	for (int i = 0; i <= m; ++i) {
		if (dp[n][i] == 1) ans = i;
	}
	cout << ans;
}
