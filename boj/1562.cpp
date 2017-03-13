/*
1562 계단수

단순한 dp였는데 방문정보를 저장해야하는 차이점이 있다.!!
visited배열을 이용하게 되면 메모이제이션을 구현할 수 없다. 왜냐면
모든 정보가 주어졌을때 그 정보를 다시 이용해야 되는데
visit으로 따로 저장하면 current와 select만으로는 매번 다른 정답을 구하게 된다.
따라서 한방에 저장해주어야 하는데 여기서는 숫자의 갯수가 10개니깐
비트마스크를 이용해서 답을 정해줄 수 있다. 1<<10 으로 cache를 3차원으로 구현해준다.

*/
#include <cstdio>
#include <string.h>
int n;
int cache[101][11][1<<10];
//현재까지 current개 골랐고	 현재 select를 골랐을때
//가능한 모든 계단수를 반환한다.
int foo(int current, int select, int visited){
	if(select > 9 || select < 0)
		return 0;
	if(current==n){
		if(visited == ((1<<10)-1))
			return 1;
		else
			return 0;
	}
	int& ret = cache[current][select][visited];
	if(ret != -1) return ret;
	ret = 0;
	ret += foo(current+1,select-1,visited|(1<<(select-1))) + foo(current+1,select+1,visited|(1<<(select+1)));
	ret %= 1000000000;
	return ret;
}

int main(){
	scanf("%d", &n);
	int ans = 0;
	memset(&cache,-1,sizeof(cache));
	for(int i = 1; i < 10; ++i){
		ans += foo(1,i,(1<<i));
		ans %= 1000000000;
	}
	printf("%d", ans);
}