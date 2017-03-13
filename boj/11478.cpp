/*
11478
서로 다른 부분 문자열의 개수

suffix array를 고른후에
바로 인접한 친구들의 LCP를 계산하고 그 친구들은 중복된 것이므로 제거하면서
합계를 구해나가면 된다. 이 문제는 LCP를 O(N^2)에 구해도 성공한다고 함. (n = 1000 이므로)
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

	int h = 0, ans = 0;
	for(int i = 0; i < n; ++i){
		if(rank[i]){
			int j = suffixArray[rank[i]-1];
			while(s[i+h] == s[j+h]) h++;
			ans += s.length() - suffixArray[i] - h;
		}else{
			//rank[i] = 0인 경우에는 suffix array의 맨 처음 친구이니깐 그냥 그 글자수 그대로 접두사를 가지고 있는다
			//근데 이게 rank[i] = 0인 친구가 항상 S[0:]이 아니다. -> 즉 접미사배열의 맨 처음은 S[0:]이 아닐 수 있으니깐.
			//이렇게 중간에 들어가야 한다.
			ans += s.length() - suffixArray[i];
		}

		if(h) --h;
	}

	cout << ans;
}