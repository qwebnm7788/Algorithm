/*
1168 조세퍼스 문제2
으아. 너무 어렵다
*/

#include <stdio.h>
#include <vector>
#include <algorithm>
using namespace std;

vector<int> ans;

//[0~n-1]번이 각각 그 번호가 위치해 있는 표시를 위해 1씩 주었다 (즉 1이 그 수가 아직 살아있음을 의미한다.)
//각 노드는 주어진 범위에 살아있는 사람이 몇명인지를 표시한다.
int init(int left, int right, int node) {
	if (left == right)
		return ans[node] = 1;
	int mid = (left + right) / 2;
	return ans[node] = init(left, mid, node * 2) + init(mid + 1, right, node * 2 + 1);
}

//number번째 사람을 죽인다.
int update(int number, int value, int node, int nodeLeft, int nodeRight) {
	if (nodeLeft == nodeRight)
		return ans[node] += value;
	int mid = (nodeLeft + nodeRight) / 2;
	if (ans[node * 2] >= number)
		return ans[node] = update(number, value, node * 2, nodeLeft, mid) + ans[node * 2 + 1];
	else
		return ans[node] = ans[node*2] + update(number - ans[node * 2], value, node * 2 + 1, mid + 1, nodeRight);
}

//query는 주어진 범위에 사람이 몇명 살아있는지를 반환하게 된다.
//이를 통해서 x번 사람을 죽인 후에 x번 사람 앞에 명이 있는지를 이용하면 다음번에 죽을 사람은
//몇번째 사람인지를 알 수 있다. 
int query(int left, int right, int node, int nodeLeft, int nodeRight) {
	if (right < nodeLeft || left > nodeRight)
		return 0;
	if (left <= nodeLeft && nodeRight <= right)
		return ans[node];
	int mid = (nodeLeft + nodeRight) / 2;
	return query(left, right, node * 2, nodeLeft, mid) + query(left, right, node * 2 + 1, mid + 1, nodeRight);
}

//number번째 사람이 누군지를 반환한다.
int indexQuery(int number, int node, int nodeLeft, int nodeRight) {
	if (nodeLeft == nodeRight)
		return nodeLeft;
	int mid = (nodeLeft + nodeRight) / 2;
	if (ans[node * 2] >= number)
		return indexQuery(number, node * 2, nodeLeft, mid);
	else
		return indexQuery(number - ans[node * 2], node * 2 + 1, mid + 1, nodeRight);
}
int main() {
	freopen("input.txt", "r", stdin);
	int n, m;
	scanf("%d %d", &n, &m);
	
	vector<int> ret;
	ans.resize(4 * n);

	init(1, n, 1);

	ret.push_back(m);
	update(m, -1, 1, 1, n);

	int current = m;
	int size = n - 1;
	for (int i = 0; i < n - 1; ++i) {
		//query(1,current,1,n)을 하면 current까지의 남은 사람의 수 즉 새로운 배열의 인덱스 값(1부터 시작이라고 하면)이 된다.(current가 죽은 후에 줄어든 배열에서의)
		//+m을 하면 그 다음번에 죽을 친구의 인덱스 값이 되는데 modular 연산이 %를 하면 0~size-1이 나온다는 것을 생각해보면
		//예를 들어 size = 4일때  query + m 이 1+3 = 4라고 해보자 우리는 남은 사람의 수 자체를 인덱스로 두었기 때문에
		//시작이 1부터야 그러니깐 query + m = 4라는 거는 0번으로 가면 안되고 4번 그 자체가 된다.
		int next = (query(1, current, 1, 1, n) + m) % size;
		if (next == 0)
			next = size;

		//next번째 사람이 누군지를 알아낸 후에 배열에 추가해준다.
		ret.push_back(indexQuery(next, 1, 1, n));
		//그리고 그 친구를 죽인다.
		update(next, -1, 1, 1, n);
			
		//current를 이동시킨 후에 전체 배열의 크기가 줄었으니 size를 감소시킨다.
		current = ret.back();
		size--;
	}

	printf("<");
	for (int i = 0; i < ret.size(); ++i) {
		if (i == ret.size() - 1)
			printf("%d>", ret[i]);
		else
			printf("%d, ", ret[i]);
	}
}