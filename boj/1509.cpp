#include <iostream>
#include <cstring>
#include <algorithm>
#include <string>
using namespace std;

const int MAXN = 2505;
const int INF = 2e9;

bool cal[MAXN][MAXN];				//cal[i][j] = in[i:j]�� �Ӹ�������� ���� ����
int memo[MAXN];

int foo(int index) {
	if (index == 0) return 1;
	int& ret = memo[index];
	if (ret != -1) return ret;
	ret = INF;						//�ڱ��ڽ��� �Ӹ����
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

	for (int i = 0; i < len; ++i) cal[i][i] = true;				//�ڱ��ڽ��� �ϴ� �Ӹ����
	
	for (int i = 0; i < len; ++i) {								//k = 1�� ���� ���� �������. (�� ���̰� 2�� �Ӹ����)
		if (in[i] == in[i + 1]) cal[i][i + 1] = true;
	}

	for (int k = 2; k < len; ++k) {								//k = 2 (���̰� 3�� �Ӹ����)���� �� ������ش�.
		for (int i = 0; i < len - k; ++i) {
			int j = i + k;
			cal[i][j] = (in[i] == in[j] && cal[i + 1][j - 1]);
		}
	}

	memset(memo, -1, sizeof(memo));
	cout << foo(len - 1);
}