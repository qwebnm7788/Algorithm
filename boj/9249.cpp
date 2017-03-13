/*
9249 최장 공통 부분 문자열

5582번 문제와 같고
그냥 이번엔 LCS를 출력해주면 된다.
구한 index에서 LCP값의 길이만큼 slicing하면 된다.
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
		:group(gT), t(tT) {}
	bool operator()(int a, int b){
		if(group[a] != group[b]) return group[a] < group[b];
		return group[a+t] < group[b+t];
	}
};

int main(){
	string a,b;
	cin >> a >> b;

	string c = a + "#" + b;

	int n = c.length();
	int t = 1;

	vector<int> suffixArray(n), group(n+1), tempGroup(n+1);

	for(int i = 0; i < n; ++i){
		suffixArray[i] = i;
		group[i] = c[i];
	}
	group[n] = tempGroup[n] = -1;

	while(t <= n){
		Comparator comp(group,t);
		sort(suffixArray.begin(),suffixArray.end(),comp);

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

	vector<int> LCP(n),rank(n);
	for(int i = 0; i < n; ++i)
		rank[suffixArray[i]] = i;

	int h = 0, len = 0;
	string lcs = "";
	for(int i = 0; i < n; ++i){
		if(rank[i]){
			int j = suffixArray[rank[i]-1];
			while(c[i+h] == c[j+h]) h++;
			LCP[i] = h;
			if((i < a.length() && j > a.length()) || (i > a.length() && j < a.length())){
				if(h > len){
					len = h;
					lcs = c.substr(i,h);
				}
			}
		}
		if(h) h--;
	}
	cout << len << endl << lcs;
}