/*
Suffix Array (접미사 배열)

문자열을 다룰 때 사용하는 자료구조이다.
어떤 문자열 S의 모든 접미사를 사전순으로 정렬해서 배열에 저장한 것을 말한다.

이때 배열에 저장하는 것은 그때의 접미사 자체를 문자열로 집어넣으면 O(|S|^2)이 되니깐 ((|S|*|S+1|/2) 이니깐)
그냥 그 접미사의 시작 index를 저장해준다.


그러면 이러한 접미사 배열을 통해서 할 수 있는 일은 대표적으로 문자열 검색이 있다.
KMP 탐색도 있지만 이번에는 접미사 배열을 이용해보자.

만약 H에서 N을 포함하고 있을때 N을 찾는다고 생각해보자.
이때 알아야 할 정보는 H가 포함하는 N은 H의 어느 접미사에 대해서 접두사로 자리잡고 있다는 것이다.
(즉 다시 말해서 포함하는 N을 하나 잡으면 H의 모든 접미사 중에 하나는 N을 그 접미사의 접두사로 한다)

왜냐하면 모든 접미사를 쪼개는 방법과 모든 접두사를 쪼개는 방법을 생각해보면 서로 정반대로 쪼갠다는 것을 알 수 있는데
이러한 사실을 보면 알 수 있지 않을까..?

어쨋든 이렇게 되면 이제 H의 접미사 배열은 H의 모든 접미사가 정렬된 상태로 저장되어 있으니깐 이를 이진탐색으로
검색해보면 매번 검색마다는 mid 접미사에 대해서 접두사만큼 (|N|만큼)을 체크해봐야 하므로 O(|N|)이 걸리고
이진탐색은 총 O(log|H|)번 이루어지므로 O(|N|log|H|)에 문자열을 검색할 수 있음을 알 수 있다.
*/

/*
그렇다면 접미사 배열을 어떻게 효율적으로 생성할까

우선 간단하게 생각해보면 모든 접미사를 넣어놓고 비교함수를 만들어서 sort함수로 정렬하면 되는데
이렇게 되면 우선 sort함수는 O(nlogn)번의 비교를 하고 그 때마다 비교함수를 사용하게 된다.

간단한 방법은 strcmp함수를 이용해서 두 친구중에 누가 먼저오나를 보면되고
strcmp함수는 그냥 linear하게 비교하기 때문에 O(비교하는 두 문자열의 길이) = O(n)이 된다.
따라서 전체 시간복잡도는 O(n^2logn)이 된다.
*/


#include <vector>
#include <algorithm>
using namespace std;

//struct로 만들어 놓고 비교함수를 오버로딩 해놓는다.
struct SuffixComparator {
	const string& s;
	SuffixComparator(const string& s)
		:s(s) {}
	bool operator() (int i, int j) {
		//s.substr을 하지 말고 곧바로 strcmp로 비교해서 하면 임시객체를 만드는 비용을 줄일 수 있다.
		return strcmp(s.c_str() + i, s.c_str() + j) < 0;		//접미사 S[i:],S[j:]보다 앞서면 true
	}
};

//s의 suffix array를 계산한다.
vector<int> getSuffixArrayNaive(const string& s) {
	vector<int> perm;		//접미사 배열
	for (int i = 0; i < s.size(); ++i) perm.push_back(i);		//우선은 초기화 perm[i] = i로. -> 이게 제일 간단하다 왜냐면 모든 index가 등장해주기 때문
	sort(perm.begin(), perm.end(), SuffixComparator(s));
	return perm;
}


/*
좀 더 빠른 방법은 다음과 같다.

접미사 배열을 여러번 정렬하는 것인데 매번 정렬마다 정렬의 기준을 바꿔가면서 하는 것이다.
즉 처음에는 각 접미사의 첫글자로 비교하여 정렬하고 그다음은 첫 두글자를 비교 , 첫 네글자, 첫 여덟글자 ...로 비교하는 것이다. (n글자 이하인 동안 계속)

이런식으로 정렬을 하게되면 총 logN번을 정렬을 하여 접미사 배열을 얻는다.
이 친구가 정렬을 더 많이 하지만 더 빠른이유는 비교함수를 O(1)에 구현할 수 있기 때문이다.

이때 필요한 정보는 group[]인데 
각각의 iteration을 보자. 첫번째의 경우 첫글자를 기준으로 정렬을 했다고 하면
첫 글자를 기준으로 그룹을 나누는 것이다. 순서대로 그룹을 나누는데 첫글자가 같으면 같은 그룹번호를 갖고 다르다면
그룹번호가 커지면서 달라지게 된다. group[i] = S[i:] 접미사가 속한 그룹의 번호가 되도록 해보자.

이를 확장해서 살펴보자.
이전라운드에서 첫 글자 t를 기준으로 정렬을 해서 group[]배열 또한 만들어 놓은 상태라고 생각하자.
이제 다음라운드가 되어서 첫 2t글자를 기준으로 정렬할때를 보면
만약 두 접미사 S[i:],S[j:]의 첫 t글자가 다르다면 group[i],group[j]의 값을 통해서 순서를 바로 할 수 있다.
그렇지만 둘의 첫 t글자가 같다면 이제 S[i+t:]와 S[j+t:]의 첫 t글자를 보면 된다. (즉 한번에 2t글자를 볼 필요가 어느 경우에서도 없다.)
->이전의 t글자로 저장해놓은 group[]을 이용해서 2t 글자 비교에 이용하여 얻을 수 있따.

이렇게 되면 비교함수에서 group[i],group[j]를 비교하거나 group[i+t],group[j+t]를 비교하는 둘 중의 하나만을 사용하는 O(1)의 연산이 되기때문에
정렬연산이 O(nlogn)이 된다.

그 후에 group을 다시 배정하는데 O(n)이 걸리고 이러한 정렬은 O(logn)번을 반복하므로 이렇게 suffix array를 구하는 알고리즘의 시간복잡도는
O(n(logn)^2)이 되어서 위에서의 (n^2logn)보다 훨씬 빨라졌다.

이러한 방식의 suffix array를 구하는 알고리즘을 맨버-마이어스 알고리즘이라고 한다.
*/

//첫 2t글자를 이용해서 비교함수를 구현한다.
//길이가 0인 접미사도 고려한다
struct Comparator {
	const vector<int>& group;
	int t;
	Comparator(const vector<int>& _group, int _t)
		:group(_group), t(_t) {}
	bool operator() (int a, int b) {
		//S[a:],S[b:]의 첫 t글자가 다르면 그냥 group번호로도 정렬할 수 있다.
		if (group[a] != group[b]) return group[a] < group[b];
		//아니라면 S[a+t:],S[b+t:]의 첫 t글자를 비교한다.
		return group[a + t] < group[b + t];
	}
	
};

/*
위에서 a+t,b+t의 범위체크는 필요가 없는데 왜냐면 a+t,b+t에 도달하려면 처음 t글자가 동일해야 하고 이 말은 이 두 접미사 S[a:],S[b:]는 길이가 최소 t이상이라는 것이다.
그러면 a,b의 index는 N-t이하를 가지고 되고 여기에 t를 더해봤자 최대 N까지밖에 나오지 않기 떄문에
group배열의 크기를 N+1로 잡으면 N index도 접근이 가능해서 따로 처리를 안해도 되도록 만들어 줄 수 있다.
*/

vector<int> getSuffixArray(const string& s) {
	int n = s.size();
	//group[i] = 모든 접미사를 첫 t글자를 기준으로 정렬할때 S[i:]가 들어가는 그룹의 번호
	//t = 1일때는 따로 정렬안하고 그냥 S[i:]의 첫글자로 초기화해주어도 충분하다. -> 왜냐면 char형은 정수로 표현이 가능하고
	//사전순으로 크기가 매겨져 있기때문에 그냥 넣어놔도 알아서 group의 대소비교에 이용이 가능하다
	int t = 1;
	vector<int> group(n + 1);		//크기는 N+1
	for (int i = 0; i < n; ++i) group[i] = s[i];		//글자 그대로
	group[n] = -1;		//n은 S[n:] = 접미사의 길이가 0인 상태를 말한다. 0글자면 제일 앞에 와도 논리적으로도 맞고 위의 index 체크 문제도 해결해준다.

	//logn번 정렬
	vector<int> perm(n);		//suffix array 결과
	while (t < n) {
		//현재까지 group[]은 첫 t글자를 기준으로 계산이 된 상태
		//이제 첫 2t글자를 기준으로 다시 정렬 -> 즉 t글자로 grouping된 정보를 이용해서 첫 2t글자를 기준으로 정렬한다.
		Comparator compareUsing2T(group, t);
		sort(perm.begin(), perm.end(), compareUsing2T);
		
		t *= 2;
		if (t >= n) break;		//t가 n글자를 넘으면 종료!
		
		//2t글자를 기준으로 한 정보를 group에 저장한다.
		vector<int> newGroup(n + 1);
		newGroup[n] = -1;
		newGroup[perm[0]] = 0;
		for (int i = 1; i < n; ++i) {
			if (compareUsing2T(perm[i - 1], perm[i]))
				newGroup[perm[i]] = newGroup[perm[i - 1]] + 1;		//perm[i-1]이 perm[i]보다 먼저온다면 
			else
				newGroup[perm[i]] = newGroup[perm[i - 1]];
		}
		group = newGroup;
	}
	return perm;
}


/*
활용 예제
원형문자열에서의 n글자를 읽는 방법의 수 중 사전순으로 가장 빠른 문자열을 찾을때

읽는 방법의 수는 n개가 있고 이를 모두 후보로 만들어서 제일 사전순으로 빠른애를 비교하려면 O(n^2)이 걸린다.
그렇지만 원형 문자열 S를 두번 이어붙인 S^2을 이용해서 접미사 배열을 만든 뒤에
길이가 N이상인 접미사중에 사전순으로 가장 앞에 오는 친구를 찾으면 간단하게 구할 수 있다. (-suffix array를 구하는 O(n(logn)^2))
S^2이니깐 길이가 2*n인데 여기서 내가 찾는 모든 후보들은 길이가 N이다. (왜냐면 기존 원형문자열에서 읽는 친구니깐 N)
그러면 가능한 친구들은 접미사 배열의 길이가 N보다 커야한다. (왜냐면 N보다 커야지 내가 찾아낸 index가 N보다 작을꺼니깐)
*/

#include <string>
using namespace std;
string minShift(const string& s) {
	string s2 = s + s;
	vector<int> a = getSuffixArray(s2);
	for (int i = 0; i < a.size(); ++i) {
		if (a[i] <= s.size())		//가장 먼저 걸리면 그냥 그 값을 리턴한다.
			return s2.substr(a[i], s.size());		//a[i]부터 s의 길이까지하면 딱 된다.
	}
	return ("요긴 절대 못온다.");		//왜냐면 2n에서 길이가 n인 접미사는 무조건 만들어지니깐 (suffix array는 모든 경우를 다만드니깐)
}

/*
서로 다른 부분문자열의 수 세기

길이가 n인 문자열은 최대 n*(n+1)/2개의 부분문자열을 가질 수 있따.
이것들 중에 서로 다른것만을 센 갯수를 얻으려고 하면 우선 set에다가 넣어주는 방법이 있는데
set에 집어넣을때는 각 문자열마다 O(logN)번의 비교를 해야 넣을 수 있다고 한다.
또한 각 문자열의 비교에 O(N)이 걸리게 된다.
따라서 모든 부분문자열은 O(N^2)개이므로 총 O(N^3logn)이 된다.
-> hash를 써서 O(n^3)까지 줄일수도 있다고 한다.


길이가 m인 접미사에는 m개의 접두사가 존재함을 바로 알 수 있다.
그러면 만약 각 접미사에서 중복되는 접두사가 하나도 없다면 그냥 모든 접미사에 대해서 길이를 모두 더한 값이 원하는 값이 될것이다.

이용할 성질은 바로 한 부분문자열이 두번 이상 출현하게 될때 이 부분문자열을 접두사로 갖는 접미사는 suffix array에서
서로 인접한 index에 존재한다는 것이다. ->왜냐면 suffix array는 접미사가 사전순으로 정렬된것인데 사전순은 글자의 앞부분부터
비교를 하게 되니깐 접두사를 기준으로 같은 친구들은 뭉쳐있게 된다.

따라서 한 부분문자열이 이미 출현한 친구인지는 바로 위에 친구들만 살펴봐주면 된다.

이제 중복되는 접두사를 제외하고 갯수를 세어줌으로써 답을 구하면 된다.
->각 접미사에 대해서 바로 앞 접미사와 나의 최대 공통된 접두사의 길이를 제외해줌으로써 갯수를 중복되지 않게 셀 수 있게 된다.

이렇게 가장 긴 공통 접두사를 구하는 것을 LCP(longest common prefix) 라고 한다.
*/

//S[i:],S[j:] 접미사의 최장 공통접두사 길이를 반환한다.
int commonPrefix(const string& s, int i, int j) {
	int k = 0;
	while (i < s.size() && j < s.size() && s[i] == s[j])
		++i, ++j, ++k;
	return k;
}

//s의 서로다른 부분문자열의 수를 반환
int countSubstrings(const string& s) {
	vector<int> a = getSuffixArray(s);
	int ret = 0;
	int n = s.size();
	for (int i = 0; i < a.size(); ++i) {
		int cp = 0;
		if (i > 0) cp = commonPrefix(s, a[i - 1], a[i]);		//바로 위 친구만 보면된다.
		ret += s.size() - a[i] - cp;		//s.size() - a[i]는 S[i:]의 길이가 되고 거기서 바로 앞친구랑 공통이 된부분은 제외한다.
	}
	return ret;
}

//이러한 LCP배열을 구하는데는 commonPrefix()가 O(N)에 수행되고 countSubstrings도 O(N)만큼 돌아서 O(N^2)이 된다.

/*
LCP 배열을 구하는데 O(N)으로 구할 수 있는 방법.

S[i:]와 접미사 배열에서 인접한 접미사와의 LCP 를 h라고 할때 h가 1보다 크다면 S[i+1:]과 이 친구와 인접한 접미사와의 LCP는
최소한 h-1이상이라는 사실을 이용한다.
*/

//rank[i] = S[i:]접미사가 사전순으로 몇번째인가를 묻는다.
//즉 suffixArray[i] 의 역함수와 같다. rank[suffixArray[i]] = i 이다.
int h = 0, suffixArray[5], rank[5], a[5];
string s;
int n = s.length();
for (int i = 0; i < n; ++i) {
	if (rank[i]) {
		//rank[i]가 0이 아니면 (0인 경우는 접미사배열의 맨 첫번째 친구인데 이 친구는 LCP계산이 안되므로 패스
		int j = suffixArray[rank[i] - 1];		//접미사배열에서 내 바로 앞 친구와의 비교
		while (s[i + h] == s[j + h]) h++;		//h-1개"부터" 비교를 한다. 최소 h-2개임은 증명되었다. (블로그참조) 그 후에 겹치는것까지 h를 세어준다.
		a[rank[i]] = h;		//a[i] = 접미사배열에서 i번 친구와 i-1번째 친구의 LCP값이 들어간다.
	}
	if (h) h--;		//h가 1보다 크다면 h-1과 같으므로 두번째 친구부터는 다음친구에 넘겨줄때 h를 h-1로 넘겨준다.
}


