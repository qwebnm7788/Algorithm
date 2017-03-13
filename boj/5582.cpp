/*
5582 공통 부분 문자열

http://www.roman10.net/2012/03/16/suffix-array-part-3-longest-common-substring-lcs/
http://lpcs.math.msu.su/~pritykin/csr2008presentations/starikovskaya.pdf
http://cs.stackexchange.com/questions/9555/computing-the-longest-common-substring-of-two-strings-using-suffix-arrays ->댓글 보고 본문 수정하고 보기
LCS를 구하는 문제이다.
다이나믹 프로그래밍으로 구하는 것이 가장 간단하다.

LCS (longest common substring)
아이디어는 LCS는 두 문자열의 suffix들의 LCP와 같다는 것이다.
왜냐면 우선 각 문자열의 sufifx array를 구하게 되면 모든 substring을 다룰 수 있고
그렇게 된 상태에서 두 문자열의 suffix array를 비교해서 LCP를 얻으면 둘의 각각의 부분문자열 중에 가장 긴 prefix를 찾게 된다.
그러면 그거 자체가 LCS가 된다...

둘을 한꺼번에 suffix array로 만들어서 보자.
우선 두 문자열을 #,$등의 문자를 이용해서 붙여준다. 이때 이러한 char의 조건은
양 문자열에 등장하지 않는 친구여야 하고 등장하는 char 모두에 대해서 가장 작은 코드값을 가져서 정렬하면
제일 앞에 오도록 해주어야 한다.


그 다음에 LCP를 얻어주면 되는데 이 때 주의할 점은 이렇게 한방에 만든 suffix array는 물론 두 문자열을 모두 합쳐서 얻을 수 있는
부분문자열(substring)을 모두 이용해서 비교할 수 있지만 common이라는 조건을 무시할 수 있다는 것이다.
즉 ababab와 ccc를 합쳐서 ababab#ccc가 되어서 LCP를 찾으면 ab를 찾게 된다는 것이지. 근데 이것은 ccc에는 포함되지 않으니깐 LCS가 아니야
그냥 ababab 자체의 LCP와 같다.

따라서 LCP[i]는 SA[i-1]과 SA[i]사이에서 구한 값임을 인지하고 구별하기 위해서는
이 SA[i-1]과 SA[i]가 서로 다른 문자열의 suffix이라는 사실일때만 LCS를 구하는 과정의 일환임을 아는것이다.
그래야지만 common 속성을 맞춰줄 수 있다.

#을 넣은 이유는 suffix를 생성해내고 정렬하게 되면 그냥 둘을 이어붙여서 suffix를 구하게 되면 둘을 이어서 만든 substring도 사이사이에 들어가서
정렬할때 끼워지게 된다. 만약 #같은 정렬의 우선순위가 가장 작은 친구들이 앞에 선다면 #을 기준으로 첫번째 문자열의 부분문자열, 두번째 문자열의 부분문자열로 나뉠수 있다.
../? 사실 잘 모르겠다.

어쨋든 이렇게 SA[i-1]가 SA[i]가 서로 다른 문자열에 속함은 #을 넣은 위치를 알면 간단하다.
SA[i-1]과 SA[i]가 #을 가운데라고 했을때  SA[i-1] # SA[i] 이거나 SA[i] # SA[i-1]인 경우에 성립한다.


이러한 조건을 만족하는 LCP중 가장 큰 값이 LCS가 된다.

만약 LCS의 실제 값을 알고 싶다면 SA[i-1]이나 SA[i]중 아무거나 골라서 그 index에서 LCP[i]만큼을 slicing해서 읽으면 된다.
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

	//suffix array calculate for c
	vector<int> suffixArray(n), group(n+1), tempGroup(n+1);

	//initialize
	for(int i = 0; i < n; ++i){
		suffixArray[i] = i;
		group[i] = c[i];
	}
	group[n] = tempGroup[n] = -1;				//group[i] = S[i:]가 t글자 기준으로 지금 어디에 잇는지.

	//make suffix array
	while(t <= n){
		Comparator comp(group,t);
		sort(suffixArray.begin(),suffixArray.end(),comp);

		t *= 2;
		if(t >= n) break;

		//현재 suffixArray는 첫 2t글자를 이용해서 정렬이 되어있으므로 그냥 grouping 만 다시 해주면 된다.
		tempGroup[suffixArray[0]] = 0;			
		for(int i = 1; i < n; ++i){
			if(comp(suffixArray[i-1],suffixArray[i]))		//2t글자를 기준으로 나보다 앞선다면 나는 걔랑은 첫 2t글자 기준으로는 같은 compnent가 아니다.
				tempGroup[suffixArray[i]] = tempGroup[suffixArray[i-1]] + 1;
			else			//첫 2t글자가 같다면 같은 component
				tempGroup[suffixArray[i]] = tempGroup[suffixArray[i-1]];
		}		
		group = tempGroup;
	}

	vector<int> LCP(n),rank(n);
	for(int i = 0; i < n; ++i)
		rank[suffixArray[i]] = i;

	int h = 0, ans = 0;
	for(int i = 0; i < n; ++i){
		if(rank[i]){
			int j = suffixArray[rank[i]-1];
			while(c[i+h] == c[j+h]) h++;
			LCP[i] = h;		//LCP[i] = S[i:]와 S[i-1:]의 LCP
			if((i < a.length() && j > a.length()) || (i > a.length() && j < a.length()))
				ans = max(ans,h);
		}
		if(h) h--;
	}
	cout << ans;
}