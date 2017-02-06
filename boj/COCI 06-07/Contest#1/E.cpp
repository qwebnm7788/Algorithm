/*
비트마스크를 이용한 dp문제이다.
TSP문제와 비슷하게 생각해주면 되는데 TSP는 최단거리이고 이 친구는 최장거리를 생각해보면된다.

dp[i] != -1 을 이미 계산된점인것으로 체크를 해주려고 했는데
그렇게 하면 안되고 check라는 배열을 따로 만들어서 해야 된다.; 왜인지는 잘 모르겠네 아마 부동소수점 오차 인듯 싶다. 아니면 내가 잘못
*/

#include <cstdio>
#include <algorithm>
using namespace std;

int n;
int arr[21][21];
double dp[1 << 21];
bool check[1 << 21];

//visited인 상태에서 here에 왔을때 모든 미션을 완수했을때 성공확률을 반환한다.
double foo(int here, int visited) {
	//기저사례 : n명의 친구들이 모두 미션을 수행했을때
	if (here == n)
		return 1.0;

	double& ret = dp[visited];
	//이미 이러한 조합으로는 진행해보았을경우에는 계산해놓은 값을 반환한다.
	if (check[visited])
		return ret;
	check[visited] = true;
	ret = 0.0;
	for (int i = 0; i < n; ++i) {
		//이미 수행한 미션은 거르고
		if ((visited & (1 << i)))
			continue;
		//수행해보지 않은 i번 미션을 here친구가 수행하고 here+1번째 친구는 i번을 수행했다고 표시한 후에 그결과를 받으면 된다.
		ret = max(ret, arr[here][i]*0.01 * foo(here + 1, visited | (1 << i)));
	}
	return ret;
}

int main() {
	freopen("input.txt", "r", stdin);

	scanf("%d", &n);
	for (int i = 0; i < n; ++i) {
		for (int j = 0; j < n; ++j) {
			scanf("%d", &arr[i][j]);
			dp[i] = -1;
		}
	}
	//원하는 값은 퍼센트이므로 100을 곱해준다.
	printf("%f\n", foo(0, 0)*100);

}