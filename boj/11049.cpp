/*
11049 행렬곱셈순서

//[a,b]사이의 값 k를 정해서 foo(a,k) + foo(k+1,b) + 왼쪽 행렬과 오른쪽 행렬의 곱셈연산을 시도해 보면 된다.
//이때 왼쪽 행렬의 행(row)는 항상 a번 행렬의 행(row)이 되고 오른쪽행렬의 행(row)은 항상 k+1번 행렬의 행(row), 열(col)은 b번째 행렬의 열(col)이 됨을 이용해준다.

*/
#include <iostream>
#include <string.h>
#include <algorithm>
using namespace std;

const int MAXN = 505;
const int INF = 987654321;

pair<int, int> arr[MAXN];
long long cache[MAXN][MAXN];

//a번 ~ b번 행렬까지 곱해서 얻는 최소의 곱셈연산 횟수
long long foo(int a, int b) {
	if (a == b) return 0;			//base case -> a == b 그냥 하나의 행렬이므로 0
	if (b - a == 1) return arr[a].first * arr[b].first * arr[b].second;		//-> 2개의 행렬곱은 그대로 계산해준다.
	long long& ret = cache[a][b];
	if (ret != -1) return ret;
	ret = INF;
	for (int i = a; i <= b; ++i)			//모든 경우를 시도
		ret = min(ret, foo(a, i) + foo(i + 1, b) + arr[a].first * arr[i + 1].first * arr[b].second);
	return ret;
}

int main() {
	freopen("input.txt", "r", stdin);
	int n;
	cin >> n;
	for (int i = 0; i < n; ++i)
		cin >> arr[i].first >> arr[i].second;
	memset(cache, -1, sizeof(cache));
	cout << foo(0, n - 1);
}