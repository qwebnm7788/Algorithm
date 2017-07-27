#include <iostream>
#include <cstring>
#include <algorithm>
#include <limits>
using namespace std;

const int MAXN = 101;
const long long INF = 1e9 + 5;

long long memo[MAXN][MAXN];
char answer[MAXN + MAXN];
int n, m;
long long k;

//foo(a,z) 'a'�� a�� 'z'�� z�� �������� ���� �� �ִ� ���ڿ��� ������
//�̶� �����ؾ� �� ���� a,z�� k�� �ִ밪�� 1e9�� ���� �� ���� ����� �� �� �ֱ⶧����
//1e9�� �̻� �Ѿ�� �׳� 1e9���� ĿƮ���ְ� sol���� ���� ã�� ������.
//�� a,z�� �������δ� long long�� ǥ�������� �Ѿ�� ���� ������ ���� ��������
//����� k�� 1e9 �����̹Ƿ� �׳� 1e9�� ĿƮ���ش�.
long long foo(int a, int z) {
	if (a == 0 || z == 0) return 1;
	long long& ret = memo[a][z];
	if (ret != -1) return ret;
	ret = min(foo(a - 1, z) + foo(a, z - 1),INF);
	return ret;
}

//sol(a,z,found,x) = 'a'�� a�� 'z'�� z�� �������� found������ ģ���� ã�°� (x�� ����������)
void sol(int a, int z, long long found, int x) {
	//��� ��쿡�� n+m�ڸ��� ���ڰ� �ǹǷ�
	if (a == 0) {						//a�� �� �������� ���� �ڸ��� z�� ä��� �ǰ�
		for (; x < n + m; ++x) answer[x] = 'z';
		return;
	}
	if (z == 0) {						//z�� �� �������� ���� �ڸ��� a�� ä��� �ȴ�.
		for (; x < n + m; ++x) answer[x] = 'a';
		return;
	}
	long long temp = foo(a - 1, z);			//a�� ����������
	if (found <= temp) {					//found�� �װͺ��� �۴ٸ� ���� �ڸ������� a�� ���°� �´�.
		answer[x] = 'a';
		sol(a - 1, z, found, x + 1);
	}
	else {									//�ƴ϶�� z�� �����ϰ� found - temp�� ��ŭ�� ã���ش�.
		answer[x] = 'z';
		sol(a, z - 1, found - temp, x + 1);
	}
}

int main() {
	cin >> n >> m >> k;
	memset(memo, -1, sizeof(memo));
	long long test = foo(n, m);
	if (test < k) cout << "-1";
	else {
		sol(n, m, k, 0);
		for (int i = 0; i < n + m; ++i) cout << answer[i];
	}
}