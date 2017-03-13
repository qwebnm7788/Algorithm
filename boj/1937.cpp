/*
1937 욕심쟁이 판다

정해는 DFS + DP인것 같다. [row][col]에서 dfs를 돌리면서 값을 갱신해주면 된다.
즉 모든 점에서 dfs를 돌려주면 된다. 모든 점에서 dfs를 돌리므로 O(N^2)번 DFS를 돌려야 한다.
DFS가 약 O(4N)정도 걸리므로 O(N^3)정도 걸리고 DP로 처리해주게 되면 O(N^2)정도에 들어올 것 같다.

내가 푼 방식은 BFS를 이용했는데 visited를 따로 관리해주어서 좀 느리다.
visited를 관리해주지 않아도 되는 이유는 다음과 같다.
-> [row][col]에서 이동할 수 있는 칸은 arr[row][col]보다는 값이 큰 쪽이다 그렇게 되면
이제 그 점을 [x][y]라 한다면 arr[row][col] < arr[x][y]라는 의미인데 이제 x,y점에서 보게 되면
이전의 점은 돌아갈 수 없는 점이 된다. arr[x][y] > arr[row][col]로 주어진 조건이 성립하지 않기 때문.
이때 주의할 점은 매번 루프마다 초기화를 하게되면 나처럼 visited를 따로 관리해 주지 않는 이상은 중복계산을 계속하게 된다.

한번 [row][col]점이 계산되었다면 다음부터는 하지 않게끔 처리를 해준다면 visited를 따로 만들 필요가 없다.
(즉 한번 계산한 점은 그 값이 그냥 정답이라고 한다.)
*/
#include <iostream>
#include <string.h>
#include <algorithm>
using namespace std;

const int MAXN = 501;

int n;
int arr[MAXN][MAXN], cache[MAXN][MAXN][4];
bool visited[MAXN][MAXN];

int cnt = 0;
//현재 [row][col]에 before 방향에서 왔다면 판다가 생존할 수 있는 최대의 일 수를 반환한다. (before = 1,2,3,4 위,오른,아래,왼 순이다.
int foo(int row, int col, int before) {
	int& ret = cache[row][col][before];
	if (cache[row][col][before] != -1) return ret;
	visited[row][col] = true;
	ret = 1;
	if (row > 0 && !visited[row-1][col] && arr[row][col] < arr[row-1][col])
		ret = max(ret, foo(row - 1, col, 3) + 1);
	if (row < n - 1 && !visited[row+1][col] && arr[row][col] < arr[row+1][col])
		ret = max(ret, foo(row + 1, col, 1) + 1);
	if (col > 0 && !visited[row][col-1] && arr[row][col] < arr[row][col-1])
		ret = max(ret, foo(row, col - 1, 2) + 1);
	if (col < n - 1 && !visited[row][col+1] && arr[row][col] < arr[row][col+1])
		ret = max(ret, foo(row, col + 1, 4) + 1);
	visited[row][col] = false;
	return ret;
}

int main() {
	freopen("input.txt", "r", stdin);

	memset(cache, -1, sizeof(cache));

	cin >> n;
	for (int i = 0; i < n; ++i)
		for (int j = 0; j < n; ++j)
			cin >> arr[i][j];

	int ans = -1;
	for (int i = 0; i < n; ++i) {
		for (int j = 0; j < n; ++j) {
			for (int k = 0; k < 4; ++k)
				ans = max(ans, foo(i, j, k + 1));
		}
	}
	cout << ans;
}