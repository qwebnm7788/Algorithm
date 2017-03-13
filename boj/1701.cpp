/*
1701 Cube Editor

suffix array로 처리한 후에 LCP를 구해주면서 최대값을 출력하면 된다.
왜 KMP로 안풀렸는지 잘 모르겠다. ㅜㅜ
*/
#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
using namespace std;

struct Comparator {
	const vector<int>& group;
	int t;
	Comparator(const vector<int>& gT, int tT)
		:group(gT), t(tT) {}
	bool operator()(int a, int b){
		if(group[a] != group[b]) return group[a] < group[b];
		return group[a+t] < group[b+t];
	}
};

int main(){
	string s;
	cin >> s;

	int l = s.length();

	vector<int> suffixArray(l), group(l+1), tempGroup(l+1);
	int t = 1;
	for(int i = 0; i < l; ++i){
		suffixArray[i] = i;
		group[i] = s[i];
	}	
	group[l] = tempGroup[l] = -1;
	while(t <= l){
		Comparator comp(group,t);
		sort(suffixArray.begin(),suffixArray.end(),comp);

		t *= 2;
		if(t >= l) break;
		tempGroup[suffixArray[0]] = 0;
		for(int i = 1; i < l; ++i){
			if(comp(suffixArray[i-1],suffixArray[i]))
				tempGroup[suffixArray[i]] = tempGroup[suffixArray[i-1]] + 1;
			else
				tempGroup[suffixArray[i]] = tempGroup[suffixArray[i-1]];
		}
		group = tempGroup;
	}

	vector<int> rank(l);
	for(int i = 0; i < l; ++i)
		rank[suffixArray[i]] = i;

	int ans = 0, h = 0;
	for(int i = 0; i < l; ++i){
		if(rank[i]){
			int j = suffixArray[rank[i]-1];
			while(s[i+h] == s[j+h]) h++;
			ans = max(ans,h);
		}
		if(h) h--;
	}
	cout << ans;
}