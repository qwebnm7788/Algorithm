/*
2887 행성터널

MST문제로 크루스칼 알고리즘으로 해결할 수 있는데
관건은 어떤 간선을 비교대상으로 삼느냐 이다. 모든 간선이 이어질 가능성이 있어서
정점 전부를 이어본다면 N(N-1)/2가 되어서 O(N^2) = 10^10 개의 간선을 만들어 주어야 한다.

근데 조금만 더 생각해보면 다음과 같다
문제에서 가중치를 판단할때 두 점 사이의 가중치는 min(x좌표의 차이, y좌표의 차이, z좌표의 차이) 가된다.
즉 세개중에 하나의 경우로 가중치를 가지고 가게 되는데

두점 A,B가 존재한다고 보자 만약에 A와 B가 x로 인접한 점이 아니라고 해보자(x좌표의 크기순서로 정렬했을때 한칸차이나는 친구가 아닐때)
그러면 A와 B사이에 C라는 점이 (x좌표 기준으로) 존재하게 되는데 그러면 이 (A,B)를 잇는 간선이 MST를 이룬다면 N-1개의 간선을 갖는다

간선의 가중치가 x좌표 (min에 의해서)로 선택되었다고 생각해보자.
(A,B)대신에 (A,C),(C,B)를 추가하게 되면 N개의 간선으로 된 연결그래프를 만들어 낼 수 있다.
또한 이 친구는 사이클이 될꺼야 왜냐면 MST에서는 모든 정점이 이미 연결된 상태인데 한 간선을 빼버리고 이미 연결된 정점을 이용해서
서로에게 도달하기 때문에 새로 추가한 간선 두개를 포함하는 사이클이 생겨

또한 (A,C),(C,B)의 가중치는 |Ax-Cx|와 |Cx-Bx|가 되고 기존의 가중치인 |Ax-Bx|를 대신하니깐
|Ax-Cx| + |Cx-Bx| - |Ax-Bx| = 0 이 되어버린다. 즉 새로 만들어낸 싸이클에서 아무 간선이나 지워버려도 기존의 MST의 총 가중치와 작아진다.
(왜냐면 기존의 간선 + 새로 생긴 두개의 간선인데 원래 맨 처음에는 기존의 간선 + (A,B)의 가중치로 이루어져있었는데
이제는 기존의 간선 + (A,C) + (C,B)가 되었고 이 세개의 가중치의 총합이 원래의 것과 동일하니깐 여기서 아무거나 지워도 원래의 가중치보다는 작아진다.(0이라면 같기도 하겠죵)
(MST는 이어져만 있으면 되니깐 싸이클에서 아무거나 하나 빼도 MST를 만족한다. 갯수도 N-1개가 되니깐)

이런 방식으로 y,z좌표또한 min에서 선택될 가능성이 존재하므로

x,y,z좌표로 정렬을 해본다음 서로 인접한 정점끼리만 간선을 추가해 줌으로써
O(3N)에 모든 간선을 생성해 볼 수 있고

이를 이용해서 크루스칼 알고리즘을 이용하면 MST의 총 비용을 구할 수 있다.

*/

#include <stdio.h>
#include <cmath>
#include <vector>
#include <algorithm>
using namespace std;

struct point {
	int x, y, z;
	point()
		:point(0, 0, 0) {}
	point(int a, int b, int c)
		:x(a), y(b), z(c) {}
};

vector<pair<int, pair<int, int>>> edges;
vector<pair<point, int>> arr;
vector<int> parent;

int find(int x) {
	if (parent[x] < 0)
		return x;
	return parent[x] = find(parent[x]);
}

bool merge(int a, int b) {
	a = find(a);
	b = find(b);
	if (a == b)
		return false;
	parent[b] = a;
	return true;
}




bool compX(const pair<point,int>& a, const pair<point, int>& b) {
	return a.first.x < b.first.x;
}
bool compY(const pair<point, int>& a, const pair<point, int>& b) {
	return a.first.y < b.first.y;
}
bool compZ(const pair<point, int>& a, const pair<point, int>& b) {
	return a.first.z < b.first.z;
}


int main() {
	freopen("input.txt", "r", stdin);
	int n;
	scanf("%d", &n);
	
	edges.resize(n);
	arr.resize(n);
	parent.resize(n, -1);

	int x, y, z;
	for (int i = 0; i < n; ++i) {
		scanf("%d %d %d", &x, &y, &z);
		arr[i] = make_pair(point(x, y, z), i);
	}
	
	//x,y,z에 대해서 각각 정렬해서 바로 인접한 친구들끼리만 연결해준다. (무방향 그래프라서 한쪽으로만 봐주면 된다.)
	sort(arr.begin(), arr.end(), compX);
	for (int i = 0; i < n-1; ++i)
		edges.push_back(make_pair((int)abs(arr[i].first.x - arr[i + 1].first.x), make_pair(arr[i].second, arr[i + 1].second)));

	sort(arr.begin(), arr.end(), compY);
	for (int i = 0; i < n-1; ++i)
		edges.push_back(make_pair((int)abs(arr[i].first.y - arr[i + 1].first.y), make_pair(arr[i].second, arr[i + 1].second)));

	sort(arr.begin(), arr.end(), compZ);
	for (int i = 0; i < n-1; ++i)
		edges.push_back(make_pair((int)abs(arr[i].first.z - arr[i + 1].first.z), make_pair(arr[i].second, arr[i + 1].second)));

	//kruskal

	sort(edges.begin(), edges.end());

	long long ans = 0;
	int cnt = 0;
	for (int i = 0; i < edges.size(); ++i) {
		int u = edges[i].second.first;
		int v = edges[i].second.second;
		int w = edges[i].first;

		if (merge(u, v)) {
			ans += w;
			cnt++;
			if (cnt == n - 1)
				break;
		}
	}

	printf("%lld", ans);

}