#include <iostream>
#include <cstring>
#include <algorithm>
#include <limits>
using namespace std;

const int MAXN = 101;
const long long INF = 1e9 + 5;

long long memo[MAXN][MAXN];
char answer[MAXN + MAXN];
int n, m;
long long k;

//foo(a,z) 'a'가 a개 'z'가 z개 남았을때 만들 수 있는 문자열의 가짓수
//이때 주의해야 할 점은 a,z가 k의 최대값인 1e9개 보다 더 많이 만들어 낼 수 있기때문에
//1e9개 이상 넘어가면 그냥 1e9개로 커트해주고 sol에서 답을 찾게 해주자.
//즉 a,z의 조합으로는 long long의 표현범위를 넘어가는 수의 조합을 만들 수있지만
//물어보는 k가 1e9 이하이므로 그냥 1e9로 커트해준다.
long long foo(int a, int z) {
	if (a == 0 || z == 0) return 1;
	long long& ret = memo[a][z];
	if (ret != -1) return ret;
	ret = min(foo(a - 1, z) + foo(a, z - 1),INF);
	return ret;
}

//sol(a,z,found,x) = 'a'가 a개 'z'가 z개 남았을때 found번쨰의 친구를 찾는것 (x는 정답지정용)
void sol(int a, int z, long long found, int x) {
	//모든 경우에는 n+m자리의 문자가 되므로
	if (a == 0) {						//a를 다 썼을때는 남은 자리는 z로 채우면 되고
		for (; x < n + m; ++x) answer[x] = 'z';
		return;
	}
	if (z == 0) {						//z를 다 썼을때는 남은 자리는 a로 채우면 된다.
		for (; x < n + m; ++x) answer[x] = 'a';
		return;
	}
	long long temp = foo(a - 1, z);			//a를 선택했을때
	if (found <= temp) {					//found가 그것보다 작다면 지금 자리에서는 a를 고르는게 맞다.
		answer[x] = 'a';
		sol(a - 1, z, found, x + 1);
	}
	else {									//아니라면 z를 선택하고 found - temp개 만큼을 찾아준다.
		answer[x] = 'z';
		sol(a, z - 1, found - temp, x + 1);
	}
}

int main() {
	cin >> n >> m >> k;
	memset(memo, -1, sizeof(memo));
	long long test = foo(n, m);
	if (test < k) cout << "-1";
	else {
		sol(n, m, k, 0);
		for (int i = 0; i < n + m; ++i) cout << answer[i];
	}
}