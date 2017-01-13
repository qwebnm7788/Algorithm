/*
각 노드의 표현을 표현하는 구간의 값의 총합으로 하면 된다.
값의 범위는 x가 -10e9~10e9 이고 최대 10e6일을 살 수 있으므로 최대 10e15을 표현할 수 있는
long long 값을 이용하면 된다. (update의 value값도 long long 형으로 수정!)
update 의 구현을 ans[node] = value 가 아닌 ans[node] += value로 수정하면 간단하게 풀 수 있다.
*/
#include <stdio.h>
#include <vector>
#include <algorithm>
#include <limits>
using namespace std;

vector<long long> arr;
vector<long long> ans;

long long init(int left, int right, int node) {
	if (left == right)
		return ans[node] = arr[left];
	int mid = (left + right) / 2;
	return ans[node] = init(left, mid, node * 2) + init(mid + 1, right, node * 2 + 1);
}

long long query(int left, int right, int node, int nodeLeft, int nodeRight) {
	if (nodeRight < left || nodeLeft >right)
		return 0;
	if (left <= nodeLeft && nodeRight <= right)
		return ans[node];
	int mid = (nodeLeft + nodeRight) / 2;
	return query(left, right, node * 2, nodeLeft, mid) + query(left, right, node * 2 + 1, mid + 1, nodeRight);
}

long long update(int index, long long value, int node, int nodeLeft, int nodeRight) {
	if (index < nodeLeft || index > nodeRight)
		return ans[node];
	if (nodeLeft == nodeRight)
		return ans[node] += value;
	int mid = (nodeLeft + nodeRight) / 2;
	return ans[node] = update(index, value, node * 2, nodeLeft, mid) + update(index, value, node * 2 + 1, mid + 1, nodeRight);
}
int main() {
	freopen("input.txt", "r", stdin);

	int n, q;
	scanf("%d %d", &n, &q);

	arr.resize(n);
	ans.resize(4 * n);

	long long a, b, c;
	for (int i = 0; i < q; ++i) {
		scanf("%lld %lld %lld", &a, &b, &c);
		
		if (a == 1) {
			update(b - 1, c, 1, 0, n - 1);
		}
		else {
			printf("%lld\n", query(b - 1, c - 1, 1, 0, n - 1));
		}
	}
}