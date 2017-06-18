/*
12788번 제 2회 IUPC는 잘 개최될 수 있을까?

그리디로 가장 많은 펜을 가진 친구부터 나누어주면 된다.
*/
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main() {
	freopen("input.txt", "r", stdin);
	int n, m, k;
	cin >> n >> m >> k;
	m *= k;
	vector<int> pen(n);
	for (int i = 0; i < n; ++i) cin >> pen[i];
	sort(pen.begin(), pen.end());
	int ans = 0;
	for (int i = n - 1; i >= 0 && m > 0; --i) {
		m -= pen[i];
		ans++;
	}
	if (m > 0) cout << "STRESS";
	else cout << ans;
}