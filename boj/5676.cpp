//[i,j] -> i~j까지 원소의 곱이 양수 음수 0인지를 저장
//1,-1,0으로만 저장하자. 곱셈이 너무 커질수 있을듯
#include <stdio.h>
#include <vector>
#include <algorithm>
using namespace std;

vector<int> arr;
vector<int> ans;
vector<char> ret;

int init(int left, int right, int node) {
	if (left == right)
		return ans[node] = arr[left];
	int mid = (left + right) / 2;
	return ans[node] = init(left, mid, node * 2)*init(mid + 1, right, node * 2 + 1);
}

int query(int left, int right, int node, int nodeLeft, int nodeRight) {
	if (right < nodeLeft || left > nodeRight)
		return 1;
	if (left <= nodeLeft && nodeRight <= right)
		return ans[node];
	int mid = (nodeLeft + nodeRight) / 2;
	return query(left, right, node * 2, nodeLeft, mid)*query(left, right, node * 2 + 1, mid + 1, nodeRight);
}

int update(int index, int value, int node, int nodeLeft, int nodeRight) {
	if (index < nodeLeft || index > nodeRight)
		return ans[node];
	if (nodeLeft == nodeRight)
		return ans[node] = value;
	int mid = (nodeLeft + nodeRight) / 2;
	return ans[node] = update(index, value, node * 2, nodeLeft, mid) * update(index, value, node * 2 + 1, mid + 1, nodeRight);
}

int main() {
	freopen("input.txt", "r", stdin);
	int n, k;
	while (scanf("%d %d", &n, &k) > 0) {
		arr = vector<int>(n);
		ans = vector<int>(4 * n);
		ret = vector<char>();
		int x;
		for (int i = 0; i < n; ++i) {
			scanf("%d", &x);
			if (x > 0)
				arr[i] = 1;
			else if (x < 0)
				arr[i] = -1;
			else
				arr[i] = 0;
		}

		init(0, n - 1, 1);

		char a;
		int b, c, temp;
		for (int i = 0; i < k; ++i) {
			getchar();
			scanf("%c %d %d", &a, &b, &c);
			if (a == 'P') {
				temp = query(b - 1, c - 1, 1, 0, n - 1);
				if (temp > 0)
					ret.push_back('+');
				else if (temp < 0)
					ret.push_back('-');
				else
					ret.push_back('0');
			}
			else {
				if (c > 0)
					c = 1;
				else if (c < 0)
					c = -1;
				else
					c = 0;
				update(b - 1, c, 1, 0, n - 1);

			}
		}

		for (int i = 0; i < ret.size(); ++i)
			printf("%c", ret[i]);
		printf("\n");
	}
}