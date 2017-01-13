/*
9426 중앙값 측정

으.. 이문제는 각 노드가 자신이 표현하는 범위에 속하는 숫자의 수의 누적합을 들고 있도록 작성하면된다.
즉 범위 자체가 들어오는 온도의 값이 되는거야 그래서 맨 위의 루트는 온도를 잰 횟수 n을 기준으로 작성하는 것이 아니라
온도의 최대 범위인 x(<=65535)로 작성하면 된다.

왜 이렇게 하냐면 구하는 값은 정렬된 상태에서 (k+1)/2 번째 수인데 그냥 arr로 구하게 되면 정렬을 매번 해주어야 한다.(들어오는 수마다)
그러니깐 그냥 자신의 크기에 맞는 자리에 가져다 놓으면 그 범위안에 몇번째 수인지로 판단하고 들어가면 정렬된 순서를 뽑을 수있다.

그렇게 되면 우선 k-1개 까지는 그냥 각각의 자리에 1씩 업데이트를 시켜주고
k번 부터는 새로운 친구 업데이트 + 쿼리 + 맨 앞 친구 제거 를 반복해주면 된다.


update는 각 노드가 자신의 표현범위 숫자를 몇개나 가지고 있는지를 저장하게끔 작성해주면 되고(1,0으로 누적합을 이용)
구하는 값은 (k+1)/2번째의 수이므로 각 노드가 몇개의 숫자를 가지고 있는지 알고 있기 때문에 (k+1)/2번째 수를 찾아 내려가면 되는데
query를 우선 왼쪽 자식이 가진 수의 갯수가 (K+1)/2 보다 크거나 같다면 중앙값은 왼쪽 아래 노드가 표현하는 값의 범위에 들어가니깐 글로 내려가고
그게 아니면 오른쪽으로 내려가는데 오른쪽으로 내려가는 경우에는 이제 갯수가 0부터 시작이 아니라 왼쪽 노드의 갯수를 제외해야 하니깐 (k+1)/2-ans[node*2]상태로 내려가야한다.

이렇게 리프 노드까지 내려가면 원하는 번째의 수를 구할 수 있는데 그 수는 그냥 그 노드가 표현하는 index의 값과 같다. (그 노드가 표현하는 수 자체는 1일꺼야 (그 수가 있다는 표시)

그리고 MAX_X가 65535가 아닌 65536인데 왜냐면 내가 index에 저장할때 arr의 값-1을 하지않았기 때문이징. 최대값으로 온도를 집어넣으면
WA가 나온다. (MAX_X 를 65535로 하면 -> 내가 query의 범위를 MAX_X-1로 하기때문)
*/

#include <stdio.h>
#include <vector>
#include <algorithm>
using namespace std;

const int MAX_X = 65536;

vector<long long> arr;
vector<long long> ans;

long long update(int index, int value, int node, int nodeLeft, int nodeRight) {
	if (index < nodeLeft || index > nodeRight)
		return ans[node];
	if (nodeLeft == nodeRight)
		return ans[node] += value;
	int mid = (nodeLeft + nodeRight) / 2;
	return ans[node] = update(index, value, node * 2, nodeLeft, mid) + update(index, value, node * 2 + 1, mid + 1, nodeRight);
}

long long query(int index, int node, int nodeLeft, int nodeRight) {
	if (nodeLeft == nodeRight)
		return nodeLeft;
	int mid = (nodeLeft + nodeRight) / 2;
	if (index <= ans[node * 2])
		return query(index, node * 2, nodeLeft, mid);
	else
		return query(index - ans[node * 2], node * 2 + 1, mid + 1, nodeRight);
}

int main() {
	freopen("input.txt", "r", stdin);
	int n, k;
	scanf("%d %d", &n, &k);

	arr.resize(n);
	ans.resize(4*MAX_X);

	for (int i = 0; i < k - 1; ++i) {
		scanf("%lld", &arr[i]);
		update(arr[i], 1, 1, 0, MAX_X - 1);
	}

	long long ret = 0;
	for (int i = 0; i < n - k + 1; ++i) {
		scanf("%lld", &arr[k+i-1]);
		update(arr[k+i-1], 1, 1, 0, MAX_X - 1);
		ret += query((k + 1) / 2, 1, 0, MAX_X - 1);
		update(arr[i], -1, 1, 0, MAX_X - 1);
	}
	printf("%lld", ret);
}