/*
1629번 곱셈

a,b,c가 INT_MAX까지 들어올 수 있을때
(a^b)%c를 구하는 문제이다.

여기서 그냥 naive하게 a^b을 for루프로 구하게 되면 O(b)가 되고 b는 2^31 ~~ 10^9 가량이 되므로
시간초과..?에 걸리게 된다. (곱셈이 느린 연산이라서 그런가..?)

그래서 a^b을 좀 더 빠르게 해보면
b가 홀수인 경우에는 a^b = a^(b/2) * a^(b/2)와 같으므로 왼쪽 절반의 결과를 얻으면
반대쪽 절반은 따로 계산할 필요가 없어짐을 알 수 있다.

따라서 O(logb)에 a^b을 구할 수 있게 된다. 이를 통해 시간초과를 해결해야 문제를 풀 수 있다.
*/
#include <iostream>
using namespace std;
//a^b
long long foo(int a, int b, int c) {
	if (b == 0) return 1;
	if (b % 2 == 1) return (a * foo(a, b - 1, c)) % c;
	else {
		long long temp = foo(a, b / 2, c);
		return (temp * temp) % c;
	}
}

int main() {
	int a, b, c;
	cin >> a >> b >> c;
	cout << foo(a, b,c);
}