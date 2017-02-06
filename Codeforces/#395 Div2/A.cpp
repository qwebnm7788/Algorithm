#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main(){
	int n,m,z;
	cin >> n >> m >> z;
	int cnt = 0;
	vector<bool> check(z+1);
	for(int i = n; i <= z; i += n)
		check[i] = true;
	for(int i = m; i <= z; i += m)
		if(check[i])
			cnt++;
	cout << cnt;
}