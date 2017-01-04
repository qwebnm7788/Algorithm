//2-SAT ���� �׷��� ���� ����
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

//�׷����� ��������Ʈ ǥ��
vector<vector<int>> adj;

//ȸ�ǽð��� ���� ��ġ�� ������ true�� �����Ѵ�.
bool disjoint(const pair<int, int>& a, const pair<int, int>& b) {
	return a.second <= b.first || b.second <= a.first;
}

//meetings[]�� �� ���� ���ϴ� ȸ�� �ð��� ���
//i�� ���� ���ϴ� �ð��� meetings[2*i] �Ǵ� meetings[2*i+1]�� �ϳ��̰� �� �� �ϳ��� �� �ؾ� �Ѵ�.
//���� �׷��� ���� �Լ�
void makeGraph(const vector<pair<int, int>>& meetings) {
	int vars = meetings.size();

	//�׷����� �� �������� �ΰ��� ������ ���´�. (x||y) �� x -> !y �� y -> !x �� ǥ�������ϴϱ�
	adj.clear();
	adj.resize(vars * 2);
	for (int i = 0; i < vars; i += 2) {
		//�켱 ���⼭�� (i||j)���� �߰��Ѵ�. �� �� �ϳ��� ���ؾ� �ϴϱ� !
		int j = i + 1;
		adj[i * 2 + 1].push_back(j);		//!i -> j
		adj[j * 2 + 1].push_back(i);		//!j -> i
	}

	//i�� ȸ�ǿ� j�� ȸ�ǰ� ��ġ�� ȸ�Ƕ�� �� ���� �߻��ؼ��� �ȵǴ� ģ���̹Ƿ� (!i || !j) ���� �߰����ָ� �ȴ�. -- �� ���ÿ� ���� ���� �ʴ� ���� �߰�.!
	for (int i = 0; i < vars; ++i) {
		for (int j = 0; j < i; ++j) {
			if (!disjoint(meetings[i], meetings[j])) {
				//i�� �� ������ �ʰų� j���� ������ �ʴ� ���� !
				//(!i || !j) �� i -> !j �� j -> !i�� ǥ�������ϴ�.
				adj[2 * i].push_back(2 * j + 1);
				adj[2 * j].push_back(2 * i + 1);
			}
		}
	}
}


/*
���� ���� � �� (X||Y)�� �����̶�� !X -> Y �̰� !Y -> X�� ģ������ ���� �Ǵµ�
�̰� �� ���� (X||Y)�� �����̴ϱ� X �� Y��� �����̰� !X->Y �� �� -> ����
!Y->X�� �� -> ������ ģ������ �� �� �־�
�׷��ϱ� �� -> �������� ���� ģ���� ���Բ� �ִ��� ���ָ� ��� ���� ������ ���� �츮�� ���ϴ� ���ǽ���
������ ������� �� ��������

1. x ������ !x ������ �ϳ��� ��, �ϳ��� �������� �з��ǵ��� �Ѵ�.
2. �׸��� �� -> �������� ���� ��δ� ����.

�� �� ������ �����ϸ鼭 ���� �׷����� ���� �� �� �ִٸ� �ظ� ���� �� �ִ�.

�̰� �������� �ʴ� ��츦 ���� ���� ��� �� ����Ŭ�� x������ !x������ ��� �����ִ� ����
����Ŭ�� ��� ���ۺ��� ���µ� x -> ... -> !x -> ... -> x �� �Ǵµ� x�� !x�� �� �� �ϳ���
������ �ɲ��� �׷��� �� -> ������ ��ΰ� ����� �Ǵϱ� ���� ������ �������� ���ϰ� ���� !

�̷� �׷����� ������ SCC�� ǥ���� �� �־�

Ư¡�� �̰� x�� !x�� ���� ��Ī���� �Ӽ��� ������
SCC�� �������ָ� �׷����� ��Ī�� �׷����� ����ٴ°�

���� �� ������ �׷����� �̿��ؼ� 2-SAT�� Ǯ��� �� ���� �׷����� DAG���� �� �� �ְ�
���⼭ indeg�� 0 �� ģ���� �ϴ� �� ã��
�׸��� �� �߿� �� ģ���� �ִ��� �������� �з��Ѵ�����
�׿� ��Ī�Ǵ� ������ ������ ����� �ְ� �� ������ �����ָ� �ȴ�.

�� ������ ��� �ݺ��ϸ� �ȴ�.

�̰� �� �ǳĸ� p->q���� p�� �������� ����� �ָ� q�� �����̴� ���̴� �� ������ �׻� ���̾�
�׷��� ���ظ� �� ���� ����

���࿡ ���⼭ indeg = 0�� ģ���� ����µ� �̹� ������ �з��� �Ǿ��ִٸ� �� ģ���� �׳� �ǳ� �ٸ� �ǰ�¡?

*/

vector<int> solve2SAT() {
	int n = adj.size() / 2;		//������ ��! �׷����� ũ��� �ι�ϱ� ����

	//���� �׷����� SCC�� ��Һ��� ���´�.
	vector<int> label = tarjanSCC();		//tarjanSCC�� SCC ������Ʈ�� �з��� ���

	//�� SAT ������ �ذ� �������� Ȯ��
	//���࿡ x�� !x�� �ϳ��� SCC�� ���Ѵٸ� �Ұ��� �ϰ��� �� -> ������ ����ϱ�
	for (int i = 0; i < 2 * n; i += 2) {
		if (label[i] == label[i + 1])
			return vector<int>();	//�ȵŸ� �׳� �� ����
	}

	//�����ϴٸ�
	vector<int> value(2 * n, -1);

	//Ÿ�� �˰������� SCC�� ���������� �������� ��ȣ�� �ű�� Ư¡�� �̿��ϸ�
	//���� �����ϰ� ���������� �ʿ� ���� �ٷ� ���� ���� �� �ִ�.
	vector<pair<int, int>> order;
	for (int i = 0; i < 2 * n; ++i) {
		order.push_back(make_pair(-label[i], i));		//�������� ���������� SCC�� ��ȣ�� ������ �ٿ��� �����ߵ�.
	}
	sort(order.begin(), order.end());		//�׷��� �̰� �ϸ� ���������� ������ order�� ���� �ȴ�. order.second�� ������ȣ!

	//�� ������ ���� ����
	for (int i = 0; i < 2 * n; ++i) {
		int vertex = order[i].second;
		int variable = vertex / 2;	
		int isTrue = vertex % 2 == 0;
		if (value[variable] != -1)		//�̹� ������ ģ���� �ǳʶٰ�
			continue;

		//���� ������ ������ �������� ����� �ָ� �ȴ�.
		//!x�� x���� ���� ���Դٸ� x�� ��
		//x�� !x���� ���� ���Դٸ� x�� ����
		value[variable] = !isTrue;		//variable�� ���� isTrue�� ������ ������
		//variable(x)�� ������ ���������� vertex�� ���� ���̶�� 2*i�ϱ� 0���� istrue�� ���̰�
		//���� ������ ���� �����ٸ� 2*i+1�� isTrue�� ������ �Ǵϱ� ������ �ȴ�.
		//������ �̹� ���� ������ ģ���� �ǳʶٴϱ� ���� �ϳ��� ���� ������� �� �� �ִ�.
	}

	return value;

}