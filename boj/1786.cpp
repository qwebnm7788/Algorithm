/*
1786 찾기

KMP 알고리즘 예제문제
입력시 cin 으로 하면 화이트스페이스를 지나치게 되므로 한줄씩 입력받는 cin.getline을 사용해야한다.
*/
#include <iostream>
#include <vector>
#include <string>
#include <cstring>
#include <algorithm>
using namespace std;

const int MAX = 1000001;
char T[MAX], P[MAX];
int pi[MAX] = { 0 };

int main() {
	freopen("input.txt", "r", stdin);

	cin.getline(T, MAX);
	cin.getline(P, MAX);

	int n = strlen(T);
	int m = strlen(P);

	for (int i = 1, matched = 0; i < m; ++i) {
		if (matched > 0 && P[i] != P[matched]) matched = pi[matched - 1];
		if (P[i] == P[matched]) pi[i] = ++matched;
	}

	vector<int> ans;

	for (int i = 0, matched = 0; i < n; ++i) {
		if (matched > 0 && T[i] != P[matched]) matched = pi[matched - 1];
		if (T[i] == P[matched]) {
			matched++;
			if (matched == m) {
				ans.push_back(i - matched + 1);
				matched = pi[matched - 1];
			}
		}
	}

	cout << ans.size() << endl;
	for (int i = 0; i < ans.size(); ++i)
		cout << ans[i] + 1 << " ";
}