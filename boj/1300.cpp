/*
1300 k번째 수
n^2의 크기로 배열을 실제 생성하는 것에는 무리가 있다.
따라서 답을 한번씩 던져보면서 성립하는지의 여부를 확인하는 parametric search를 이용한다.

이분탐색을 통해 어떤 수 x에 대해 x-1이하의 수는 k개 '미만'이 존재하고
x이하의 수는 k개 '이상'이 존재한다면 x는 k번째 수임을 알 수 있다. (x와 동일한 값이 있더러도 만족시키기 위해서는)

이때 x-1이하의 수나 x이하의 수의 갯수를 확인하는 방법은 i행의 값들에 대해서 min(x/i, n)이 되는데
i행의 값들은 모두 i의 배수와 같다. 또한 index가 1부터 시작한다고 하였으므로 1*i, 2*i, 3*i ...으로 진행된다.
따라서 x를 i로 나눈다면 1,2,3과 같은 어떠한 수가 된다. (정수 나눗셈이므로 항상 성립되는 값으로 내림이 된다.)
index가 1부터 시작하였으므로 그냥 그 값 자체가 x보다 작은 수의 갯수와 같다. (i행에서의)
이때 i행의 총 갯수인 n개를 넘어갈 수 있으므로 적절히 scaling 해준다.
*/
#include <iostream>
#include <algorithm>
using namespace std;

const int MAXN = 1e5;

int main() {
	long long n, k;
	cin >> n >> k;
	long long lo = 0, hi = MAXN*MAXN;
	while (lo + 1 < hi) {
		long long mid = (lo + hi) / 2;
		long long cnt = 0;
		for (long long i = 1; i <= n; ++i) cnt += min(mid / i, n);
		if (cnt >= k) hi = mid;
		else lo = mid;
	}
	cout << hi;
}