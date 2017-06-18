/*
2098 외판원 순회
*/
#include <iostream>
#include <cstring>
#include <algorithm>
using namespace std;

const int INF = 2e9;
const int SIZE = 16;

int N, W[SIZE][SIZE], cache[SIZE][1 << SIZE];

//현재 current도시에 있고 visited를 방문하였을때 모든 도시를 순회할때의 최소비용을 반환한다.
int foo(int current, int visited){
	int& ret = cache[current][visited];
	if(ret != -1) return ret;
	//base case -> 모든 도시를 방문하였을때
	if(visited == (1 << N) - 1){
		if(W[current][0] != 0) return W[current][0];			//0번 마을을 시작 마을이라고 보았다. -> 즉 돌아갈 수 있다면 그 비용을 반환한다.
		return INF;			//불가능하다면 엄청 큰 값을 줘서 선택되지 못하게 하자.
	}

	ret = INF;
	for(int i = 0; i < N; ++i){
		if((visited & (1 << i)) || W[current][i] == 0) continue;		//이미 방문했거나, current에서 갈 수 없는 도시라면 
		//i번 도시를 방문해보고 그 도시 방문비용이 지금까지의 최소인지를 본다.
		ret = min(ret, foo(i,visited | (1 << i)) + W[current][i]);
	}
	return ret;
}

int main(){
	cin >> N;
	for(int i = 0; i < N; ++i){
		for(int j = 0; j < N; ++j){
			cin >> W[i][j];
		}
	}

	memset(cache,-1,sizeof(cache));
	cout << foo(0,1);		//visited = 1은 000...01로 0번도시 방문을 표시한것이다.
}