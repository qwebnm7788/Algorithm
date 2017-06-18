/*
1049번 기타줄


모든 경우를 다 시도해 보면 되는데 각 브랜드에서는 밑에 명시된 4가지의 경우들이 있게된다.
지수적으로 경우의 수가 증가하므로..?
여기에 메모이제이션을 적용해준다.
foo(index,current) = 0-index번 브랜드를 이용하여 현재 current개의 기타줄이 있을때 적어도 N개의 기타줄을 사는 최소의 비용이라고 하자.
그렇게 되면 
1.index번 브랜드에서 하나도 사지 않는 경우
2.패키지만 사는경우
3.낱개만 사는경우
4.패키지와 낱개를 조합하여 사는 경우가 있다.

1~4는 모두 2중 for루프를 이용하여 한번에 표현할 수 있다.

또한 그리디하게 가장 가격이 저렴한 패키지 가격과 낱개가격을 찾아준 다음
패키지 + 낱개 로 사는 법, 전부 패키지로 사는법(남더라도), 전부 낱개로 사는 법 중
가장 저렴한 것을 출력해주어도 된다.
*/
#include <iostream>
#include <cstring>
#include <algorithm>
using namespace std;

const int MAXN = 101;
const int MAXM = 51;
const int SIZE = 2;
const int INF = 2e9;

int cost[MAXN][SIZE];			//cost[i][k] = i번 브랜드의 [0] = 패키지 가격, [1] = 낱개 가격
int cache[MAXM][MAXN];
int n, m;

//foo(index,current) = 0~index번 브랜드를 이용하여 현재 current개의 기타줄이 있을때 적어도 N개 이상의 기타줄을 사는데
//드는 최소의 비용
int foo(int index, int current) {
	if (current >= n) return 0;
	if (index == m) return INF;

	int& ret = cache[index][current];
	if (ret != -1) return ret;
	ret = INF;
	for (int i = 0; ; ++i) {
		for (int j = 0; ; ++j) {
			ret = min(ret, foo(index + 1, current + (6 * i + j)) + cost[index][0] * i + cost[index][1] * j);
			if (current + (6 * i + j) >= n) break;
		}
		if (current + 6 * i >= n) break;
	}

	return ret;
}

int main() {
	freopen("input.txt", "r", stdin);
	cin >> n >> m;
	for (int i = 0; i < m; ++i) cin >> cost[i][0] >> cost[i][1];
	memset(cache, -1, sizeof(cache));
	cout << foo(0, 0);
}

//greedy solution
#include <iostream>
#include <algorithm>
using namespace std;

int main() {
	int n, m;
	cin >> n >> m;

	int a, b, package, individual;
	package = individual = 1005;
	for (int i = 0; i < m; ++i) {
		cin >> a >> b;
		package = min(package, a);
		individual = min(individual, b);
	}

	int ans = (n / 6 + ((n % 6) != 0))*package;
	ans = min(ans, min(n*individual, (n / 6)*package + (n % 6)*individual));
	cout << ans;
}