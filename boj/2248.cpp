/*
������ �ִ��� �ڸ����� 31�ڸ��̰� 31 31 2^31�� �����°��� �ִ��� ����� ���� �ȴ�.
2^31 -1 �� �ƴ� 2^31�� ������ 00000000000000000000000000000000�� ù��°(1)�� �Ű����� �����̴�
���� �Է¿��� ������ i�� int���� ������ 1��ŭ ��� �� �ֱ� ������ �̿� �����Ͽ�
long long ���·� �޾��־�� �Ѵ�.
*/
#include <iostream>
#include <cstring>
#include <algorithm>
using namespace std;

const int MAXN = 32;
const int MAXL = 32;

int memo[MAXN][MAXL];
char answer[MAXN];

//foo(n,l) = n�ڸ� ������ �� 1�� ������ l������ �������� ����
int foo(int n, int l) {
	if (n == 0 || l == 0) return 1;
	int& ret = memo[n][l];
	if (ret != -1) return ret;
	ret = foo(n - 1, l);			//n��° �ڸ��� 0 �� ���
	if (l) ret += foo(n - 1, l - 1);			//n��° �ڸ��� 1�ΰ��
	return ret;
}

//sol(n,l,found,index) = n�ڸ� ������ �� 1�ǰ����� l�������� ������ �� (ũ������� ����) found���� ���� ������
void sol(int n, int l, long long found, int index) {
	if (l < 0) return;
	if (n == 0) {
		for (; index < n; ++index) answer[index] = '0';
		return;
	}
	int temp = foo(n-1, l);				//N��° ���� 0�� ���
	if (found <= temp) {				//���� ���ٸ� N��° ���� 0�� ģ���� ����		(ũ�� ���̹Ƿ� 0���� ���� �˻�����)
		answer[index] = '0';
		sol(n - 1, l, found, index + 1);
	}
	else {							//�װ� �ƴϸ� N��° ���� 1�̴�.
		answer[index] = '1';
		sol(n - 1, l - 1, found - temp, index + 1);
	}
}
int main() {
	int n, l;
	long long i;
	cin >> n >> l >> i;
	memset(memo, -1, sizeof(memo));
	sol(n, l, i, 0);
	for (int i = 0; i < n; ++i) cout << answer[i];
}