/*
12786번 INHA SUIT

D[i][j][k] = i번 나무의 j번 높이의 구멍에 k번의 T연산을 이용하여 도달했을때 마지막 나무까지 사용하는 최소의 t연산의 수 라고 하자

D[i][j][k] = D[i+1][j+1][k], D[i+1][j][k], D[i+1][j-1][k], D[i+1][2*j][k](이때 j가 10이상이면 20으로 고정), D[i+1][가능한 모든 구멍][k+1]중 min값을 찾아주면 된다.

처음 시작이 1이고 1번나무부터 비교해야 함에 주의한다.
*/
#include <iostream>
#include <cstring>
#include <algorithm>
using namespace std;

const int MAXN = 101;
const int MAXM = 21;
const int MAXT = 51;
const int INF = 2e9;

bool tree[MAXN][MAXM];
int cache[MAXN][MAXM][MAXT];
int n, k;

int foo(int current, int height, int t) {
	if (t > k) return INF;
	if (current == n) return 0;
	int& ret = cache[current][height][t];
	if (ret != -1) return ret;
	ret = INF;
	if (tree[current + 1][height + 1])
		ret = foo(current + 1, height + 1, t);
	if (tree[current + 1][height - 1])
		ret = min(ret, foo(current + 1, height - 1, t));
	if (tree[current + 1][height])
		ret = min(ret, foo(current + 1, height, t));

	if (tree[current + 1][(height >= 10 ? 20 : 2 * height)])
		ret = min(ret, foo(current + 1, (height >= 10 ? 20 : 2 * height), t));
	for (int i = 0; i < MAXM; ++i) {
		if (tree[current + 1][i]) ret = min(ret, foo(current + 1, i, t + 1) + 1);
	}
	return ret;
}
int main() {
	freopen("input.txt", "r", stdin);
	cin >> n >> k;
	int cnt, x;
	for (int i = 1; i <= n; ++i) {
		cin >> cnt;
		for (int j = 0; j < cnt; ++j) {
			cin >> x;
			tree[i][x] = true;
		}
	}
	memset(cache, -1, sizeof(cache));
	int ans = foo(0,1,0);
	if (ans == INF) cout << "-1";
	else cout << ans;
}