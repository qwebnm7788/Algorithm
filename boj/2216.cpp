/*
2216 문자열과 점수

foo(first,second) = X[first:]와 Y[second:]로 이루어진 문자열로 얻을 수 있는 최대의 점수를 반환
foo(first,second) = max(둘다 공백이 아닐때, X가 공백, Y가 공백)으로 얻을 수 있다.
주의할 점은 둘의 원래길이보다도 더 긴 것이 정답일 수 있다. 또한 -1도 정답으로 나올수 있어서 dp테이블 초기화에 유의해야 한다.
둘다 동시에 끝에 도달한다면 아무 처리를 안해주어도 되지만
둘중 하나가 먼저 끝난다면 남은 친구는 공백과 대응된다고 할 수 있으므로 처리해주면 된다.
*/
#include <iostream>
#include <string.h>
#include <string>
#include <algorithm>
using namespace std;

const int INF = 987654321;
const int MAXLEN = 3001;

int cache[MAXLEN][MAXLEN];
int a, b, c;
string X, Y;

int foo(int first, int second) {
	if (first == X.length() || second == Y.length()) {
		if (first == X.length() && second == Y.length()) return 0;
		else if (first == X.length()) return (Y.length() - second)*b;
		else return (X.length() - first)*b;
	}
	//둘다 공백이 아닌경우
	int& ret = cache[first][second];
	if (ret != -INF) return ret;
	ret = foo(first + 1, second + 1) + ((X[first] == Y[second]) ? a : c);

	//Y번 친구가 공백인 경우
	ret = max(ret, foo(first + 1, second) + b);
		
	//X번 친구가 공백인 경우
	ret = max(ret, foo(first, second + 1) + b);
	return ret;
}
int main() {
	freopen("input.txt", "r", stdin);

	cin >> a >> b >> c;
	cin >> X >> Y;
	memset(cache, -1, sizeof(cache));
	for (int i = 0; i < MAXLEN; ++i)
		for (int j = 0; j < MAXLEN; ++j)
			cache[i][j] = -INF;
	cout << foo(0, 0);
}