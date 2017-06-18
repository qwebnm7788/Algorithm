/*
12780번 원피스
(C)

모든 자리에 대해서 가능한지 여부를 완전탐색으로 풀어주면 된다.
O(HN)이 되어 시간내에 충분히 풀 수 있다.
*/
#include <iostream>
#include <string>
using namespace std;

int main() {
	freopen("input.txt", "r", stdin);
	string h, n;
	cin >> h >> n;
	int hLen = h.length();
	int nLen = n.length();
	int ans = 0;
	bool check;
	for (int i = 0; i < hLen; ++i) {
		check = true;
		for (int j = 0; j < nLen; ++j) {
			if (h[i + j] != n[j]) {
				check = false;
				break;
			}
		}
		if (check) ans++;
	}
	cout << ans;
}