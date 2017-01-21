/*
2336 굉장한 학생

으.. 어려운 문제야
첫번째 시험을 순서대로 봐보면 나보다 뒤에 있는 친구들은 내가 굉장한 학생이 되는데에는 아무런 영향을 미치지 않아
왜냐면 나보다 대단한 학생이라면 첫번쨰 시험에서도 나보다 잘봤어야 되니깐
그러니깐 첫번째 친구를 순서대로 보면서 먼저 쿼리를 날리고 나를 업데이트 해준다면 첫번째 시험의 영향은 따로 고려안해주어도 된다.

이제 굉장한 학생이 되기 위한 경우를 생각해보면 첫번쨰 시험의 i등을 한 친구라고 하면 
0~i-1번째 친구들에 대해서 그 친구들이 두번째 시험에서도 나보다 못보고 세번째 시험에서도 나보다 못봐야지 나는 굉장한 학생이 된다.
여기서 0~i-1번째는 이미 업데이트를 잘 해두어서 쿼리를 이용해서 한번에 구해보자

세그먼트 트리의 i번 리프노드를 2번째 시험을 i등한 친구의 3번쨰 시험 등수라고 하자
그렇게 구성한 트리에 대해서 구간에 대한 최소값을 반환하도록 쿼리를 작성하면 된다.

첫번쨰 시험의 i등 친구의 굉장한 학생 여부를 판별하는 중이라고 생각해보면
쿼리를 0~i번친구의 2번쨰 시험 등수 -1 을 쿼리의 범위로 주면 된다.

이미 첫번쨰 시험을 잘본친구들만 업데이트가 되어있고 나보다 두번쨰 시험을 잘본 친구가 있는 지를 체크 해줌과 동시에
그 잘본 친구들의 세번째 시험결과의 최소등수를 얻어옴으로써 확인할수 있기 때문이다

만약 나보다 두번째 시험을 못봤으면 당연히 이 쿼리의 범위에서 제외되어서 쿼리는 엄청 큰값이 나온다.(INF로 초기화를 시켰다.)
만약 두번째 시험을 나보다 잘봤으면 세번째 시험을 볼 필요가 생기는건데 이것마저 나보다 잘봤으면 나는 굉장한 학생이 아니고
이것도 나보다 못봤으면 나는 굉장한 학생이 된다. 

3번째 시험의 등수의 최소를 주니깐 두번째 시험을 나보다 잘본 모든 친구에 대해(쿼리의 범위에 들어가는친구들) 세번째 시험의 최소등수보다 내가 더 작으면
모든 친구들보다 내가 세번째 시험을 잘본거니깐 나는 굉장한학생이 된다.!!

*/
#include <stdio.h>
#include <vector>
#include <algorithm>
using namespace std;

const int INF = 987654321;

vector<int> ans;

// 두번째 시험을 number 등한 친구에 값을 세번쨰 시험의 등수인 value로 업데이트 해준다.
int update(int number, int value, int node, int nodeLeft, int nodeRight) {
	if (number < nodeLeft || number > nodeRight)
		return	ans[node];
	if (nodeLeft == nodeRight)
		return ans[node] = value;
	int mid = (nodeLeft + nodeRight) / 2;
	return ans[node] = min(update(number, value, node * 2, nodeLeft, mid), update(number, value, node * 2 + 1, mid + 1, nodeRight));
}

//[left,right]범위 내의 최소값을 반환한다. (즉 두번째 시험을 [left,right]등 한 친구들 중의 세번째 시험의 최소등수를 반환한다.
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
	int n;
	scanf("%d", &n);

	ans = vector<int>(4 * n, INF);			//세그먼트트리의 초기값을 매우 큰값으로 잡아두었다.
	vector<vector<int>> arr(3);
	vector<vector<int>> index(3);			//index[i][j] => i번 시험에서 j번 친구는 몇등?

	for (int i = 0; i < 3; ++i) {
		arr[i] = vector<int>(n);
		index[i] = vector<int>(n + 1);
	}

	for (int i = 0; i < 3; ++i) {
		for (int j = 0; j < n; ++j) {
			scanf("%d", &arr[i][j]);
			index[i][arr[i][j]] = j;
		}
	}

	int ret = 0;
	for (int i = 0; i < n; ++i) {
		//세번째 시험의 최소값이 나보다 크다면 나는 굉장한 학생이야
		if (index[2][arr[0][i]] < query(0, index[1][arr[0][i]] - 1, 1, 0, n-1)) 
			ret++;
		update(index[1][arr[0][i]], index[2][arr[0][i]], 1, 0, n-1);
	}
	printf("%d", ret);
}
