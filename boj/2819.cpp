/*
�ܼ��ϰ� �ùķ��̼� �Ͽ� ��� instruction�� ���ƺ���
�Ź� �Ÿ��� ������ְ� �Ǹ� O(NM)�� �Ǿ� �ð��ʰ��� �ް� �ȴ�.

��� �������� ��ġ�� x��ǥ, y��ǥ�� ���� �����ϴ� �迭�� ����� �ְ�
����������.

�� �ܰ��� ��ɾ ���� (0,0)���� ������ ��ġ�� ���Ž����ָ鼭 
������ ���� ������ ��ȭ���� ������ �� �ִ�.

1) ���� �������� �̵��Ѵٸ�
cY�� ������ (���� y��ǥ�� ����) ���ʿ� �ִ� ������������ �Ÿ��� ��� -1�� �� ���̴�.
�ؿ� �ִ� �����鿡�Դ� ��� +1�� �� ȿ���� ����

cY �ؿ� �ִ� ������ ������ F��� �Ѵٸ� �� ģ������ ������ lower_bound �� �̿��Ͽ� cY�� �˻��Ͽ� O(logM)�� ������ �� �ִ�
2) ���� �������� �̵��Ѵٸ�
����ϰ� cY�� ������ �Ʒ��� ������ ���������� ��� �Ÿ��� -1���� �� ���̰�
���� �ִ� ģ���鿡�Դ� +1���� �ɰ��̴�.

�Ʒ��� ģ������ upper_bound�� ������ ������ �� �ִ�.( �̹����� cY�� ���� ������ �����ؾ� �ϹǷ� upper_bound�� ����Ͽ���)
�̷��� �Ǹ� ������ ���� answer �� answer = answer - F + (n-F)  �� F��ŭ -1�� �ǰ� �� �� ������ (n-F) ��ŭ + 1�� �ȴ�.

������ ����, ���ʿ� ���ؼ��� ����� ������� ���������ν�
O(NlogM)�� ������ ������ �� �ִ�.

cin , cout�� ����ϰ� �Ǹ� �ð��ʰ��� �����Ƿ� scanf,printf �Լ��� �̿�����.
*/
#include <cstdio>
#include <vector>
#include <string>
#include <cmath>
#include <algorithm>
using namespace std;

const int MAXM = 300005;

int main() {
	int n, m;
	scanf("%d %d", &n, &m);

	long long answer = 0;

	vector<int> xcor(n), ycor(n);
	for (int i = 0; i < n; ++i) {
		scanf("%d %d", &xcor[i], &ycor[i]);
		answer += abs(xcor[i]) + abs(ycor[i]);
	}

	sort(xcor.begin(), xcor.end());
	sort(ycor.begin(), ycor.end());

	char inst[MAXM];
	scanf("%s", inst);

	int cX, cY;
	cX = cY = 0;

	for (int i = 0; i < m; ++i) {
		if (inst[i] == 'S') {		//north
			cY++;
			answer += 2 * (lower_bound(ycor.begin(), ycor.end(), cY) - ycor.begin()) - n;
		}
		else if (inst[i] == 'J') {	//south
			cY--;
			answer += n - 2 * (upper_bound(ycor.begin(), ycor.end(), cY) - ycor.begin());
		}
		else if (inst[i] == 'I'){	//east
			cX++;
			answer += 2 * (lower_bound(xcor.begin(), xcor.end(), cX) - xcor.begin()) - n;
		}
		else{						//west
			cX--;
			answer += n - 2 * (upper_bound(xcor.begin(), xcor.end(), cX) - xcor.begin());
		}
		
		printf("%lld\n", answer);
	}
}