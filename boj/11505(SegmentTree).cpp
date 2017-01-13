/*
11505
저장되는 숫자 자체는 int형의 범위를 넘지 못하지만(mod연산으로)
곱셈 과정 중간에서(곱한 후에 mod연산 직전) int형을 넘어갈 수 있으므로 long long 형을 사용하거나 다른 접근 방법을 찾아야 한다.
*/
#include <stdio.h>
#include <algorithm>
#include <vector>
#include <limits>
using namespace std;

const int MAX = 1000000007;

vector<int> arr;
vector<int> ans;

long long init(int left, int right, int node) {
	if (left == right)
		return ans[node] = arr[left];
	int mid = (left + right) / 2;
	return ans[node] = (init(left, mid, node * 2)*init(mid + 1, right, node * 2 + 1)) % MAX;
}

long long update(int index, int value, int node, int nodeLeft, int nodeRight) {
	if (index < nodeLeft || index > nodeRight)
		return ans[node];
	if (nodeLeft == nodeRight)
		return ans[node] = value;
	int mid = (nodeLeft + nodeRight) / 2;
	return ans[node] = (update(index, value, node * 2, nodeLeft, mid) * update(index, value, node * 2 + 1, mid + 1, nodeRight)) % MAX;
}

long long query(int left, int right, int node, int nodeLeft, int nodeRight) {
	if (right < nodeLeft || left > nodeRight)
		return 1;
	if (left <= nodeLeft && nodeRight <= right)
		return ans[node];
	int mid = (nodeLeft + nodeRight) / 2;
	return (query(left, right, node * 2, nodeLeft, mid)*query(left, right, node * 2 + 1, mid + 1, nodeRight)) % MAX;
}
int main() {
	freopen("input.txt", "r", stdin);
	int n, m, k;
	scanf("%d %d %d", &n, &m, &k);

	arr.resize(n);
	ans.resize(4 * n);

	for (int i = 0; i < n; ++i)
		scanf("%d", &arr[i]);

	init(0, n - 1, 1);

	int a, b, c;
	for (int i = 0; i < m + k; ++i) {
		scanf("%d %d %d", &a, &b, &c);
		if (a == 1)
			update(b - 1, c, 1, 0, n - 1);
		else
			printf("%d\n", query(b - 1, c - 1, 1, 0, n - 1) % MAX);
	}
}