/*
747B - Mammoth's Genome Decoding
A,C,G,T,? 로 이루어진 문자열이 주어지는데
A,C,G,T의 갯수가 전부 합쳐서 n개인데 각각의 것들이 동일한 갯수로 존재하여야 한다.

editorial
n개로 이루어진 문자열이므로 A,C,G,T가 모두 같은 개수를 가지려면 n/4개씩을 가지게 하면 된다.
즉 n mod 4 != 0 이라면 절대로 만들수 없으니깐 no sol
그리고 이미 n/4개 보다 많이 가진 친구가 있어도 no sol이다.
이 두 조건을 만족한다면 항상 답을 만들 수 있다. -> ?로 대체해주면서

이제 주어진 문자열을 돌면서 ?를 부족한 A,C,G,T의 갯수만큼 대체해주면 된다.
*/

#include <iostream>
#include <string>
using namespace std;

int main(){
	int n;
	cin >> n;

	string s;
	cin >> s;

	if(n%4 !=0){
		cout << "===";
		return 0;
	}

	int a = n/4, c = n/4, g = n/4, t = n/4;

	for(int i = 0; i < n; ++i){
		if(s[i]=='A')
			a--;
		else if(s[i]=='C')
			c--;
		else if(s[i]=='G')
			g--;
		else if(s[i]=='T')
			t--;
	}


	if( (a < 0) || (c < 0) || (g < 0) || (t < 0) ){
		cout << "===";
		return 0;
	}

	for(int i = 0; i < n; ++i){
		if(s[i]=='?'){
			if(a){
				s[i] = 'A';
				a--;
			}else if(c){
				s[i] = 'C';
				c--;
			}else if(g){
				s[i] = 'G';
				g--;
			}else{
				s[i] = 'T';
				t--;
			}
		}
	}
	cout << s;
}