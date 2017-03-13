/*
13302 리조트

가능한 모든 방법을 시도해보면서 최적의 해를 찾으면 된다.
특정 날의 쿠폰갯수를 유지하면서 해주면 중복된 계산을 피할 수 있다.
dp[day][coupon] = day번째 날에 coupon 개의 쿠폰을 가질때 남아있는 갈 수 있는 모든 날을 갈때 드는 최소의 비용
dp[day][coupon] = min(쿠폰을 쓴날, 1일권, 3일권, 5일권, 가지못하는 날일때) 로 계산한다.
*/
#include <iostream>
#include <string.h>
#include <algorithm>
using namespace std;

const int INF = 987654321;
const int MAXN = 101;
const int MAXC = 41;
const int buy[3] = { 1,3,5 };
const int give[3] = { 0,1,2 };
const int price[3] = { 10000,25000,37000 };

int n, m, x;
bool impossible[MAXN];
int cache[MAXN][MAXC];

int foo(int day, int coupon) {
	if (day >= n) return 0;
	int& ret = cache[day][coupon];
	if (ret != -1) return ret;
	if (impossible[day]) return ret = foo(day + 1, coupon);

	ret = INF;
	for(int i = 0; i < 3; ++i)
		ret = min(ret, foo(day + buy[i], coupon + give[i]) + price[i]);
	
	if (coupon >= 3) ret = min(ret, foo(day + 1, coupon - 3));

	return ret;
}

int main() {
	freopen("input.txt", "r", stdin);
	cin >> n >> m;
	for (int i = 0; i < m; ++i) {
		cin >> x;
		impossible[x-1] = true;
	}
	memset(cache, -1, sizeof(cache));
	cout << foo(0, 0);
}