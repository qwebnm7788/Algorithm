#include <iostream>
#include <string.h>
using namespace std;

const int MOD = 1000000007;

int n;
int cache[101];
//2*width 사각형을 채우는 방법의 수를 MOD로 나눈 나머지를 반환
int tiling(int width){
	//base case = width =1 일때  하나로 채울 수 있다.
	if(width <= 1) return 1;
	//memoization
	int& ret = cache[width];
	if(ret != -1) return ret;
	return ret = (tiling(width-1) + tiling(width-2)) % MOD;
}

int main(){
	int test;
	cin >> test;
	for(int z = 0; z < test; ++z){
		cin >> n;
		memset(cache, -1, sizeof(cache));
		cout << tiling(n) << endl;
	}
}