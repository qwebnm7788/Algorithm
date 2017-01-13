/*
1849 순열
주어진 A[i]를 이용해서 어떻게 하면 원래의 순열로 복원할 수 있을지를 생각하는게 중요하다
이 때 포인트는 A[i]가 i번 수의 앞에 "작은"수가 몇개있느냐를 표현했다는 것인데
i=1일 때는 앞에 작은 수가 있을수 없기 때문에 a[1] = 5 라면 1은 6번째 수로 확정된다.
i=2일 때 앞에 작은 수는 1뿐이고 나머지는 다 2보다는 큰 수가 되어서 1을 제외한 앞에 빈자리를 a[2]개만큼 남긴 다음자리에
정착 시키면 된다.

이때 2를 집어넣을때 1을 무시하는 방법 중에 하나는
세그먼트의 노드가 표현하는 범위내의 남은 자리 수를 가지고 있게 하는것이다.
i를 작은 순서로 업데이트 할것이기 때문에 작은지 큰지는 알 필요가 없다. (2를 넣을때 1이 자리를 이미 차지해서 2가 남은 자리를 살필때는 1이 있는 자리를 제외하고
살피게 된다.)

*/

#include <stdio.h>
#include <vector>
#include <algorithm>
using namespace std;

vector<int> arr;
vector<int> ans;
vector<int> ret;

int cnt = 1;
//init으로 맨 처음에 남은 모든 자리에 대해서 1로 초기화를 시켜준다.
//즉 각 노드는 자신이 가진 구간에서 남은 자리의 수를 갖는다.
int init(int left, int right, int node) {
	if (left == right)
		return ans[node] = 1;
	int mid = (left + right) / 2;
	return ans[node] = init(left, mid, node * 2) + init(mid + 1, right, node * 2 + 1);
}

//이제 각 수를 업데이트 하는데 number를 가지고 와 그래서 왼쪽 노드를 보고 여유구간이 value보다 크거나 갖다면
//내가 있어야 할곳은 그곳이니깐 거기로 내려가 아니라면 오른쪽
//그리고서 맨 끝으로 내려가서 -1을 줌으로써 그 자리를 차지하면 된다. 이 때 그 자리의 값을 따로 저장해 주면 된다.

int update(int number, int value, int node, int nodeLeft, int nodeRight) {
	if (nodeLeft == nodeRight) {
		ret[nodeLeft] = cnt++;
		return ans[node] += value;
	}
	int mid = (nodeLeft + nodeRight) / 2;
	if (number <= ans[node * 2])
		return ans[node] = update(number, value, node * 2, nodeLeft, mid) + ans[node * 2 + 1];
	else
		return ans[node] = ans[node * 2] + update(number - ans[node * 2], value, node * 2 + 1, mid + 1, nodeRight);
}

int main() {
	freopen("input.txt", "r", stdin);
	int n;
	scanf("%d", &n);

	arr.resize(n);
	ret.resize(n);
	ans.resize(4 * n);

	init(0, n - 1, 1);

	for (int i = 0; i < n; ++i) {
		scanf("%d", &arr[i]);
		update(arr[i]+1, -1, 1, 0, n - 1);
	}

	for (int i = 0; i < n; ++i) {
		printf("%d\n", ret[i]);
	}
}