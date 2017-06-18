/*
11578번 팀원모집

N,M제한이 매우 작기 때문에 비트마스크를 이용하여 냅색문제를 풀듯이 풀어주면 된다.

foo(current,T) = 현재 current번 학생을 기준으로 잡고(항상 다음번 커지는 순번의 학생을 잡는다), T는 지금까지 푼 문제를 비트로 표현한다.(i번 문제를 풀었다면 i-1번 비트가 1이된다.)

foo(current, T) = min(foo(current+1,T),foo(current+1,T에 current가 풀수있는문제 추가) + 1) 가 된다.

base case는 모든문제를 다풀었다면 성공이고 그렇지 못하고 마지막 친구까지를 돌았다면 INF를 준다.
*/
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

const int MAXN = 11;
const int INF = 2e9;

int n, m, cnt;
vector<vector<int>> student(n);

int foo(int current, int T) {
	if (T == ((1 << n) - 1)) return 0;
	if (current == m) return INF;
	int ret = foo(current + 1, T);
	for (int i = 0; i < student[current].size(); ++i)
		T |= (1 << (student[current][i] - 1));
	ret = min(ret, foo(current + 1, T) + 1);
	return ret;
}

int main() {
	freopen("input.txt", "r", stdin);
	cin >> n >> m;
	student.resize(m);
	for (int i = 0; i < m; ++i) {
		cin >> cnt;
		student[i].resize(cnt);
		for (int j = 0; j < cnt; ++j) cin >> student[i][j];
	}
	int ans = foo(0, 0);
	if (ans > m) cout << "-1";
	else cout << ans;
}