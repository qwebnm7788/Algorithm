/*
1321 군인

처음에는 한 정점의 값이 왼쪽 정점의 전체 합과 오른쪽 정점의 전체합을 따로 가지고 있어서
구하려는 값이 왼쪽 정점의 값보다 작다면 왼쪽으로 가고 아니면 오른쪽으로 가는 방식으로 작성했는데

결국에는 각 정점의 값이 표현하는 구간의 전체값의 합으로 표현해준 것과 같은 효과이고
이것이 더 간단한 코드로 작성되었다.

그래도 struct를 이용해서 정점이 표현하는 정보를 표현하는 법을 사용해볼수도 있었다.
*/
#include <stdio.h>
#include <vector>
#include <algorithm>
using namespace std;

struct range {
	int leftSum;
	int rightSum;

	range(int le=0, int ri=0) {
		leftSum = le;
		rightSum = ri;
	}
};

vector<int> arr;
vector<range> ans;

range init(int left, int right, int node) {
	if (left == right) {
		ans[node].leftSum = arr[left];
		return ans[node];
	}
	int mid = (left + right) / 2;
	range temp = init(left, mid, node * 2);
	ans[node].leftSum = temp.leftSum + temp.rightSum;
	temp = init(mid + 1, right, node * 2 + 1);
	ans[node].rightSum = temp.leftSum + temp.rightSum;
	return ans[node];
}

range update(int index, int value, int node, int nodeLeft, int nodeRight) {
	if (index < nodeLeft || index > nodeRight)
		return ans[node];
	if (nodeLeft == nodeRight) {
		ans[node].leftSum += value;
		return ans[node];
	}
	int mid = (nodeLeft + nodeRight) / 2;
	range temp = update(index, value, node * 2, nodeLeft, mid);
	ans[node].leftSum = temp.leftSum + temp.rightSum;
	temp = update(index, value, node * 2 + 1, mid + 1, nodeRight);
	ans[node].rightSum = temp.leftSum + temp.rightSum;
	return ans[node];
}

int query(int number, int node, int nodeLeft, int nodeRight) {
	if (nodeLeft == nodeRight)
		return nodeLeft+1;
	int mid = (nodeLeft + nodeRight) / 2;
	if (number <= ans[node].leftSum)
		return query(number, node * 2, nodeLeft, mid);
	else
		return query(number-ans[node].leftSum, node * 2 + 1, mid + 1, nodeRight);
}

int main() {
	freopen("input.txt", "r", stdin);

	int n;
	scanf("%d", &n);

	arr.resize(n);
	ans.resize(4 * n);

	for (int i = 0; i < n; ++i)
		scanf("%d", &arr[i]);

	init(0, n - 1, 1);
	int m;
	scanf("%d", &m);

	int a, b, c;
	for (int i = 0; i < m; ++i) {
		scanf("%d", &a);
		if (a == 1) {
			scanf("%d %d", &b, &c);
			update(b-1, c, 1, 0, n - 1);
		}
		else {
			scanf("%d", &b);
			printf("%d\n", query(b, 1, 0, n - 1));
		}
	}
}


/*
#include <stdio.h>
#include <algorithm>
#include <vector>
using namespace std;

vector<long long> ans;

long long init(const vector<int>& arr, int node, int start, int end)
{
	if (start == end)
		return ans[node] = arr[start];
	int mid = (start + end) / 2;
	return ans[node] = init(arr, node * 2, start, mid) + init(arr, node * 2 + 1, mid + 1, end);
}
long long update(int index, int newval, int node, int start, int end)
{
	if (index < start || index > end)
		return ans[node];
	if (start == end)
		return ans[node] = newval;
	int mid = (start + end) / 2;
	return ans[node] = update(index, newval, node * 2, start, mid) + update(index, newval, node * 2 + 1, mid + 1, end);
}
int query(int num, int node, int start, int end)
{
	if (start == end)
		return start;
	int mid = (start + end) / 2;
	if (num <= ans[node * 2])
		return query(num, node * 2, start, mid);
	else
		return query(num - ans[node * 2], node*2+1, mid + 1, end);
}
int main()
{
	int n, m;
	scanf("%d", &n);
	vector<int> arr(n);
	for (int i = 0; i < n; i++)
		scanf("%d", &arr[i]);
	ans.resize(4 * n);
	init(arr, 1, 0, n - 1);
	scanf("%d", &m);
	long long a, b, c;
	for (int i = 0; i < m; i++)
	{
		scanf("%lld", &a);
		if (a == 1)
		{
			scanf("%lld %lld", &b, &c);
			arr[b - 1] += c;
			update(b - 1, arr[b-1], 1, 0, n - 1);
		}
		else
		{
			scanf("%lld", &b);
			printf("%d\n", query(b, 1, 0, n - 1) + 1);
		}
	}
}
*/
