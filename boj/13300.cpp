/*
13300 방배정

*/
#include <iostream>
using namespace std;

int arr[2][6];

int main() {
	freopen("input.txt", "r", stdin);

	int n, k;
	cin >> n >> k;

	int s, y;
	for (int i = 0; i < n; ++i) {
		cin >> s >> y;
		arr[s][y - 1]++;
	}

	int ans = 0;
	for (int i = 0; i < 2; ++i) {
		for (int j = 0; j < 6; ++j) {
			ans += arr[i][j] / k;
			if (arr[i][j] % k) ans++;
		}
	}
	cout << ans;
}