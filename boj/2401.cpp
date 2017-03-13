/*
2401 최대 문자열 붙여넣기

문제를 이해하는게 조금 어려웠는데 그냥 단순하게
긴 문자열이 쓰여있는데 주어진 짧은 문자열들로 위를 덧붙인다고 할때 덧붙이는 짧은 문자열끼리는
겹치지 않도록 했을때 가장 많이 붙여놓을 수 있는 길이를 반환하는 것이다.

예제에서 aabbc에 aab,bbc를 붙일 수 있다면 aab를 붙이고 나면 bbc는 겹치게 되니 붙일 수 없다.
따라서 3개의 문자가 최대한 붙여넣는 것이므로 답은 3이다.

긴 문자열에 짧은 문자열을 붙여넣기 위해서는 긴문자열에서 짧은 문자열이 존재하는 곳을 찾아야 한다.
짧은 문자열은 여러번 사용 가능하므로 그러한 위치는 여러개를 검색하여도 좋다.

이때 문제를 풀때 제한이 되는것은 짧은 문자열끼리는 겹치지 못한다는 것인데 이는 다이나믹 프로그래밍으로 해결할 수 있다.

긴 문자열에 대해서 go[index]에 긴 문자열의 index에 짧은 문자열을 붙일 수 있을때 그것의 끝 index 즉  긴문자열의 index~go[index] 까지를 짧은 문자열이 먹고있으므로
이만큼을 건너 뛸수 있도록 저장해두자.

모든 짧은 문자열에 대해서 이 값을 기록해둔다면 다음과 같은 재귀함수로 구해줄수있다.

foo(index) = 가장 긴 문자열의 부분문자열 [index:]에서 최대 문자열 붙여넣기를 진행해서 얻을 수 있는 최대의 값을 반환한다고 하자.
이 경우에는 go에 저장해놓은 값을 이용해서 go[index]에는 index에서 찾을 수 있는 각 문자열들의 종료지점을 가지고 있는데
이렇게되면 go[index][i]-index+1 칸을 내가 붙여넣었으므로 go[index][i]-index+1 만큼을 얻을 수있고
이제 go[index][i] 다음칸부터의 (=foo(go[index][i]+1) ) 최대 문자열 붙여넣기를 한 값을 얻어서 그 값을 더해주면 된다.

또한 여기서 추가해준 케이스는
위에서 계산한 값들은 모두 index에서 문자열을 붙여넣었을 경우를 계산한것이고 만약 여기서 붙여넣을 수 있지만 (go[index]에 값들이 존재하지만)
붙여넣지 않기로 결정할때 더 큰 값을 얻을 수 있으므로 계산후에 foo(index+1)과 한번 더 비교를 진행하여 최대값을 반환해주면 된다.

foo(x)는 x값에 따라서만 결과값이 정해지는 최적부분구조를 가지고 있고 주어진 짧은 문자열들의 길이가 같은 경우가 있으므로
중복되는 연산이 진행될 수 있으므로 테이블을 형성해서 중복되는 계산을 피해줌으로써 TLE를 막을수있다.
*/
#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
using namespace std;

int sourceSize, targetSize;
vector<vector<int>> go;			//search[i][j] = 문자열의 i번 index에서 주어진 문자열을 찾았을때 그 문자열만큼 이동하고 종료된 칸을 갖는다.
vector<int> dp;

//주어진 문자열 s에서 s[index:]에서 얻을 수 있는 최대 문자열 붙여넣기를 한 문자열의 최대 길이를 반환한다.
int foo(int index) {
	//base case
	if (index >= sourceSize) return -1;
	int& ret = dp[index];
	if (ret != -1) return ret;
	ret = 0;
	for (int x : go[index])
		ret = max(ret, x - index + 1 + foo(x + 1));
	ret = max(ret, foo(index + 1));
	return ret;
}

vector<int> getPi(const string& source) {
	int size = source.length();
	vector<int> pi(size, 0);
	
	for (int i = 1, matched = 0; i < size; ++i) {
		if (matched > 0 && source[i] != source[matched]) matched = pi[matched - 1];
		if (source[i] == source[matched]) pi[i] = ++matched;
	}
	return pi;
}

void kmp(const string& source, const string& target) {


	vector<int> pi = getPi(target);

	for (int i = 0, matched = 0; i < sourceSize; ++i) {
		if (matched > 0 && source[i] != target[matched]) matched = pi[matched - 1];
		if (source[i] == target[matched]) {
			matched++;
			if (matched == targetSize) {
				go[i - matched + 1].push_back(i);
				matched = pi[matched - 1];
			}
		}
	}
}

int main() {
	freopen("input.txt", "r", stdin);
	ios_base::sync_with_stdio(false);

	string source, target;
	cin >> source;

	sourceSize = source.length();
	go.resize(source.length());

	int n;
	cin >> n;
	for (int i = 0; i < n; ++i) {
		cin >> target;
		targetSize = target.length();
		kmp(source, target);
	}

	dp = vector<int>(sourceSize, -1);
	cout << foo(0);
}