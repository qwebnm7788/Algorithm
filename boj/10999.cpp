/*
10999 구간 합 구하기2

Lazy Propagation !
*/
#include <cstdio>
#include <vector>
#include <algorithm>
using namespace std;

vector<long long> arr;
vector<long long> lazy;
vector<long long> ans;

long long init(int nodeLeft, int nodeRight, int node) {
	if (nodeLeft == nodeRight)
		return ans[node] = arr[nodeLeft];
	int mid = (nodeLeft + nodeRight) / 2;
	return ans[node] = init(nodeLeft, mid, node * 2) + init(mid + 1, nodeRight, node * 2 + 1);
}

void propagate(int nodeLeft, int nodeRight, int node) {
	if (lazy[node] != 0) {
		if (nodeLeft != nodeRight) {
			lazy[node * 2] += lazy[node];
			lazy[node * 2 + 1] += lazy[node];
		}
		ans[node] += (nodeRight - nodeLeft + 1)*lazy[node];
		lazy[node] = 0;
	}
}

void update(int left, int right, int value, int node, int nodeLeft, int nodeRight) {
	propagate(nodeLeft, nodeRight, node);

	if (right < nodeLeft || left > nodeRight)
		return;
	if (left <= nodeLeft && nodeRight <= right) {
		lazy[node] += value;
		propagate(nodeLeft, nodeRight, node);
		return;
	}

	int mid = (nodeLeft + nodeRight) / 2;
	update(left, right, value, node * 2, nodeLeft, mid);
	update(left, right, value, node * 2 + 1, mid + 1, nodeRight);
	ans[node] = (ans[node * 2] + ans[node * 2 + 1]);
}

long long query(int left, int right, int node, int nodeLeft, int nodeRight) {
	propagate(nodeLeft, nodeRight, node);
	if (right < nodeLeft || left > nodeRight)
		return 0;
	if (left <= nodeLeft && nodeRight <= right)
		return ans[node];
	int mid = (nodeLeft + nodeRight) / 2;
	return query(left, right, node * 2, nodeLeft, mid) + query(left, right, node * 2 + 1, mid + 1, nodeRight);
}


int main() {
	int n, m, k;
	scanf("%d %d %d", &n, &m, &k);

	arr.resize(n);
	ans.resize(4 * n);
	lazy.resize(4 * n);

	for (int i = 0; i < n; ++i)
		scanf("%d", &arr[i]);

	init(0, n - 1, 1);

	long long a, b, c, d;
	for (int i = 0; i < m + k; ++i) {
		scanf("%lld", &a);
		if (a == 1) {
			scanf("%lld %lld %lld", &b, &c, &d);
			update(b - 1, c - 1, d, 1, 0, n - 1);
		}
		else {
			scanf("%lld %lld", &b, &c);
			printf("%lld\n", query(b - 1, c - 1, 1, 0, n - 1));
		}
	}
}
