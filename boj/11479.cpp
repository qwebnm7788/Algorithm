/*
11479
서로 다른 부분 문자열의 개수 2

11478과 같지만 그때는 LCP를 O(N^2)에 구해도 되지만
여기서는 O(N)에 구해야 한다. 또한 부분문자열의 수가 int형의 범위를 넘어갈 수 있다.
왜냐면 가능한 모든 부분 문자열의 수는 ...? 뭐지 N!은 아닌데 (알파벳의 수때문에)

*/
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
using namespace std;

struct Comparator {
	const vector<int>& group;
	int t;
	Comparator(const vector<int>& gT, int tT)
		: t(tT), group(gT) {}
	bool operator()(int a, int b){
		if(group[a] != group[b]) return group[a] < group[b];
		return group[a+t] < group[b+t];
	}
};

int main(){
	string s;
	cin >> s;

	int n = s.length();
	int t = 1;

	vector<int> suffixArray(n), group(n+1), tempGroup(n+1);
	for(int i = 0; i < n; ++i){
		suffixArray[i] = i;
		group[i] = s[i];
	}
	group[n] = tempGroup[n] = -1;

	while(t < n){
		Comparator comp(group,t);
		sort(suffixArray.begin(), suffixArray.end(), comp);

		t *= 2;
		if(t >= n) break;

		tempGroup[suffixArray[0]] = 0;
		for(int i = 1; i < n; ++i){
			if(comp(suffixArray[i-1],suffixArray[i]))
				tempGroup[suffixArray[i]] = tempGroup[suffixArray[i-1]] + 1;
			else
				tempGroup[suffixArray[i]] = tempGroup[suffixArray[i-1]];
		}
		group = tempGroup;
	}

	vector<int> rank(n);
	for(int i = 0; i < n; ++i)
		rank[suffixArray[i]] = i;

	long long h = 0, ans = 0;
	for(int i = 0; i < n; ++i){
		if(rank[i]){
			int j = suffixArray[rank[i]-1];
			while(s[i+h] == s[j+h]) h++;
			ans += s.length() - suffixArray[i] - h;
		}else
			ans += s.length() - suffixArray[i];

		if(h) --h;
	}

	cout << ans;
}