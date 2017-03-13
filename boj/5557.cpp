/*
5557 1학년

다이나믹 프로그래밍.
*/
#include <iostream>
#include <string.h>
using namespace std;

int n;
int arr[101];
long long cache[101][21];

//cache[i][j] = i번까지 이용했을때 합이 j일때 나머지를 모두 이용했을때 arr[n-1]을 만들 수 있는 가짓수
//foo(index,current) = index까지 이용해서 합이 current일때 나머지를
//모두 더해서 얻을 수 있는 올바른 등식의 수를 반환한다.
int foo(int index, int current){
	//base case = 끝에 도달했을때 정답이면 1 아니면 0 을 반환한다.
	if(index == n-2){
		return (current == arr[n-1] ? 1 : 0);
	}

	//base case 2 = 중간에 값이 0 미만 20초과가 되면 안된다.
	if(current > 20 || current < 0)
		return 0;

	long long& ret = cache[index][current];
	if(ret != -1) return ret;

	ret = foo(index+1,current+arr[index+1]) + foo(index+1,current-arr[index+1]);
	return ret;
}
int main(){
	cin >> n;
	for(int i = 0; i < n; ++i)
		cin >> arr[i];
	memset(cache,-1,sizeof(cache));
	cout << foo(0,arr[0]);
}
