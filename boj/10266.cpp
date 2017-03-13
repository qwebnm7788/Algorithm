/*
10266 시계 사진들

환형시프트 문제이다.
주어진 시계는 바늘이 0~360000까지 돌아가는데 각 사진에서 바늘이 있는 부분을 o로 표시하고 아닌 부분을 x로 표시하게 되면
한 문자열을 시프트하여 다른 문자열로 만들 수 있는지 여부를 체크하는 문제로 바뀌게 된다.
*/
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
using namespace std;

const int MAX = 360000;

int main() {
	freopen("input.txt", "r", stdin);
	int n;
	cin >> n;

	string target, source;
	target = source = string(MAX, 'x');
	int temp, cnt = 0;
	while (cnt < n) {
		cin >> temp;
		target[temp] = 'o';
		cnt++;
	}
	cnt = 0;
	while (cnt < n) {
		cin >> temp;
		source[temp] = 'o';
		cnt++;
	}

	target = target + target;

	int targetSize = target.length();
	int sourceSize = source.length();

	vector<int> pi(sourceSize, 0);
	for (int i = 1, matched = 0; i < sourceSize; ++i) {
		if (matched > 0 && source[i] != source[matched]) matched = pi[matched - 1];
		if (source[i] == source[matched]) pi[i] = ++matched;
	}

	bool check = false;
	for (int i = 0, matched = 0; i < targetSize; ++i) {
		if (matched > 0 && target[i] != source[matched]) matched = pi[matched - 1];
		if (target[i] == source[matched]) {
			matched++;
			if (matched == sourceSize) {
				check = true;
				matched = pi[matched - 1];
			}
		}
	}
	if (check)
		cout << "possible";
	else
		cout << "impossible";
}