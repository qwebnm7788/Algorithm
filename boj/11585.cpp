/*
11585 속타는 저녁메뉴

목표로 하는 문자열을 target 현재상태를 current라고 하면
결국은 current를 환형시프트 시켜가면서 target으로 만들 수 있느냐를 찾는 문제이다.
왜냐면 시프트 시켜서 target으로 만들수 있다면 그때의 첫번째 글자가 12시방향으로 위치하게 만든다면
가능해지기 때문이다.

이때는 currentcurrent로 이어붙인다음에 여기서 target을 찾는 방법으로 구해줄수있는데.
target을 움직이면서 대보면 뒷부분에 밖으로 나가는 부분은 다시 current의 시작부분이 되게 되므로
current를 반시계방향으로(왼쪽으로)시프트 시킨것과 같은 효과를 보게된다. 여기서 찾게 된다면 current를 회전시켜서
target을 얻을 수 있는 것이므로 이 때의 갯수를 세어주면 된다.

여기서 예외로 처리해야 할 부분이 있는데 currentcurrent에서 target을 찾는 방법으로 환형시프트의 효과를 준 것이므로 currentcurrent자체에서 뒷부분의 current에서 답을 찾는것은
세어주면 안된다 . 이런경우는 딱 한가지가 있는데 current와 target이 서로 같은경우이다. 이때는 0번에서 찾을때도 구할 수 있고 current번(index상에서 두번째 current의 시작부분)에서 또다시 마지막으로
찾을 수 있게 되기 때문이다.
이를 간단하게 처리하는 방법은 애초에 currentcurrent를 만든다음 맨 마지막 글자를 제외시켜줌으로써 그러한 상황이 아예 발생하지 못하게 하면 된다.

또한 이문제에서 입력에 상당히 주의를 해야되는데
왠만하면 getchar()를 이용하지 말자. cin 과 getchar를 섞어서 사용하고 \n를 걸러내는 방식으로 하면 30~50%정도에서 WA를 받는다.
\n을 걸러내지 말고 애초에 n이 주어져서 입력받아야 하는 숫자가 정해져있으므로 더 안전한 방법으로 입력을 받도록 하자.
*/
#include <iostream>
#include <string>
#include <algorithm>
#include <vector>
using namespace std;

vector<int> getPi(const string& source) {
	int size = source.length();
	vector<int> pi(size, 0);

	for (int i = 1, matched = 0; i < size; ++i) {
		if (matched > 0 && source[i] != source[matched]) matched = pi[matched - 1];
		if (source[i] == source[matched]) pi[i] = ++matched;
	}
	return pi;
}

//source에서 target을 검색, 시작위치를 반환
vector<int> kmp(const string& source, const string& target) {
	int sourceSize = source.length();
	int targetSize = target.length();

	vector<int> ret;
	vector<int> pi = getPi(target);
	for (int i = 0, matched = 0; i < sourceSize; ++i) {
		if (matched > 0 && source[i] != target[matched]) matched = pi[matched - 1];
		if (source[i] == target[matched]) {
			matched++;
			if (matched == targetSize) {
				ret.push_back(i - matched + 1);
				matched = pi[matched - 1];
			}
		}
	}
	return ret;
}

//original을 시프트해서 target으로 만들수 있다면 true 아니라면 false
int foo(const string& original, const string& target) {
	string temp = original + original;
	temp.pop_back();
	return kmp(temp, target).size();
}

int gcd(int a, int b) {
	if (b == 0) return a;
	return gcd(b, a%b);
}

int main() {
	freopen("input.txt", "r", stdin);
	int n;
	cin >> n;

	char temp;
	string target, current;
	while (target.length() < n && cin >> temp) {
		if (temp != ' ')
			target.push_back(temp);
	}
	while (current.length() < n && cin >> temp) {
		if (temp != ' ')
			current.push_back(temp);
	}

	int numer = foo(current, target);
	int x = gcd(n, numer);
	
	numer /= x;
	n /= x;
	cout << numer << "/" << n;
}