/*
13301 타일 장식물

각 i번째 정사각형의 한 변의 길이는 피보나치 수열을 이룸을 알 수 있다.
그리고 N번째 까지의 사각형의 둘레의 합은 N번째 사각형의 한 변이 전체사각형의 한변을 이루고
N-1번째 사각형과 N번째 사각형의 합이 다른 한 변을 이루게 됨을 알 수 있다.
*/
#include <iostream>
#include <algorithm>
using namespace std;

const int MAXN = 85;

long long cache[MAXN];

//num번째 사각형의 변의 길이를 반환한다.
long long foo(int num) {
	if (num == 0 || num == 1) return 1;
	long long& ret = cache[num];
	if (ret != -1) return ret;
	return ret = foo(num - 1) + foo(num - 2);
}

int main() {
	int n;
	cin >> n;
	fill(cache, cache + n, -1);
	n--;
	if (n == 0) cout << "4";		//4;;
	else
		cout << (foo(n - 1) + 2 * foo(n)) * 2;
}