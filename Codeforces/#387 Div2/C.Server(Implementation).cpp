/*
server[i]를 i번 서버가 free가 될때 까지 남은 시간이라고 하자
그리고 나서 매번 query가 올때마다 server 배열을 돌면서 이 친구가 실행가능한지 여부를 보자
만약에 free server가 k개 보다 적다면 -1을 출력하면 되고 된다면 그 번호를 다 더해서 출력해주면 된다.
또 되는경우에는 그 server[i]에 t+d를 더해주면 된다. -> 왜냐면 t~t+d-1까지 occupy될것이고 t+d부터는 free가 될꺼니깐!
이때 for문을 사용하는데 낮은 번호부터 O(N)만에 돌아볼수있다.!
총 q개의 query가 오고 매 루프마다 O(n)을 돌아야 하므로

총 시간복잡도는 O(nq)가 될꺼야

*/

#include <iostream>
#include <algorithm>
using namespace std;

int server[101];		//처음은 0초부터 모두 available하므로 초기화된 상태로 가면 된다.

int main(){
	int n,q;
	cin >> n >> q;

	int t,k,d;
	int cnt = 0;
	int ans = 0;
	for(int i = 0; i < q; ++i){
		ans = cnt = 0;
		cin >> t >> k >> d;
		for(int j = 0; j < n; ++j){
			if(server[j]<=t)
				cnt++;
		}
		if(cnt >= k){
			for(int j = 0; j< n; ++j){
				if(server[j]<=t){
					k--;
					ans += j+1;
					server[j] = t+d;
					if(k==0)
						break;
				}
			}
			cout << ans << endl;
		}else{
			cout << "-1\n";
		}
	}



}