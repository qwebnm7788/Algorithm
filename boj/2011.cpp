/*
2011 암호코드

cache[n] = n자리의 수를 암호화 하는 방법의 가짓수
cache[n] = cache[n-1] + cache[n-2] (n번째 자리를 한자리로 읽는 경우 + 두자리로 읽는 경우)
이때 한자리로 읽기 위해서는 그 자리수는 '0'이면 안되고
두자리로 읽기 위해서는 10 ~ 26 사이의 수여야 한다.

0이 입력되는 경우는 불가능하므로 0을 출력해야 한다.
*/

#include <iostream>
#include <string>
using namespace std;

const int MAX = 5001;
const int MOD = 1000000;

int cache[MAX];

int main() {
	string in;
	cin >> in;
	int len = in.length();
	cache[0] = cache[1] = 1;
	for (int i = 2; i <= len; ++i) {
		if (in[i - 1] != '0') cache[i] = cache[i - 1];
		if (stoi(in.substr(i - 2, 2)) <= 26 && stoi(in.substr(i-2,2)) >= 10) cache[i] += cache[i - 2];
		cache[i] %= MOD;
	}
	if (len == 1 && in == "0") cout << "0";
	else cout << cache[len];
}