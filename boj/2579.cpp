/*
2579 계단오르기

dp,
3번째 계단을 계산하기 전에 3번임을 찾아야하므로 base case의 순서도 중요
그리고 안되는 경우 -1을 리턴하면 안된다. (완전 작은값을 반환) -> 중간에 -1한 친구가 다시 살아나 버릴수있다.
*/
#include <iostream>
#include <string.h>
#include <algorithm>
using namespace std;

const int INF = 987654321;
int n;
int cache[301][3];
int arr[301];

//foo(current,count) = current까지 count 개를 연속으로 밟았을때 얻을 수 있는 총 점수의 최대값을 반환한다.
int foo(int current, int count){
	if(current > n || count >= 3)
		return -INF;
	if(current == n)
		return arr[current];
	int& ret = cache[current][count];
	if(ret != -1) return ret;
	return ret = max(foo(current+1,count+1),foo(current+2,1)) + arr[current];
}

int main(){
	cin >> n;
	for(int i = 1; i <= n; ++i)
		cin >> arr[i];
	memset(&cache,-1,sizeof(cache));
	cout << foo(0,0);
}