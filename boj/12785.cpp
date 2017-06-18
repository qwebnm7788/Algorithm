/*
12785번 토쟁이의 등굣길

조합을 이용하여 한 점에서 격자상의 경로를 통해
목표지점까지의 경로로 가는 최단거리의 수를 이용한다.

(시작점 ~ 토스트가게) X (토스트가게 ~ 도착점)으로 구할 수 있다.

여기서 격자상에서는 조합의 수만을 확인하기 때문에
(토스트가게 ~ 도착점)을 평행이동하여 (원점 ~ 평행이동한 도착점)으로 변형하여 풀 수 있다.
*/
#include <iostream>
#include <algorithm>
using namespace std;

const int MAX = 205;
const int MOD = 1000007;

int arr[MAX][MAX];

int main() {
	freopen("input.txt", "r", stdin);
	int w, h, x, y;
	cin >> w >> h >> x >> y;
	for (int i = 0; i < w; ++i) arr[0][i] = 1;
	for (int i = 0; i < h; ++i) arr[i][0] = 1;

	for (int i = 1; i < h; ++i) {
		for (int j = 1; j < w; ++j) {
			arr[i][j] = (arr[i - 1][j] + arr[i][j - 1]) % MOD;
		}
	}

	long long ans = arr[y - 1][x - 1];
	ans = (ans * arr[h - y][w - x]) % MOD;
	cout << ans;
}