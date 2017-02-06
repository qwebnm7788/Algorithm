/*
758B - Blown Garland

1.
brute force
맨 처음 4개에 대해서 !가 주어지면 주어진 대로 혹은 이미 주어진 몇개의 알파벳이 있으면 그 상태를 이용해서
4개를 (원래의 구조를 훼손하지 않고) 재배치하면 그 뒤로는 쭉 알아낼 수 있다
이렇게 해서 만족하는 친구를 찾아주면 되는데 최악의 경우 맨 처음 4개가 !!!!이 되어서 4!개의 배치를 진행할 수있고
각 배치의 경우마다 O(n)의 검사를 해보아야 하므로

총 시간복잡도는 O(24n) ~= O(n)이 된다.
*/

/*
2.
Asymptotic behavior method

문제를 잘보면 4개의 연속되는 전구는 서로다른 전구여야 한다.
따라서 n번째 전구는 n-4번째 전구와 같은 종류가 되어야 함을 알 수 있다.

따라서 위치를 modulo 4 해서 같은 값이 나오는 친구들은 모두 같은 전구임을 알 수 있다.

이 방법은 사용가능한데 그 이유는 문제의 조건에서 각 전구들이 최소한 한번 이상씩 나오기 때문에
각자의 위치를 못 찾을 일은 없다.

Time complexcity = O(n)
*/

#include <iostream>
#include <string>
using namespace std;

int main(){
	string s;
	cin >> s;
	
	char bulb[4] = {};		//index[i] = modulo4 해서 i가 나온친구는 어떤 전구인가
	int ans['Y'+1] = {};
	for(int i = 0; i < s.length(); ++i){
		if(s[i] == '!')
			continue;
		bulb[i%4] = s[i];
	}
	
	for(int i = 0; i < s.length(); ++i){
		if(s[i]=='!')
			ans[bulb[i%4]]++;
	}
	
	cout << ans['R'] << " " << ans['B'] << " " << ans['Y'] << " " << ans['G'];
}