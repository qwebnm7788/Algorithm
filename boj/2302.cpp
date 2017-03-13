/*
2302 극장좌석

손으로 계산해보면 배열하는 가짓수는 피보나치 수열로 구할 수 있음을 알 수 있다.
따라서 vip좌석을 기준으로 뭉텅이를 나누어서 모든 수의 곱을 구하면 원하는 답을 얻는다.

밑에 구한 방법은 해답에 있는 방식으로
foo(index) = index번 자리까지 앉혔을때 얻을 수 있는 배열의 수 라고 정의한다. (arr[:index]까지)
index번 친구가 앉을 수 있는 방법은
1) index자리에 그냥 앉는경우 -> 이땐 foo(index-1)에 +1을 한것과 답이 같다.
2) index-1번 자리에 앉는경우 -> 이땐 index-1번 주인은 index번에 와서 앉아야 한다. 따라서 foo(index-2)에 +1을 한것과 같다.

따라서 foo(index) = foo(index-1) + foo(index-2) 가 정답이 된다.

여기서는 vip자리에 따른 예외처리를 적절히 해주면 된다.
지금이 vip이지 않도록 main에서 적당한 처리를 해주었다.
*/
#include <iostream>
#include <string.h>
using namespace std;

const int MAXN = 41;

bool vip[MAXN];
long long cache[MAXN];

long long foo(int index){
	long long& ret = cache[index];
	if(ret != -1) return ret;
	if(index == 0) return 1;
	if(index == 1) return (vip[index-1] ? 1 : 2);
	if(vip[index-1]) return 1;
	if(vip[index-2]) return 2;
	ret = 0;
	return ret = foo(index-1) + foo(index-2);
}

int main(){
	int n,m,x;
	cin >> n >> m;

	memset(cache,-1,sizeof(cache));

	long long ans = 1;
	for(int i = 0; i < m; ++i){
		cin >> x;
		x--;
		if(x && !vip[x-1])
			ans *= foo(x-1);
		vip[x] = true;
	}

	if(!vip[n-1])
		ans *= foo(n-1);

	cout << ans;
}
