/*
Lazy Propagation

���׸�Ʈ Ʈ���� ����Ǵ� �����̴�.

������ ���׸�Ʈ Ʈ������ update�� ���ϴ� ������ Ư�������� ���� ���� ���ϴ� query������ �־���.

�׷��� Ư���� ����[a,b]�� ���ؼ� ���ÿ� �� x�� ���Ѵٰ� �����غ��� (���Ѵٴ� ������ �׶��׶��� Ʈ���� ������ ���� �ٸ� �� �ִ�.)
���� ���� �ϴ����� �������شٸ� a~b�� ��� index�� ���ؼ� update�� ���������ν� �����س� �� �ִ�.
���ϴ� ������ ���̸� k(=b-a+1)�̶�� �ϸ� �� ���������� O(logN) (N�� ��ü������ ��)�� ó���ǹǷ�
O(klogN)�� ������ �ټ� �ְ� k�� �ִ� n���� Ŀ���Ƿ� �ð����⵵�� O(nlogn)�� �ȴ�.

�׷��� �̸� O(logN)�� �����ϴ� ����� �ִµ� �̴� lazy propagation�� �̿��ϴ� ����̴�.!

������ ������� ���׸�Ʈ Ʈ������ �����ϵ��� ���ָ� �Ǵµ� ���⼭ �߰��� �������־�� �ϴ� ����
���׸�Ʈ Ʈ���� �� ��帶�� lazy��� �迭�� ���� ����� �ִ°��̴�.

lazy�迭�� �� ��尡 ǥ���ϴ� ������ ���ؼ� �󸶸�ŭ ���� ��ȹ�� ������ �˷��ִ� �迭�� �ȴ�. 
->�׷����� ������ ���� �������� ��������

���� lazy���� �ִ� ���� ���� ���� �ʿ��� ������ ���´ٸ� �� lazy���� ������ ���·� ���� ��ȯ�� �־�� �Ѵ�.
�̶� Ư�� ����� lazy���� �����ϴ� �������� �����´ٸ� ���� �� ģ���� ������ְ� �ڽ��� �ڽĵ鿡�� lazy�� �Ѱ��ִµ�
�� �Ѱ��ִ� ���� lazy propagation �̶�� �Ѵ�.

�̷������� ��� �̷�� ���� ���������� �������� �Ǵµ� �̶��� ���̻� �̷� ģ���� �����ϱ�
��¿�� ���� �ڽ��� ���� lazy���� ��������ָ� �ȴ�.

*/

/*
���ϴ� ������ ��� ���� ��忡 ���������� ���� lazy�� �ִٸ� lazy�� propagation���ְ� �� ���� ���� ���·� ��ȯ�� ���ָ� �Ǵµ�
���Ҷ��� �ڽ��� �����ϴ� ��� �������� lazy���� ���߾�� �ϴ°Ŵϱ� (�ڽ��� �����ϴ� ������ ���� * lazy��)�� �����־�� �Ѵ�.

�������� ���Դٸ� �׳� �ڽ��� ���� �����ִ°� ����

�׷��� �����ؾ� �� ���� �ִ� propagation�� �������� �Ѱ��־��ٸ� ������ ���ߵ��� ������ �������� ���� �׳� �ڽ��� ���� ���ϴ� ���·� �Ͽ��ٸ� (lazy�� �δ°� �ƴϰ�)
���� ģ������ ���� �������־�� �Ѵ�. (�ֳĸ� �ڽ��� ǥ���ϴ� �������� ������ ���߱� ������ -> �� �� ������带 �����ϴ� ������ ���� ��� ���ŵǾ�� �� -> ������ ���׸�Ʈ Ʈ��ó��)
���� �ڽĵ�� propagation�� ������ �������� �ڽ��� ���� �������ִ� ������ �߰������� �ʿ��ϴ� ! (������ �����ϴ� ���̽��� �ֱ� ����)
*/

//�������� ǥ���ϴ� ���׸�Ʈ Ʈ���� lazy propagation ������ ���� 
#include <algorithm>
#include <vector>
using namespace std;

vector<long long> arr;
vector<long long> lazy;
vector<long long> ans;

long long init(int nodeLeft, int nodeRight, int node) {
	if (nodeLeft == nodeRight)
		return ans[node] = arr[nodeLeft];
	int mid = (nodeLeft+nodeRight) / 2;
	return ans[node] = init(nodeLeft, mid, node * 2) + init(mid + 1, nodeRight, node * 2 + 1);
}

//[nodeLeft,nodeRight] ������ ǥ���ϴ� node�� lazy���� �ڽĿ��� propagate�Ѵ�.
void propagate(int node, int nodeLeft, int nodeRight) {
	//lazy���� �����Ѵٸ�
	if (lazy[node] != 0) {

		//������尡 �ƴϸ� �ڽ����� �̷���
		if (nodeLeft != nodeRight) {
			lazy[node * 2] += lazy[node];
			lazy[node * 2 + 1] += lazy[node];
		}

		//�ڽ��� ���� ������ �ش��ϴ� ��ŭ �����ָ� �ȴ�.
		ans[node] += lazy[node] * (nodeRight - nodeLeft + 1);
		lazy[node] = 0;
	}
}

//[left,right]�� ������ value��ŭ�� ���� update��Ų��.
void update(int left, int right, int value, int node, int nodeLeft, int nodeRight) {
	//�켱 propagate ��Ų��. (����ģ����� �׳� ����ǰ���)
	propagate(node,nodeLeft,nodeRight);
	//������ ���Ե��� ������ ����
	if (right < nodeLeft || left > nodeRight)
		return;
	//�� ����� ǥ�������� ������ ������ ���ԵǸ� lazy�� �� ��忡 �ο��� �Ŀ�
	//propagte�ؼ� ���� ����ϰ� ��ȯ�ϸ� �ǰ�
	//lazy�� �� �ڽĵ鿡�� ������ �Ѵ�.
	//�׸��� ����
	if (left <= nodeLeft && nodeRight <= right) {
		lazy[node] += value;
		propagate(node, nodeLeft, nodeRight);
		return;
	}

	//������ ���� �� ũ�ٸ� ������ �ɰ�����.
	int mid = (nodeLeft + nodeRight) / 2;
	update(left, right, value, node * 2, nodeLeft, mid);
	update(left, right, value, node * 2 + 1, mid + 1, nodeRight);

	//update�� �Ŀ� ���� ������ ��ȭ�����־�� �Ѵ�.
	//�ֳĸ� �� ģ������ leaf�� �������� �� �ֱ� �����̴�.?
	//�׳� ���� = �ӿ� ���� ! 
	ans[node] = ans[node * 2] + ans[node * 2 + 1];
}

//[left,right]�� �������� ��ȯ�Ѵ�.
long long query(int left, int right, int node, int nodeLeft, int nodeRight) {
	//�־��� ������ lazy�� �����ϴ� ģ���� ������ �� �����Ƿ�
	//���ϴ� ������ �������鼭 propagation�� ���� ������ �Ŀ� ���� ���Ѵ�.
	propagate(node, nodeLeft, nodeRight);

	if (right < nodeLeft || left > nodeRight)
		return 0;
	if (left <= nodeLeft && nodeRight <= right)
		return ans[node];
	int mid = (nodeLeft + nodeRight) / 2;
	return query(left, right, node * 2, nodeLeft, mid) + query(left, right, node * 2 + 1, mid + 1, nodeRight);
}


//�̷��� ������ �ϰ� �Ǹ� �� ������ ���� ������ O(klogN)�� �ƴ� O(logN)���� ó�� �� �� �ִ�.