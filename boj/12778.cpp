/*
12778 CTP공국으로 이민 가자
(A)

아스키코드를 이용하여
문자 -> 정수
정수 -> 문자 로 변환하면 된다.
*/
#include <iostream>
using namespace std;

int main() {
	freopen("input.txt", "r", stdin);
	int test;
	cin >> test;
	while (test--) {
		int m,n;
		char q,t;
		cin >> m >> q;
		for (int i = 0; i < m; ++i) {
			if (q == 'C') {
				cin >> t;
				cout << t - 'A' + 1 << " ";
			}
			else {
				cin >> n;
				cout << (char)(n + 'A' - 1) << " ";
			}
		}
		cout << endl;
	}
}