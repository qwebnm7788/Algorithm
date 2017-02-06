/*
747A Display Size
문제 -> (b>=a) 일때 a는 row b는 col을 이용해서 a*b = n을 만족시키는 b-a를 최소화하는 a,b를 찾는것

editorial 
a의 값을 i = 1~n을 돌면서 하나씩 다 해보면 되는데 여기서 a*b = n을 만족시켜야 하므로
n mod i = 0인지를 체크해주어야 하고 
abs(i-n/i)가 이미 찾아놓은 b-a보다 작은지를 체크해서 작다면 a,b의 값을 최신화 시키는 방법으로 진행한다.
Time Complexcity -> O(N)

i가 <= n까지 돌아야 한다. < n하면 안돼 ..ㅜㅜ
*/

#include <iostream>
#include <algorithm>
using namespace std;

const int INF = 987654321;

int main(){
	int a,b;
	a = 0;
	b = INF;
	int n;
	cin >> n;

	for(int i = 1; i <= n; ++i){
		//i*(n/i) == n으로 체크해주어도 되고
		//n mod i == 0으로 체크해도 된다.
		if(i*(n/i) == n){
			//그래서 지금 찾은 값이 기존의 값의 차이 보다 작다면
			//최신화 시켜주면 된다.
			if(max(n/i,i)-min(n/i,i) < b-a){
				b = max(n/i,i);
				a = min(n/i,i);	
			}
		}
	}

	cout << a << " " << b;
}