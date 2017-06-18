/*
14501번 퇴사

모든 경우에 대해서 가능한 경우를 따져주면 되므로 다이나믹 프로그래밍을 이용하면 된다.

foo(day) = [day:]일에 대해서 적절한 선택을 하였을때 얻을 수 있는 최대의 수익을 반환한다.
이렇게 되면 foo(day) = max(foo(day+1), foo(day+period[day]) + cost[day])임을 알 수 있다
즉 day의 상담을 선택하지 않거나, 선택하였을때 중 더 큰 수익을 얻는 것을 고르면 된다.

주의할 점은 1일이 걸린다면 day 당일에 종료가 됨을 의미한다는 것이다.
마지막 n번째 일에 하는 일이 1일이 걸린다면 그것또한 할 수 있는 일임을 잘 처리해주자.
(day + time[day])를 하면 >= n이 되어 항상 안된다고 표시하는 식으로 짜면 이 경우를 세주지 못한다.

또한 time이라는 전역변수를 사용하면 중복되는 이름으로 컴파일 에러가 생긴다.
*/
#include <iostream>
#include <string.h>
#include <algorithm>
using namespace std;

const int MAXN = 15;

int period[MAXN], cost[MAXN], cache[MAXN];
int n;

int foo(int day){
	if (day >= n) return 0;
	int& ret = cache[day];
	if (ret != -1) return ret;
	ret = 0;
	if (day + 1 < n) ret = max(ret, foo(day + 1));
	if (day + period[day] <= n) ret = max(ret, foo(day + period[day]) + cost[day]);
	return ret;
}

int main() {
	freopen("input.txt", "r", stdin);
	cin >> n;
	for (int i = 0; i < n; ++i)
		cin >> period[i] >> cost[i];
	memset(cache, -1, sizeof(cache));
	cout << foo(0);
}