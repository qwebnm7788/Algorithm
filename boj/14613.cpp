#include <iostream>
#include <algorithm>
#include <iomanip>

using namespace std;

const int MAXN = 21;
double prob[MAXN][MAXN][MAXN][MAXN];

int main() {
	ios_base::sync_with_stdio(false);
	double W, L, D;
	cin >> W >> L >> D;

	prob[0][0][0][0] = 1;
	prob[1][1][0][0] = W;
	prob[1][0][1][0] = L;
	prob[1][0][0][1] = D;

	for (int i = 2; i <= 20; ++i) {
		for (int w = 0; w <= i; ++w) {
			for (int l = 0; l <= i; ++l) {
				for (int d = 0; d <= i; ++d) {
					if (w + l + d != i) continue;
					if (w >= 1)
						prob[i][w][l][d] += W*prob[i - 1][w - 1][l][d];
					if (l >= 1)
						prob[i][w][l][d] += L*prob[i - 1][w][l - 1][d];
					if (d >= 1)
						prob[i][w][l][d] += D*prob[i - 1][w][l][d - 1];
				}
			}
		}
	}

	double ans[5] = { 0.0, };
	for (int w = 0; w <= 20; ++w) {
		for (int l = 0; l <= 20; ++l) {
			for (int d = 0; d <= 20; ++d) {
				if (w + l + d != 20) continue;
				else {
					int total = 2000 + 50 * (w - l);
					if (total >= 3000)
						ans[4] += prob[20][w][l][d];
					else if (total >= 2500)
						ans[3] += prob[20][w][l][d];
					else if (total >= 2000)
						ans[2] += prob[20][w][l][d];
					else if (total >= 1500)
						ans[1] += prob[20][w][l][d];
					else
						ans[0] += prob[20][w][l][d];
				}
			}
		}
	}

	for (int i = 0; i < 5; ++i)
		cout << fixed << setprecision(8) << ans[i] << endl;
}