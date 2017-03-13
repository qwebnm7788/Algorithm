/*
KMP Algorithm (Knuth-Morris-Pratt Algorithm)

주어진 문자열 H에서 다른 문자열 N을 부분문자열로 확인하는지 확인하고
존재한다면 그 부분의 시작위치를 찾는 문제를 문자열 검색 문제라고 한다.(한 문자열에서 다른 문자열을 검색하는 것)

만약 두 번 이상 존재한다면 그에 따른 모든 시작위치를 반환해주어야 한다.
*/

/*
우선 가장 간단하게 생각해보면 다음과 같다.
모든 가능한 시작위치에서 (|H|-|N|까지 되겠죵?) 한번씩 다 해보는거야

i번 반복에서 시작점을 i로 잡고 두 문자열을 |N|을 주르륵 훑으면서 서로 한글자라도 다르면 중간에 나가버리고
전부다 일치한다면 i를 저장해주면 된다.
*/

#include <vector>
using namespace std;

vector<int> naiveSearch(const string& H, const string& N) {
	vector<int> ret;

	//모든 가능한 시작위치에 다 시도
	for (int begin = 0; begin + N.size() <= H.size(); ++begin) {
		bool matched = true;
		for (int i = 0; i < N.size(); ++i) {
			//한글자라도 다르면 실패!
			if (H[begin + i] != N[i]) {
				matched = false;
				break;
			}
		}
		if (matched) ret.push_back(begin);
	}
	return ret;
}

/*
이 친구의 시간복잡도는 어떻게 될까?
최악의 경우는 다음과 같을것이다. 만약 H와 N이 둘다 모든 문자가 a로 이루어진 문자열이라고 하자.
그렇게 되면 모든 가능한 시작위치는 정답이 될꺼야.

그렇지만 매번 N의 길이만큼의 체크를 해주어야 하는것은 변함없는 사실이고
시작 가능한 위치는 |H|-|S|+1 개이고 보통은 목표가 되는 친구인 H의 길이가 N의 길이보다 훨씬 크니깐 (|H| >>> |N|)
시작 가능한 위치는 O(|H|)라고 해볼 수 있다.
매번 루프에서 O(|N|)의 비교가 필요하니깐

시간복잡도는 O(|N|*|H|)가 된다. 
구현이 쉬운 장점이 있지만 엄청나게 긴 문자열에서 조금만 긴 N을 찾으려고 하면 시간이 좀 걸리게 된다.
*/

/*
위의 알고리즘을 조금 개선해보자. 

만약 i번 위치에서 불일치가 일어났다면 단순히 i+1에서 다시 시작하는것이 아니라 i번 글자 전까지 내가 알 수 있는 정보를 이용해서
좀 더 좋은 시작위치를 찾을 수 있다.

예를 들어서 i에서 시작해서 7글자가 일치하고 8번째 글자에서 불일치가 발생했다고 생각해보자.
만약 우리가 H[i+1] = 'b' 이란것을 확인했고 N[i+1] = 'a'라는 것 또한 알고있다면 단순히 i -> i+1로 이동해서 시작을하는것은
무의미한 짓이다. (왜냐면 우리는 i~i+8까지 H와 N의 글자를 모두 확인했기 때문이지)

H[i+1:] 에서 N[i+1]과 처음으로 같아지는 친구가 아마도 다음의 시작장소로 적합할꺼야.
*/


/*
시작위치 i에서 H,N을 서로 비교해 가다가 matched 글자가 일치하였고 그 다음글자에서 불일치가 일어났다고 하자.
즉 이는 N[0:matched-1] 과 H[i:i+matched-1]이 서로 일치한다는 것과 같다.
여기서 N[0:matched-1]은 N의 접두사 중 하나임을 알 수 있다.

여기서 i+k번이 다음으로 적절한 시작위치가 되려면 N[0:matched-k] 와 H[i+k:i+matched-1]이 서로 같아야 함을 알 수 있다. (그림을 봐야 좋을듯)

이걸 자세히 보면 N[0:matched-1]의 길이 matched-k인 접두사와 접미사가 서로 같아야지 가능함을 알 수 있다.
이 사실을 빠르게 이용하려면 N의 각각의 접두사에 대해서 접두사와 접미사가 같은 문자열의 최대길이를 미리 계산해둔다면
빠르게 할 수 있을것이다.

이러한 배열을 pi[i] 라고 하면 pi[i] = N[0:i]의 접두사와 접미사가 같은 문자열의 최대길이
다시 말해 pi[i] 는 N의 i번 글자까지만을 봤을떄 그 문자열에서 접두사와 접미사가 같은 최대의 길이를 저장하는 것이다.
(이러한 pi함수를 부분일치 테이블(partial match table) 혹은 실패함수(failure function)이라고 한다.
*/


/*
matched 글자가 일치한 후에 불일치가 일어났다면 다음 시작위치는 어디 일까?
바로 지금의 시작위치 +  matched-pi[matched-1] 가 된다.
게다가 이렇게 시작위치를 움직이고 나서도 처음부터 비교하는 것이 아니구 이미 pi[matched-1]만큼이 일치함을 알기 때문에
matched = pi[matched-1]로 해놓고서 탐색을 계속해나가면 된다. (즉 이미 pi[matched-1]만큼은 match가 된다고 해도 좋다.)

*/

vector<int> kmpSearch(const string& H, const string& N) {
	int n = H.size(), m = N.size();
	vector<int> ret;

	//pi[i] = N[0:i]의 접미사도 되고 접두사도 되는 문자열의 최대길이
	vector<int> pi = getPartialMatch(N);

	int begin = 0, matched = 0;
	while (begin <= n - m) {
		//시작 가능한 부분은 n-m까지이다.
		if (matched < m && H[begin + matched] == N[matched]) {
			//만약 글자가 같다면
			matched++;
			if (matched == m) ret.push_back(begin);		//m글자(=|N|)모두 일치한다면 시작위치를 저장해두자.
		}
		else {
			//예외가 있다면 하나도 같은 글자가 없다면 우리가 점프할만한 정보가 없기 때문에 (이미 봐버린 정보가 없다) 그냥 다음칸으로 가자.
			if (matched == 0)
				begin++;
			else {
				begin += matched - pi[matched - 1];		//시작위치를 적절하게 점프하자.
				//또한 이미 pi[matched-1]만큼은 확인된 사실이니 옮겨버리자.
				matched = pi[matched - 1];
			}
		}
	}
}


/*
getPartialMatch() 구현 (책의 설명을 보는게 좋을듯 싶다.)
*/
#include <vector>
#include <string>
#include <algorithm>
using namespace std;
//pi[i] = N[0:i] 의 접미사도 되고 접두사도 되는 문자열의 최대길이를 계산
vector<int> getPartialMatchNaive(const string& N) {
	int m = N.size();
	vector<int> pi(m, 0);

	//가장 단순하게 생각할때
	for (int begin = 1; begin < m; ++begin) {
		for (int i = 0; i + begin < m; ++i) {
			if (N[begin + i] != N[i]) break;
			//아니라면 지금까지 i+1글자. (i=0부터니깐 +1)가 동일한것이므로 갱신
			pi[begin + i] = max(pi[begin + i], i + 1);			//그렇지만 이전 begin값에서 더 길게 만들어 줄수 있으므로 (더 길어질 수 있었다면 나보다 전에서 길어졌을꺼야) max함수 사용
		}
	}
	return pi;
}

//kmp algorithm 을 이용한 방법
//여기서 pi[]의 각 원소는 최대 한번만 변경되기 때문에 max함수를 제외해 줄 수 있다.

vector<int> getPartialMatch(const string& N) {
	int m = N.size();
	vector<int> pi(m, 0);

	//kmp로 N에서 N을 찾는다. (자기자신을) -> 이 과정에서 pi를 다 계산해줄 수 있다.
	//begin = 0이면 자기자신 자체를 찾게되니깐 begin = 1부터 시작하자.
	int begin = 1, matched = 0;
	//N의 끝에 도달할때까지 찾으면서 부분일치를 모두 기록한다.
	while (begin + matched < m) {
		if (N[begin + matched] == N[matched]) {
			//글자가 같으면
			matched++;
			pi[begin + matched - 1] = matched;			//N[0:begin+matched-1]까지의 최대 길이는 matched이다. (index가 0부터니깐 -1을 해준다.)
		}
		else {
			if (matched == 0)
				begin++;			//예외사항
			else {
				begin += matched - pi[matched - 1];			//원본의 N[0:matched-1]까지 (즉 matched개의 글자까지의 부분문자열에서 접미사=접두사 인 최대길이)
				matched = pi[matched - 1];
			}
		}
	}
	return pi;
}


/*
조금 더 전통적인 방식의 kmp 알고리즘 구현
*/

//source에서 target을 검색한다.
vector<int> kmpSearch2(const string& source, const string& target) {
	int n = source.size(), m = target.size();

	vector<int> ret;
	vector<int> pi = getPartialMatch(target);		//target의 부분일치 테이블

	int matched = 0;		//현재 대응된 글자의 수 -> 조금 쉽게 생각하자면 matched는 현재 target을 훑어보는 index라고 보면 된다.
	//source의 각 글자를 순회한다.
	for (int i = 0; i < n; ++i) {
		//target의 matched"번" 글자와 source에 해당되는 글자가 불일치한다면
		//matched가 pi[matched-1]을 따라간다. 즉, 다음번에 살펴봐야 하는 친구는 pi[0:matched-1]이 된다는 것인데
		//왜냐면 pi[0:matched-1]은 지금까지의 target의 부분문자열 중에 접두사=접미사인 친구의 최대길이이고 그 말은 뒷부분과 앞부분은 pi[0:matched-1]만큼이나 겹칠 수 있다는 것이다.
		//따라서 항상 target의 맨처음부터 보는것이 아니라 이미 확정된 부분은 건너 뛰고 보는것이 된다.
		//그런데 여기서 while문으로 이동한 이유는 반복문을 2번이상 돌아갈 수 있다는것인데
		//이 경우는 특정한 pi[x]값이 |target|/2 보다 큰 (예를 들면 "abaabaaba" 는 최대 6까지 된다. (|target|/2 = 4 , 또한 부분일치테이블에서 자기자신인 경우는 제외) 경우 생기게 된다.
		//kks 블로그를 보는것이 좋다; 결론적으로는 한번 움직이면 곧바로 다시 불일치가 일어나는 경우가 생길 수 있는데 이때는 다시 pi[matched-1]만큼 다시 움직여 줘야 한다. (j=0이 되었다면 그냥 while 나간다음에 다음칸 가야지 뭐)
		while (matched > 0 && source[i] != target[matched]) matched = pi[matched - 1];		//pi의 index가 matched-1인 것은 matched번 글자에서 어긋나니깐 그 전까지의 접미사=접두사를 이용한것이다.
		
		//글자가 대응된다면
		if (target[i] == source[matched]) {
			matched++;		//이동하고
			if (matched == m) {		//target의 글자 전체 다 맞았으면 너는 정답 !
				ret.push_back(i - m + 1);		//여기서 우리가 찾은 친구는 source[i:i+matched-1]에서 target을 찾은것이니깐 -> 그런데 이 i는 이 찾은 문자열의 처음 시작 i이고 우리가 지금 가지고 있는 i는 i(지금의 i) = i(시작지점의 i)+m-1번이니깐 시작지점의 i = (지금의)i-m+1이 된다.!
				matched = pi[matched - 1];		//이렇게 다 맞춰놓고도 pi만큼 이동해주어야 하는데. 왜냐면 가능한 "모든" 지점을 다 찾아야 하기 때문이야
				//예를 들면 source = "ababa", target="aba" 라면 정답은 1, 3인 두군데가 된다.
				//여기서 matched == m이 되었다는 것은 target의 글자 끝에 도달한것이다. 이렇게 되면 pi[matched-1]은 전체 문자열자체에서 최대 길이를 찾게 되는데 본인 자신은 제외니깐
				//pi[m-1]= 1이 된다. 그러면 다시 target의 1번을 다음 i번 글자에 대어보므로써 찾을 수 있다.
				//즉 matched == m을 찾아서 정답을 하나 구했어도 마치 답을 못구한것처럼 이동을 시켜준다. -> 만약 이동을 matched가 다 맞았다고 m개를 그냥 다 뛰고 다시 시작해버리면
				//그 사이에 지금것과 중복되는 단어로 이루어진 정답은 구하지 못하게 된다.!!!
			}
		}
	}

}

/*
이것또한 kmp를 응용해서 구해줄 수 있는데 우선은 source = target이라고 생각하자. 
즉 source에서 target을 찾는 kmp인데 source가 자기자신과 같다. -> 즉 자기자신을 자기자신에서 검색한다고 생각하면 된다.
여기서도 i는 source의 index, matched는 target의 index를 가진다고 생각하고 따라가자.

i=1부터, matched=0부터 시작하는데 i = 0이라면 둘이 같은 문자열이기 때문에 i =0번에서 비교가 성공해서 자기 자신의 전체 길이를 주게 된다.;;(접미사=접두사 길이가 아니라)
따라서 이렇게 주게 되면 나 전체는 제외하고 부분일치하는 친구들만을 볼 수 있게 된다.
*/
vector<int> getPartialMatch2(const string& target) {
	int m = target.size();
	vector<int> pi(m, 0);		//0으로 초기화
	for (int i = 1, matched = 0; i < m; ++i) {
		//while문 내부에서는 matched가 1이상을 가지니깐 항상 pi[matched-1]으 계산되어있다.
		//왜냐면 matched-1개는 일치를 했다는 의미이고 그러면 밑에서 if문에서 pi값을 계산한것이니깐.
		while (matched > 0 && target[i] != target[matched]) matched = pi[matched - 1];			//서로 다른 글자라면 pi[matched-1]을 따라간다. -> 전부다 0으로 초기화되어있어서 0인 친구를 따라가는 경우도 있기때문에 matched는 줄어들기도 한다.
		//서로 일치한다면 
		if (target[i] == target[matched]) {
			//즉 지금까지 (i번까지) source[0:i]를 이용해서 만들수있는 접미사=접두사의 최대길이는
			//matched개가 일치된거니깐 matched=0번부터 출발이니깐 +1을 한 matched+1개가 일치하는것이다.
			matched++;
			pi[i] = matched;
		}
		//아니라면 그냥 i를 다음칸으로 이동시킨다.(for문의 증감문으로)
	}
}