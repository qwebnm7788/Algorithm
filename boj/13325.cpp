/*
13325 이진트리

기본적인 아이디어는 트리의 루트에서 모든 리프노드까지의 길이중 가장 긴 길이로 모든 거리를 통일해 주면 된다.

리프노드부터 올라오면서 양쪽에 이어진 간선을 보면서 둘의 차이를 누적해서 올라오면서 계산해준다.
또한 올라오면서 간선의 값을 최대 길이로 만들었을때의 누적합을 가지고 올라온다.

foo(x) = x를 루트로 하는 트리에서 양쪽에 달린 엣지의 가중치 차이의 누적값을 반환한다.
계산하면서 x에서 부모로 올라가는 엣지의 값을 최대값으로 가는 경로로 만들어 주기 위해
len[x] += max(len[2*x],len[2*x+1])을 해준다.

이렇게 foo(1)을 구하게 되면
dist[1] 의 값은 모든 엣지를 최대경로로 만들어줄때의 트리와 기존의 트리 사이에 생기는 간선의 가중치 차이의 총합을 가지게 된다.
따라서 구하는 값은 원래의 가중치 총합 + dist[1] 이 된다.

len 배열과 정점의 indexing이 다르기때문에 조심해서 다루어야 한다.
*/
#include <iostream>
#include <algorithm>
using namespace std;

const int MAX = (1 << 21);
int dist[MAX], len[MAX];
int k, total;

//x정점의 양쪽에 달린 엣지의 가중치 차이의 누적값을 반환한다.
int foo(int x) {
	if (x >= (1 << k))
		return dist[x] = 0;
	dist[x] += foo(2*x) + foo(2*x+1) + abs(len[2*x]-len[2*x+1]);
	len[x] += max(len[2 * x], len[2 * x + 1]);
	return dist[x];
}

int main() {
	freopen("input.txt", "r", stdin);
	ios_base::sync_with_stdio(false);

	cin >> k;
	for (int i = 2; i < (1 << (k+1)); ++i) {
		cin >> len[i];
		total += len[i];
	}
	cout << foo(1) + total;
}