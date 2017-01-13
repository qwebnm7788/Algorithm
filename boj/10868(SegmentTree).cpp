#include <stdio.h>
#include <vector>
#include <algorithm>
#include <limits>
using namespace std;

const int INF = numeric_limits<int>::max();

vector<int> arr;
vector<int> ans;

int init(int left, int right, int node) {
	if (left == right)
		return ans[node] = arr[left];
	int mid = (left + right) / 2;
	return ans[node] = min(init(left, mid, node * 2), init(mid + 1, right, node * 2 + 1));
}

int query(int left, int right, int node, int nodeLeft, int nodeRight) {
	if (right < nodeLeft || left > nodeRight)
		return INF;
	if (left <= nodeLeft && nodeRight <= right)
		return ans[node];
	int mid = (nodeLeft + nodeRight) / 2;
	return min(query(left, right, node * 2, nodeLeft, mid), query(left, right, node * 2 + 1, mid + 1, nodeRight));
}

int main() {
	freopen("input.txt", "r", stdin);
	int n, m;
	scanf("%d %d", &n, &m);

	arr.resize(n);
	ans.resize(4 * n);

	for (int i = 0; i < n; ++i)
		scanf("%d", &arr[i]);

	init(0, n - 1, 1);

	int a, b;
	for (int i = 0; i < m; ++i) {
		scanf("%d %d", &a, &b);
		printf("%d\n", query(a - 1, b - 1, 1, 0, n - 1));
	}
}