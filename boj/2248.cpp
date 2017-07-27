/*
가능한 최대의 자리수는 31자리이고 31 31 2^31이 들어오는것이 최대의 경우의 수가 된다.
2^31 -1 이 아닌 2^31인 이유는 00000000000000000000000000000000이 첫번째(1)로 매겨지기 때문이다
따라서 입력에서 마지막 i가 int형의 범위를 1만큼 벗어날 수 있기 때문에 이에 조심하여
long long 형태로 받아주어야 한다.
*/
#include <iostream>
#include <cstring>
#include <algorithm>
using namespace std;

const int MAXN = 32;
const int MAXL = 32;

int memo[MAXN][MAXL];
char answer[MAXN];

//foo(n,l) = n자리 이진수 중 1의 개수가 l이하인 이진수의 갯수
int foo(int n, int l) {
	if (n == 0 || l == 0) return 1;
	int& ret = memo[n][l];
	if (ret != -1) return ret;
	ret = foo(n - 1, l);			//n번째 자리가 0 인 경우
	if (l) ret += foo(n - 1, l - 1);			//n번째 자리가 1인경우
	return ret;
}

//sol(n,l,found,index) = n자리 이진수 중 1의개수가 l개이하인 이진수 중 (크기순으로 볼때) found번에 오는 이진수
void sol(int n, int l, long long found, int index) {
	if (l < 0) return;
	if (n == 0) {
		for (; index < n; ++index) answer[index] = '0';
		return;
	}
	int temp = foo(n-1, l);				//N번째 수가 0인 경우
	if (found <= temp) {				//보다 적다면 N번째 수는 0인 친구일 꺼야		(크기 순이므로 0부터 먼저 검사하자)
		answer[index] = '0';
		sol(n - 1, l, found, index + 1);
	}
	else {							//그게 아니면 N번째 수는 1이다.
		answer[index] = '1';
		sol(n - 1, l - 1, found - temp, index + 1);
	}
}
int main() {
	int n, l;
	long long i;
	cin >> n >> l >> i;
	memset(memo, -1, sizeof(memo));
	sol(n, l, i, 0);
	for (int i = 0; i < n; ++i) cout << answer[i];
}