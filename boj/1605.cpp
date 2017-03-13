/*
1605 반복 부분문자열

2번 이상 등장한 부분문자열중에 최장길이를 반환해야 되는데
suffix array에서 바로 직전 친구들을 비교하면서 (LCP array를 만들면서) LCP중 가장 큰 값이 구하는 결과가 된다.
왜냐면 LCP를 구하는 순간 이전 친구와 내가 공통된 접두사가 있다는 의미이고 그 말을 두번 이상 등장했다는 것이된다.
또한 모든 접두사에 대해서 구할 수 있기 때문에 모든 문자열을 체크할 수 있따.
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
	int l;
	cin >> l;

	string s;
	cin >> s;

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