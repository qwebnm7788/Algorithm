#include <iostream>
using namespace std;

const int MAXN = 31;

int cache[MAXN];

int main(){
	int n;
	cin >> n;
	cache[0] = 1;
	cache[1] = 0;
	cache[2] = 3;
	for(int i = 2; i <= n; i += 2){
		cache[i] = 3*cache[i-2];
		for(int j = 4; i - j >= 0; j += 2)
			cache[i] += 2 * cache[i-j];
	}
	cout << cache[n];
}
