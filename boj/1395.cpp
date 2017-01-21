/*
1395 스위치

스위치가 누를때마다 반전된다는 성질을 활용하면 bool형으로 된 lazy로 처리해줄 수있다.
각 노드는 주어진 구간에서 켜져있는 스위치의 수의 갯수를 준다고 하자 (구간합 세그먼트트리)
lazy[node]=true라면 이 구간의 스위치를 반전할 예정인 것이다.
그렇게 되면 자식들을 잘 관찰해보면 되는데
자식들에게 lazy를 전파한 후에 자식들의 lazy상태를 보면 된다.
자식의 lazy값이 true라면 자식은 자신의 구간의 스위치를 전부 반전시킬 예정이므로
쿼리가 준 값인 켜져있는 스위치의 수가 아닌 그 나머지의 수가 켜질것이니깐 그 값을 활용해주면 되고
false라면 그대로 진행할것이기 때문에 그냥 그 값을 이용해주면된다.
*/

#include <cstdio>
#include <vector>
#include <algorithm>
using namespace std;

vector<int> ans;
vector<bool> lazy;

//node의 lazy를 자식에게 propagate한다.
void propagation(int nodeLeft, int nodeRight, int node) {
	if (lazy[node]) {
		if (nodeLeft != nodeRight) {
			//리프노드가아니라면 lazy를전파해준다.
			lazy[node * 2] = (lazy[node * 2] ? false : true);
			lazy[node * 2 + 1] = (lazy[node * 2 + 1] ? false : true);

			int mid = (nodeLeft + nodeRight) / 2;
			int temp = 0;
			//왼쪽 자식의 lazy가 true면 반전된 개수를 얻고 그렇지 않으면 그대로 가져온다.
			if (lazy[node * 2])
				temp += (mid - nodeLeft + 1) - ans[node * 2];
			else
				temp += ans[node * 2];

			//오른쪽도 마찬가지 !
			if (lazy[node * 2 + 1])
				temp += (nodeRight - mid) - ans[node * 2 + 1];
			else
				temp += ans[node * 2 + 1];

			ans[node] = temp;
		}
		else {
			//리프노드인데 lazy[node]가 true니깐 그냥 지금의 상태를 반전하면되용
			if (ans[node] == 1)
				ans[node] = 0;
			else
				ans[node] = 1;
		}
		lazy[node] = false;
	}
}

//[left,right]구간의 켜져있는 스위치의 개수를 반환한다.
int query(int left, int right, int node, int nodeLeft, int nodeRight) {
	//우선은 나까지는 왔으니깐 전파를 하고
	propagation(nodeLeft, nodeRight, node);
	
	if (right < nodeLeft || left > nodeRight)
		return 0;
	if (left <= nodeLeft && nodeRight <= right)
		return ans[node];
	int mid = (nodeLeft + nodeRight) / 2;
	return query(left, right, node * 2, nodeLeft, mid) + query(left, right, node * 2 + 1, mid + 1, nodeRight);
}

//[left,right]구간을 반전시킨다.
void update(int left, int right, int node, int nodeLeft, int nodeRight) {
	propagation(nodeLeft, nodeRight, node);

	if (right < nodeLeft || left > nodeRight)
		return;
	if (left <= nodeLeft && nodeRight <= right) {
		lazy[node] = !lazy[node];
		propagation(nodeLeft, nodeRight, node);
		return;
	}

	int mid = (nodeLeft + nodeRight) / 2;
	update(left, right, node * 2, nodeLeft, mid);
	update(left, right, node * 2 + 1, mid + 1, nodeRight);
	ans[node] = ans[node * 2] + ans[node * 2 + 1];
}

int main() {
	freopen("input.txt", "r", stdin);
	freopen("output.txt", "w", stdout);
	int n, m;
	scanf("%d %d", &n, &m);

	ans.resize(4 * n);
	lazy.resize(4 * n);

	int a, b, c;
	for (int i = 0; i < m; ++i) {
		scanf("%d %d %d", &a, &b, &c);
		if (a == 0)
			update(b - 1, c - 1, 1, 0, n - 1);
		else
			printf("%d\n", query(b - 1, c - 1, 1, 0, n - 1));
	}
}
