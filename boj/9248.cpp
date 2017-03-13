/*
9248 suffix array
suffix array 와 LCP 기본문제이다.
그런데 LCP를 O(n^2)이 아니라 O(N)에 구해주어야지 TLE를 맞지 않는다.
으아.ㅇ레ㅐㅁㄴ에ㅐㄹ뭉ㄴ
*/
#include <iostream>
#include <string>
#include <vector>
using namespace std;

struct Comparator {
	const vector<int>& group;
	int t;
	Comparator(const vector<int>& groupT, int tT)
		:group(groupT), t(tT) {}
	bool operator()(int a, int b) {
		if (group[a] != group[b]) return group[a] < group[b];
		return group[a + t] < group[b + t];
	}
};

int main() {
	ios_base::sync_with_stdio(false);

	freopen("input.txt", "r", stdin);
	string s;
	cin >> s;

	int n = s.length();
	int t = 1;
	vector<int> suffixArray(n), group(n + 1), tempGroup(n + 1);
	for (int i = 0; i < n; ++i) {
		suffixArray[i] = i;
		group[i] = s[i];
	}
	group[n] = tempGroup[n] = -1;
	while (t <= n) {
		Comparator comp(group, t);
		sort(suffixArray.begin(), suffixArray.end(), comp);

		t *= 2;
		tempGroup[suffixArray[0]] = 0;
		for (int i = 1; i < n; ++i) {
			if (comp(suffixArray[i-1],suffixArray[i]))
				tempGroup[suffixArray[i]] = tempGroup[suffixArray[i - 1]] + 1;
			else
				tempGroup[suffixArray[i]] = tempGroup[suffixArray[i - 1]];
		}
		group = tempGroup;
	}

	vector<int> LCP(n), rank(n, 0);

	for (int i = 0; i < n; ++i)
		rank[suffixArray[i]] = i;

	int len = 0;
	for (int i = 0; i < n; ++i) {
		int k = rank[i];
		if (k == 0) continue;
		int j = suffixArray[k - 1];
		while (s[i + len] == s[j + len])len++;
		LCP[k] = len;
		if (len) len--;
	}
	for (int i = 0; i < n; ++i)
		printf("%d ", suffixArray[i] + 1);
	printf("\nx ");
	for (int i = 1; i < n; ++i)
		printf("%d ", LCP[i]);
}