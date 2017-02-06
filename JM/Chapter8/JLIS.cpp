#include <iostream>
#include <algorithm>
#include <limits>
using namespace std;

const long long LOW_MAX = numeric_limits<long long>::min();

int n, m;
int A[101], B[101];
int cache[101][101];			

int jlis(int indexA, int indexB) {
	int& ret = cache[indexA + 1][indexB + 1];
	if (ret != -1) return ret;
	ret = 2;
	long long a = (indexA == -1 ? LOW_MAX : A[indexA]);
	long long b = (indexB == -1 ? LOW_MAX : B[indexB]);
	long long maxVal = max(a, b);
	for (int i = indexA+1; i < n; ++i)
		if (A[i] > maxVal)
			ret = max(ret, jlis(i, indexB) + 1);

	for (int i = indexB + 1; i < m; ++i)
		if (B[i] > maxVal)
			ret = max(ret, jlis(indexA, i) + 1);
	return ret;
}

int main() {
	freopen("input.txt", "r", stdin);
	ios_base::sync_with_stdio(false);

	int test;
	cin >> test;

	for (int z = 0; z < test; ++z) {
		cin >> n >> m;

		for (int i = 0; i < n; ++i)
			cin >> A[i];
		for (int i = 0; i < m; ++i)
			cin >> B[i];

		for (int i = 0; i <= n; ++i)
			for (int j = 0; j <= m; ++j)
				cache[i][j] = -1;

		//jlis의 시작점을 -1로 하고 A[-1],B[-1]을 -INF로 둔 후에 풀게되면
		//밖에서 모든 시작 조합을 다 시도해 볼 필요가 없어진다. 게다가 이렇게는 어떻게 해야되는지 잘 모르겠다.
		//그런데 아마도 미래의 내가 시도해보려는 방법은 안된다. 왜냐면 그런 방식으로 하게 되면 첫번째 예제 케이스를 통과하지 못하는데
		/*
		왜냐면 1 2 4, 3 4 7 에서 정답은 1 2 3 4 7 이다 그런데 시작부터 A의 시작점과 B의 시작점을 잡고서 구현해놓은 jlis에 들어가게 되면
		첫번째 배열의 1,2를 선택하는 행동을 절대 해볼 수 없다. 왜냐면 이 책의 알고리즘은 잡아놓은 두 값중 더 큰 값보다 더 큰 친구를 다음번에 찾아들어가게 되는데
		그렇게 되면 처음 어떤 쌍을 골라서 2를 골라볼 수 없다.

		하지만 -1부터 시작하게 된다면 처음에는 A를 모두 다 시도해볼 수 있다. 왜냐면 -1일때 LOW_MAX로 설정했기 떄문이지
		즉 첫번째 B를 고정하고 A를 다 돌아볼때 A 자체의 LIS도 일부 찾아본다는 것이다.
		이 부분을 실행해줄 수 없기 때문에 -1부터 해주는것이 좋다.
		*/
		cout << jlis(-1, -1) - 2 << endl;			//또 맨처음 들어간 -1을 배열에 쑤셔넣기위해서 +1을 한 값으로 indexing을 해주었다. 그러니깐 cache배열을 초기화할때 cache[n-1][m-1]까지가 아니라 cache[n][m]까지 사용함을 알자.!!!

	}
}