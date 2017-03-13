/*
1633 최고의 팀 만들기

foo(index, wSelected, bSelected) = index번 이전까지 백=wSelected, 흑=bSelected명이 골라졌을때 만들 수 있는 최고의 팀의 점수를 반환한다.
foo(index, wSelected, bSelected) = max(index번 선수가 백으로 출전, 흑으로 출전, 출전X) 와 같다.
*/

#include <iostream>
#include <vector>
#include <algorithm>
#include <string.h>
using namespace std;

const int MAXN = 1001;
const int INF = 987654321;

vector<pair<int, int>> arr;				//(백,흑)의 점수

int cache[MAXN][16][16];

int foo(int index, int wSelected, int bSelected) {
	if (wSelected == 15 && bSelected == 15) return 0;
	if (index == arr.size() || wSelected > 15 || bSelected > 15) return -INF;
	int& ret = cache[index][wSelected][bSelected];
	if (ret != -1) return ret;
	ret = foo(index + 1, wSelected, bSelected);
	ret = max(ret, foo(index + 1, wSelected + 1, bSelected) + arr[index].first);
	ret = max(ret, foo(index + 1, wSelected, bSelected + 1) + arr[index].second);
	if (ret < 0) ret = 0;			//세가지 모두 불가능한 경우에는 -INF를 반환하게 하였다. -> 꼭 없어도 될듯;
	return ret;
}
int main() {
	freopen("input.txt", "r", stdin);
	int a, b;
	while (cin >> a >> b) arr.push_back(make_pair(a, b));
	memset(cache, -1, sizeof(cache));
	cout << foo(0, 0, 0);
}