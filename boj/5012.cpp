/*
5012 불만정렬

ai < aj < ak 와 i < j < k 를 동시에 만족하는 튜플(순서중요)의 수를 찾으면 된다.

우선 가장 간단하게 생각해보면 i = 0~n-1까지 j = i+1 ~ n-1 까지 k= j+1 ~n-1까지를 훑어보면서 원하는 조건을 만족하는 친구의 개수를 세주면 된다.
이때의 시간복잡도는 O(N^3)이 되고 N은 최대 10^5이므로 O(10^15)이 되어 제한시간 1초에 들어올 수 없다.

으아.
이거 i번 친구를 확인할때 i번 왼쪽에서 i번보다 큰 친구의 수를 구하고 오른쪽에서 i번보다 작은 친구의 수를 구해주면 이제 그 친구들의 조합만 골라주면 된다. (즉 두 수의 곱과 같다.)
중복된 수는 의미없을 줄 알았는데 문제에서 요구하는 것은 그냥 튜플의 수이니깐 숫자의조합이 아니라 몇개인지로 value를 플러스 해주면서 저장해주어야 했다. ㅜㅜ 나도 잘하고싶당.
*/

#include <stdio.h>
#include <vector>
#include <algorithm>
using namespace std;

vector<int> arr;
vector<long long> ans;
vector<long long> left;
vector<long long> right;

//각 노드는 index를 높이라고 보면 (높이는 <= n이고 n은 10^5까지라서 충분하다)
//높이가 number인 친구의 수를 추가한다.
long long update(int number, int value, int node, int nodeLeft, int nodeRight) {
	if (number < nodeLeft || number > nodeRight)
		return ans[node];
	if (nodeLeft == nodeRight)
		return ans[node] += value;
	int mid = (nodeLeft + nodeRight) / 2;
	return ans[node] = update(number, value, node * 2, nodeLeft, mid) + update(number, value, node * 2 + 1, mid + 1, nodeRight);
}

//높이가 [left,right]인 친구가 몇명인지를 세준다.
long long query(int left, int right, int node, int nodeLeft, int nodeRight) {
	if (right < nodeLeft || left > nodeRight)
		return 0;
	if (left <= nodeLeft && nodeRight <= right)
		return ans[node];
	int mid = (nodeLeft + nodeRight) / 2;
	return query(left, right, node * 2, nodeLeft, mid) + query(left, right, node * 2 + 1, mid + 1, nodeRight);
}

int main() {
	freopen("input.txt", "r", stdin);
	int n;
	scanf("%d", &n);

	if (n <= 2) {
		printf("0");
		return 0;
	}

	arr.resize(n);
	ans.resize(4 * n);
	left.resize(n);
	right.resize(n);

	for (int i = 0; i < n; ++i)
		scanf("%d", &arr[i]);

	//나보다 큰 친구들의 수를 세어준다. left[i]는 i번 친구보다 왼쪽에 있으면서 큰 친구의 수
	//i=0~n-1순서로 업데이트를 해주므로 왼쪽에 있는 것을 셀 수 있다.
	for (int i = 0; i < n; ++i) {
		left[i] = query(arr[i] + 1, n, 1, 0, n);
		update(arr[i], 1, 1, 0, n);
	}

	//요기서 노드의 값을 초기화 해서 처음부터 순서만 바꾸어 업데이트 해준다.
	ans.clear();
	ans.resize(4 * n);

	//나보다 오른쪽에 있으면서 작은친구를 세어주어야 하는데 이때는 update를 오른쪽 친구부터 살펴줌으로써
	//"오른쪽에 있는 것"중에 작은것의 수를 체크해줄수 있다.
	for (int i = n - 1; i >= 0; --i) {
		right[i] = query(0, arr[i] - 1, 1, 0, n);
		update(arr[i], 1, 1, 0, n);
	}

	//그렇다면 정답은 i번 친구의 왼쪽에서 큰것의 수 X 오른쪽에서 작은것의 수 가 된다.
	long long ret = 0;
	for (int i = 0; i < n; ++i) {
		ret += left[i] * right[i];
	}
	printf("%lld", ret);
}
