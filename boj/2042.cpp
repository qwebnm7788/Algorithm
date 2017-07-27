#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

vector<long long> arr, segtree;

long long init(int node, int nodeLeft, int nodeRight) {
	if (nodeLeft == nodeRight) return segtree[node] = arr[nodeLeft];
	int mid = (nodeLeft + nodeRight) / 2;
	return segtree[node] = init(node * 2, nodeLeft, mid) + init(node * 2 + 1, mid + 1, nodeRight);
}

long long update(int index, int value, int node, int nodeLeft, int nodeRight) {
	if (index < nodeLeft || index > nodeRight) return segtree[node];
	if (nodeLeft == nodeRight) return segtree[node] = value;
	int mid = (nodeLeft + nodeRight) / 2;
	return segtree[node] = update(index, value, node * 2, nodeLeft, mid) + update(index, value, node * 2 + 1, mid + 1, nodeRight);
}

long long query(int left, int right, int node, int nodeLeft, int nodeRight) {
	if (right < nodeLeft || left > nodeRight) return 0;
	if (left <= nodeLeft && nodeRight <= right) return segtree[node];
	int mid = (nodeLeft + nodeRight) / 2;
	return query(left, right, node * 2, nodeLeft, mid) + query(left, right, node * 2 + 1, mid + 1, nodeRight);
}

int main() {
	ios_base::sync_with_stdio(false);
	int n, m, k;
	cin >> n >> m >> k;

	arr.resize(n);
	segtree.resize(4 * n);
	for (int i = 0; i < n; ++i) cin >> arr[i];

	init(1, 0, n - 1);

	int a, b, c;
	for (int i = 0; i < m + k; ++i) {
		cin >> a >> b >> c;
		if (a == 1) {
			update(b - 1, c, 1, 0, n - 1);
		}
		else {
			cout << query(b - 1, c - 1, 1, 0, n - 1) << endl;
		}
	}
}