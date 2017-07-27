#include <iostream>
#include <cstring>
#include <algorithm>
#include <string>
using namespace std;

const int MAXN = 2505;
const int INF = 2e9;

bool cal[MAXN][MAXN];				//cal[i][j] = in[i:j]가 팰린드롬인지 여부 저장
int memo[MAXN];

int foo(int index) {
	if (index == 0) return 1;
	int& ret = memo[index];
	if (ret != -1) return ret;
	ret = INF;						//자기자신은 팰린드롬
	for (int next = index; next >= 0; --next) {
		if (cal[next][index]) {
			ret = min(ret, foo(next - 1) + 1);
		}
	}
	return ret;
}

int main() {
	string in;
	cin >> in;

	int len = in.length();

	for (int i = 0; i < len; ++i) cal[i][i] = true;				//자기자신은 일단 팰린드롬
	
	for (int i = 0; i < len; ++i) {								//k = 1인 경우는 따로 계산하자. (즉 길이가 2인 팰린드롬)
		if (in[i] == in[i + 1]) cal[i][i + 1] = true;
	}

	for (int k = 2; k < len; ++k) {								//k = 2 (길이가 3인 팰린드롬)부터 다 계산해준다.
		for (int i = 0; i < len - k; ++i) {
			int j = i + k;
			cal[i][j] = (in[i] == in[j] && cal[i + 1][j - 1]);
		}
	}

	memset(memo, -1, sizeof(memo));
	cout << foo(len - 1);
}