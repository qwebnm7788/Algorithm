/*
*캐릭터가 몇개를 커버해주느냐에 따라서 케이스가 나뉘기 때문에 모든 경우를 해보아야 한다.

match(w, s) = 와일드카드 문자열 w가 s와 매칭이 되는지 여부를 반환하는 함수를 정의하자.

*/

bool match(const string& w, const string& s){
	//w와 s를 훑으면서 지나가보자.
	int pos = 0;

	//범위 내에서 두 글자가 같거나, 다르지만 와일드 카드 문자가 ?인 경우에는 계속 진행한다.
	while( pos < w.size() && pos < s.size() && (w[pos] == s[pos] || w[pos] == '?'))
		pos++;

	/*
	while문이 끝나는 조건은 다음과 같다.
	1. w가 끝났다. -> s도 끝났다면 true
	2. s가 끝났다. -> w의 남은 친구들이 모두 *이라면 true
	3. w[pos] != s[pos] -> false
	4. w[pos] == '*' -> *이 몇개의 친구를 커버해주는지 확실하지 않으므로 0~남은 문자수를 모두 커버해보면서 체크해본다.
	*/

	//1.
	if(pos == w.size())
		return pos == s.size();

	//2,4가 모두 여기에 속한다. 모두 *이라면 s가 끝났기 때문에 계속 돌면서 pos+1로 다음칸을 계속 보다가 전부다 *이라면  1번 케이스에 걸려서 true를 반환하게 된다. 
	if(w[pos] == '*'){
		//남은 s의 수만큼을 각각 커버해본다.
		//pos+skip < s.size() 까지만 하게되면 *이 남은 '전부'를 커버하는 상황을 살피지 못한다.
		//왜냐면 s.size()-1은 맨 마지막 글자가 '남은' 상태로 가는것이기 때문!
		for(int skip = 0; pos+skip <= s.size(); ++skip){
			if(match(w.substr(pos+1),s.substr(pos+skip)))
				return true;		//한번이라도 되면 true!
		}
	}
	//else
	return false;
}


//위 코드는 *마다 모두 검사를 하기 때문에 *이 많을수록, 또한 s의 길이가 길어질 수록 오래 걸리는 코드가 된다.
//예를 들면 *******a 와 aaaaaaaaab 같은 것.  아무리 해봤자 안되지만 (마지막의 b때문에) *로 하나씩 다 대응을 체크하기 때문에
//안된다고 결정짓기 까지의 걸리는 시간이 오래걸린다.


/*
위의 코드에서 중복되는 부분이 있을까?
함수의 입력으로 주어지는 w와 s는 제한되어있다. 왜냐면 내부 for루프에서 앞에꺼를 몇칸 띄어내냐의 차이지 다른 글자가 추가되는 것이 아니기 때문이다.
따라서 w도 0~100개, s도 0~100개의 글자종류밖에 없으므로 최대 101*101개의 입력종류만이 존재한다.

***....** 이라면 100*99*98.... 이 될 수도 있는데 최대 입력의 수가 101*101=10201번이므로 중복되는 부분이 있음을 알 수 있다.
*/


int cache[101][101];		//아직 계산이 안된것은 -1 true = 1 false = 0
string W, S;

//W[w:], S[s:] 에 대응되는지 여부를 반환한다.
bool matchMemoized(int w, int s){
	int& ret = cache[w][s];

	if(ret != -1)
		return ret;

	while( s < S.size() && w < W.size() && (W[w] == '?' || W[w] == S[s])){
		w++;
		s++;
	}

	if(w == W.size())
		return ret (s == S.size());

	if(W[w] == '*'){
		for(int skip = 0; s+skip <= S.size(); ++skip)
			if(matchMemoized(w+1,s+skip))
				return ret = 1;
	}
	return ret = 0;
}


//w와 s의 길이가 n이라고 한다면 각 부분문제 (W[w:],S[s:]로 대응해보는 경우)는 n^2이 되고 최악의 경우 *****...로 주어지면 matchMemoized 최대 n번 재귀를 부르게 된다.
//따라서 O(n^3)으로 처리해줄 수 있다.


//내부의 for, while 루프내부를 최적화 시키면서 O(n^2)까지 내려줄 수 있다.

while(s < S.size() && w < W.size() && (W[w] == S[s] || W[w] =='?')){
	w++;
	s++;
}

/*
이 부분에서 while문을 통과했다면 두 글자는 대응이 된다는 소리이므로 (* 제외하고 둘이 짝이 맞는다는 소리!)
그냥 w+1, s+1문제를 해결하면 확인해 줄 수 있다.

*/
while(s < S.size() && w < W.size() && (W[w] == S[s] || W[w] =='?')){
	return ret = matchMemoized(w+1,s+1);
}


/*
또한 skip이 들어간 for문에서는 몇글자를 skip할지를 고르는 부분이 있는데
1차원 for를 재귀로 수정함으로써 최적화 할 수 있다.

매 단계에서 *에 아무글자도 대응을 안시킬지 or 1글자를 대응시킬지를 확인하면서
내려가주면 1차원 for루프를 대신 할 수 있다.

*/

if(W[w] =='*'){
	//*에 아무글자도 대응 안시키거나, 1글자만 대응시켜보자.
	if(matchMemoized(w+1,s) || (s < S.size() && matchMemoized(w,s+1) )
		return ret = 1;
}


/*
Accepted code

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
using namespace std;

int cache[101][101];
string W, S;

bool foo(int w, int s) {
	int& ret = cache[w][s];
	if (ret != -1)
		return ret;

	while (w < W.size() && s < S.size() && (W[w] == S[s] || W[w] == '?')) {
		w++;
		s++;
	}

	if (w == W.size())
		return ret = (s == S.size());

	if (W[w] == '*') {
		for (int skip = 0; s + skip <= S.size(); ++skip)
			if (foo(w + 1, s + skip) == 1)
				return ret = 1;
	}
	return ret = 0;
}
int main() {
	freopen("input.txt", "r", stdin);
	int test;
	cin >> test;

	for (int z = 0; z < test; ++z) {
		int n;
		cin >> W >> n;
		vector<string> ans;

		for (int i = 0; i < n; ++i) {
			cin >> S;
			fill(&cache[0][0], &cache[0][0] + sizeof(cache) / sizeof(cache[0][0]), -1);
			if (foo(0, 0)==1)
				ans.push_back(S);
		}

		sort(ans.begin(), ans.end());
		for (int i = 0; i < ans.size(); ++i)
			cout << ans[i] << endl;
	}
}


*/

