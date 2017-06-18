/*
9084번 동전


D[i][j] = 0~i번 동전을 이용하여 j원을 만드는 가짓수라고 하면
D[i][j+coin[i]*k] += D[i-1][j]와 같다.

다른방법으로는
D[i] = i원을 만드는 가짓수 라고 정의한 후.
D[i] = D[i] + D[i-coin[j]]으로 구한다.
이때 coin에 대해서 나중에 돌아주어야 하는데
그 이유는 입력이 오름차순으로 들어오기 때문에 낮은 액면가의 동전으로 먼저 모든 가짓수를 계산한 후에 다음것으로 넘어가서 계산해주어야 중복되는 경우를 제외할 수 있다.

(예를 들면 )
*/
#include <iostream>
#include <cstring>
#include <algorithm>
using namespace std;

const int MAXN = 21;
const int MAXM = 100001;

int coin[MAXN];
int cache[MAXN][MAXM];

int main() {
	int test;
	cin >> test;
	while (test--) {
		int n, m;
		cin >> n;
		for (int i = 0; i < n; ++i) cin >> coin[i];
		cin >> m;

		memset(cache, 0, sizeof(cache));

		for (int i = 0; coin[0]*i <= m; ++i) cache[0][coin[0] * i] = 1;

		for (int i = 1; i < n; ++i) {
			for (int j = 0; j <= m; ++j) {
				if (cache[i - 1][j] == 0) continue;
				for (int k = 0; j+coin[i]*k <= m; ++k) {
					cache[i][j + coin[i] * k] += cache[i - 1][j];
				}
			}
		}

		cout << cache[n - 1][m] << endl;
	}
}

//2nd version
#include <iostream>
#include <cstring>
#include <algorithm>
using namespace std;

const int MAXN = 21;
const int MAXM = 100001;

int coin[MAXN];
int cache[MAXM];

int main() {
	freopen("input.txt", "r", stdin);
	int test;
	cin >> test;
	while (test--) {
		int n, m;
		cin >> n;
		for (int i = 0; i < n; ++i) cin >> coin[i];
		cin >> m;

		memset(cache, 0, sizeof(cache));

		cache[0] = 1;
		for (int i = 0; i < n; ++i) {
			for (int j = 0; j <= m; ++j) {
				if(j-coin[i]>=0)
					cache[j] += cache[j - coin[i]];
			}
		}
		cout << cache[m] << endl;
	}
}