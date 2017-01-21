/*
12844 XOR

세그먼트 트리 + lazy propagation 을 이용한 문제

입력시 주어지는 a,b의 구간에서 a,b의 대소관계가 주어지지 않아서 판단해주는 부분이 필요하다

lazy[node]의 값은 node가 표현하는 구간에 대해서 이 값으로 xor을 할 예정이라고 표시해주면 된다.
또한 lazy의 값을 계산해야되는 순간에 이용할수 있는 방법은 같은 수를 xor하면 0이 되고 0과 xor를 하면 자기 자신이 됨을 이용하는 것이다.

node가 표현하는 범위의 lazy를 계산하려면 자식들을 모두 xor한 수를 얻어야 한다. 현재 가지고 있는것은 왼쪽 자식의 전체 xor값인 ans[node*2]와 오른쪽 자식의 ans[node*2+1]이다.
이 둘을 xor한 것에 lazy를 자식의 숫자만큼 xor해주면 된다. (순서는 중요하지 않으므로)
그런데 이것을 빠르게 하는 방법은 자식의 숫자가 짝수라면 xor를 짝수번 하게 되어 결국은 0 이되게 된다 그렇게 되면 전체의 xor결과에는 아무 영향을 미치지 못한다.
홀수라면 한번 xor한것과 같으므로 위의 결과에 lazy[node]값을 xor시켜준 값을 얻으면 된다.

이렇게 구현하여 xor를 구간으로 만드는 세그먼트 트리를 구성하여 쿼리에 답을 해주면 된다.!
*/
#include <cstdio>
#include <vector>
#include <algorithm>
using namespace std;

vector<int> ans;
vector<int> arr;
vector<int> lazy;			//lazy[node] = node가 표현하는 구간을 이 값으로 xor할 예정이야!

int init(int nodeLeft, int nodeRight, int node) {
	if (nodeLeft == nodeRight)
		return ans[node] = arr[nodeLeft];
	int mid = (nodeLeft + nodeRight) / 2;
	return ans[node] = (init(nodeLeft, mid, node * 2) ^ init(mid + 1, nodeRight, node * 2 + 1));
}

void propagate(int nodeLeft, int nodeRight, int node) {
	if (lazy[node] != 0) {
		if (nodeLeft != nodeRight) {
			lazy[node * 2] ^= lazy[node];
			lazy[node * 2 + 1] ^= lazy[node];
		}
		
		if ((nodeRight - nodeLeft + 1) % 2 != 0)
			ans[node] ^= lazy[node];
		lazy[node] = 0;
	}
}

void update(int left, int right, int value, int node, int nodeLeft, int nodeRight) {
	propagate(nodeLeft, nodeRight, node);

	if (right < nodeLeft || left > nodeRight)
		return;
	if (left <= nodeLeft && nodeRight <= right) {
		lazy[node] ^= value;
		propagate(nodeLeft, nodeRight, node);
		return;
	}

	int mid = (nodeLeft + nodeRight) / 2;
	update(left, right, value, node * 2, nodeLeft, mid);
	update(left, right, value, node * 2 + 1, mid + 1, nodeRight);
	ans[node] = (ans[node * 2] ^ ans[node * 2 + 1]);
}

int query(int left, int right, int node, int nodeLeft, int nodeRight) {
	propagate(nodeLeft, nodeRight, node);
	if(right < nodeLeft || left > nodeRight)
		return 0;
	if (left <= nodeLeft && nodeRight <= right)
		return ans[node];
	int mid = (nodeLeft + nodeRight) / 2;
	return query(left, right, node * 2, nodeLeft, mid) ^ query(left, right, node * 2 + 1, mid + 1, nodeRight);
}

int main() {
	freopen("input.txt", "r", stdin);
	int n;
	scanf("%d", &n);

	arr.resize(n);
	ans.resize(4*n);
	lazy.resize(4 * n);

	for (int i = 0; i < n; ++i)
		scanf("%d", &arr[i]);

	init(0, n - 1, 1);
	int m;
	scanf("%d", &m);
	int a, b, c, d;
	for (int i = 0; i < m; ++i) {
		scanf("%d", &a);
		if (a == 1) {
			scanf("%d %d %d", &b, &c, &d);
			if (b > c)
				swap(b, c);
			update(b, c, d, 1, 0, n - 1);
		}
		else {
			scanf("%d %d", &b, &c);
			if (b > c)
				swap(b, c);
			printf("%d\n", query(b, c, 1, 0, n - 1));
		}
	}
}