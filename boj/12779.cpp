/*
12779 상품 is 뭔들
(B)

약수의 개수가 홀수개인 수는
n^2꼴의 수임을 이용한다. (왜냐면 자기자신이 2번 약수에 들어가기 때문!)

b와 a사이의 약수가 홀수개인 수는
sqrt(b) - sqrt(a)로 구할수 있다.
*/
#include <iostream>
#include <cmath>
using namespace std;

long long gcd(long long a, long long b) {
	if (b == 0) return a;
	return gcd(b, a%b);
}
int main() {
	freopen("input.txt", "r", stdin);
	long long a, b;
	cin >> a >> b;
	int ans = (int)sqrt(b) - (int)sqrt(a);
	long long x = gcd(b-a, ans);
	if (ans == 0) cout << "0";
	else cout << (ans / x) << "/" << (b - a) / x;
}