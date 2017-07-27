//
// Created by jaewon on 2017-06-19.
//

#include <iostream>
using namespace std;

int main(){
    ios_base::sync_with_stdio(false);
    freopen("input.txt","r",stdin);
	int l,p,v;
	int test_case = 0;
	while(cin >> l >> p >> v){
		if(l == 0 && p == 0 && v == 0) break;
		test_case++;
		int answer = (v / p) * l;
        answer += ( v % p >= l ? l : v % p);
		cout << "Case " << test_case << ": " << answer << endl;
	}
}