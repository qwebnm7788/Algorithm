/*
1351 무한수열
지수승으로 n이 감소하기 때문에 테이블에 존재하는 수는 별로 없다.
입력 n의 크기가 매우커서 배열 생성에는 제한이 있으므로
map을 이용한 다이나믹프로그래밍을 사용한다.
*/

#include <iostream>
#include <map>
using namespace std;

map<long long, long long> m;

long long n, p, q;

long long foo(long long i) {
	if (i == 0) return 1;
	if (m.count(i) == 1) return m[i];
	else {
		m.insert(make_pair(i, foo(i / p) + foo(i / q)));
		return m[i];
	}
}
int main() {
	freopen("input.txt", "r", stdin);
	cin >> n >> p >> q;
	cout << foo(n);
}