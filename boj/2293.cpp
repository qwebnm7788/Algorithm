/*
2293 동전1

동전이 사용되는 것의 순서는 무시해야 하므로 특정한 입력을 강제하여
중복되는 것을 세지 않도록 하였다. 즉 [k][x]라고 한다면 0~k번 동전을 사용하여 x원을 만드는 방법으로 설정했다.

여기서 시간은 지수승으로 증가하기 때문에(?) 다이나믹 프로그래밍을 이용하기 위해 2차원 테이블을 만들면
4MB의 메모리 제한에 걸리게 된다.

하지만 [k][x] = [k-1][x] + [k-1][x-i*coin[i]] (i >= 1, k번 동전을 사용한 수)로 정의할 수 있으므로
매번 [k][x]는 바로직전의 [k-1]의 값만을 참조한다는 것을 이용하여
[2][MAXK]의 테이블로 줄일 수 있다.
*/
#include <iostream>
#include <string.h>
using namespace std;

const int MAXN = 101;
const int MAXK = 10005;

int coin[MAXN];
int cache[2][MAXK];

int main() {
	freopen("input.txt", "r", stdin);
	int n, k;
	cin >> n >> k;
	for (int i = 0; i < n; ++i) cin >> coin[i];
	
	//처음에는 [0]번 동전으로 만들 수 있는 수는 [0]번 동전의 배수인 값이다.
	for (int i = 0; i*coin[0] <= k; ++i) {
		cache[0][i*coin[0]] = 1;
	}

	for (int i = 1; i < n; ++i) {
		//여기서 [i%2][k]만을 구해주는 것이 아닌 k이하의 모든 j에 대해 [i%2][j]를 구해주어야 한다.
		//왜냐면 [(i-1)%2][k-l*coin[i]]연산에서 k-l*coin[i]는 k이하로 떨어지기 때문!
		for (int j = 0; j <= k; ++j) {
			cache[i % 2][j] = cache[(i - 1) % 2][j];
			for (int l = 1; l*coin[i] <= j; ++l) {
				cache[i % 2][j] += cache[(i - 1) % 2][j - l*coin[i]];
			}
		}
	}
	cout << cache[(n-1) % 2][k];
}