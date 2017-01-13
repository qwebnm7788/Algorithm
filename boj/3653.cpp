/*
3653 영화수집

이 문제의 핵심은 DVD를 빼서 맨 위로 올리는 행동을 어떤 방식으로 표현 하느냐 이다

arr[x] 를 x번 영화의 높이라고 해보자 이 때 이 영화를 보고 맨위로 올린다면 배열의 크기가 N이 였다면
x번 영화 위에 있던 친구들을 한칸씩 내리고 위로 올려야 하는데 이러면 O(N)이 걸리게 된다.
그러지 말고 애초에 배열을 N+M크기로 잡게되면 

어차피 주어진 쿼리의 수는 M개 이므로 높이는 최대 올라가도 N+M이 되게 된다.

따라서 i번째 쿼리를 수행하게 되면 높이가 누적되어 올라간다고 생각하면 x번 영화를 i번 쿼리에 보면
arr[x] = n+i가 된다(맨 처음 모든 영화가 순서대로 있을때는 최대 높이가 n임을 이용)


세그먼트 트리를 특정 index에 영화가 있으면 1 없으면 0 으로 설정하자 그리고 구간합을 표현하게 구현해놓자
맨 위의 루트가 [0,n+m-1]의 구간의 합을 지니게 되고
[arr[x]+1,n+m-1] 구간을 점유하는 친구를 찾게되면 x번 영화의 높이 바로위에 있는 친구~맨 꼭대기 까지의 영화의
갯수가 구해지게 되어 O(log(n+m))에 답을 구할 수 있게 된다.
*/
#include <stdio.h>
#include <vector>
#include <algorithm>
using namespace std;

vector<int> arr;		//arr[i] = i번 영화의 높이
vector<int> ans;

int update(int index, int value, int node, int nodeLeft, int nodeRight) {
	if (index < nodeLeft || index > nodeRight)
		return ans[node];
	if (nodeLeft == nodeRight)
		return ans[node] += value;
	int mid = (nodeLeft + nodeRight) / 2;
	return ans[node] = update(index, value, node * 2, nodeLeft, mid) + update(index, value, node * 2 + 1, mid + 1, nodeRight);
}

int query(int left, int right, int node, int nodeLeft, int nodeRight) {
	if (nodeRight < left || nodeLeft > right)
		return 0;
	if (left <= nodeLeft && nodeRight <= right)
		return ans[node];
	int mid = (nodeLeft + nodeRight) / 2;
	return query(left, right, node * 2, nodeLeft, mid) + query(left, right, node * 2 + 1, mid + 1, nodeRight);
}

int main() {
	freopen("input.txt", "r", stdin);
	int test;
	scanf("%d", &test);
	for (int z = 0; z < test; ++z) {
		int n, m;
		scanf("%d %d", &n, &m);

		arr = vector<int>(n);
		ans = vector<int>(4 * (n + m));

		for (int i = 0; i < n; ++i) {
			arr[i] = n - 1 - i;
			update(arr[i], 1, 1, 0, n+m-1);
		}

		int x;
		for (int i = 0; i < m; ++i) {
			scanf("%d", &x);
			printf("%d ", query(arr[x - 1] + 1, n + m - 1, 1, 0, n + m - 1));
			update(arr[x - 1], -1, 1, 0, n + m - 1);
			arr[x - 1] = n + i;
			update(arr[x - 1], 1, 1, 0, n + m - 1);
		}
		printf("\n");
	}
}
