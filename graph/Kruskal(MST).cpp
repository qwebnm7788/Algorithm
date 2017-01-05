/*
Minimum Spanning Tree

무향그래프의 스패닝 트리는 원래의 그래프의 정점 전부와 간선의 부분집합으로 이루어진 부분 그래프이다.
이때 트리에 포함된 간선은 트리형태로서 모든 정점을 연결해주어야 한다. (즉 사이클이 없이 연결해야 한다.)
또한 스패닝 트리는 유일하지 않다. 그러므로 이러한 스패닝 트리중에 트리를 이루는 간선의 가중치의 합이 가장 작은 트리가
최소 스패닝 트리(Minimum Spanning Tree)가 된다.

*/

/*
1. 크루스칼 알고리즘(Kruskal algorithm)

우선 그래프의 모든 간선을 가중치의 오름차순으로 정렬하여 스패닝 트리에 하나씩 추가하는 방식을 택한다.
이때 추가하는 간선이 사이클을 만드는 경우는 제외한다.
이렇게 되면 모든 간선을 한번씩 검사하고 나면 종료된다. 

이 알고리즘의 핵심은 추가된 간선이 사이클을 이루는 지의 여부를 어떻게 확인하냐는 것이다.

첫번째로 가장 간단한 방법은 간선이 추가될때마다 스패닝 트리를 깊이 우선탐색으로 확인하여
역방향 간선이 존재하는지를 살피면 된다. 이경우에는 각 간선마다 한번씩 깊이우선탐색을 진행하게 되니깐
O(|E|*(|V|+|E|))가 된다. 약 O(|E|^2)이 됨을 알 수 있다.

두번째로 가능한 방법은 다음과 같은 사실을 이용한다.
한 간선이 추가되어서 이 둘이 사이클을 이룬다면 이 간선이 추가됨으로써 둘이 같은 컴포넌트에 속한다.

이를 위해서는 두 정점이 같은 컴포넌트에 속하는지 여부를 빠르게 확인해야 되는데 그 것은 disjoint set으로
쉽게 할 수 있다.

1. 맨 처음 간선의 양 끝정점이 속하는 컴포넌트를 확인한다.
-> 이미 같은 컴포넌트에 있다면 이 간선은 스패닝트리에 속하지 않는 간선이 된다.(트리가 아니니깐)
-> 서로 다른 컴포넌트에 있다면 이제 두 개의 트리를 하나로 합쳐주면 된다.
*/

#include <vector>
#include <algorithm>
using namespace std;

struct DisjointSet {
	vector<int> parent;
	vector<int> rank;
	DisjointSet(int n)
		:parent(n), rank(n, 1) {
		//초기화, rank는 1로 초기화
		for (int i = 0; i < n; ++i)
			parent[i] = i;
	}

	//u가 속한 트리의 루트 번호를 반환한다.
	int find(int u) {
		if (u == parent[u])
			return u;
		return parent[u] = find(parent[u]);
	}

	//u가 속한 트리와 v가 속한 트리를 하나로 합친다.
	void merge(int u, int v) {
		//각각의 루트를 찾아서
		u = find(u);
		v = find(v);

		//만약 이미 같은 트리에 속한다면 따로 안합쳐도 된다.
		if (u == v)
			return;

		//rank가 높은 쪽을 v로 잡고 진행
		if (rank[u] > rank[v])
			swap(u, v);
		
		
		//이제 rank[v] 가 항상 rank[u]보다 크게 되니깐 u를 v의 자식으로 넣는다.
		//항상 랭크가(높이가) 더 낮은 트리를 더 높은 트리 밑에 집어넣으면서 트리의 전체 높이가
		//높아지는 것을 방지한다.(랭크에 의한 최적화)
		parent[u] = v;
		if (rank[u] == rank[v])		//만약 같은 높이의 트리였다면 트리의 전체 높이가 하나 증가한다. v의 루트에 u의 루트가 달리니깐 전체의 높이는 1증가한다.
			++rank[v];
		parent[u] = v;
	}

	/*
	단순하게
	void merge(int u, int v){
		u = find(u);
		v = find(v);
		if(u==v)
			break;
		parent[u] =v;
	}
	이런식으로 작성하여도 좋다. 대신에 skew tree가 될수 있음
	*/
};

const int MAX_V = 100;

//정점의 수
int V;

//그래프의 인접리스트 (연결된 정점번호, 가중치)쌍으로 저장
vector<pair<int, int>> adj[MAX_V];

//주어진 그래프에 대해서 최소 스패닝 트리에 포함된 간선의 정보를 selected에 저장
//MST의 가중치의 합을 반환한다.
int kruskal(vector<pair<int, int>>& selected) {
	int ret = 0;		//가중치의 합
	selected.clear();
	//(가중치, (u,v)) 형태로 간선집합을 만든다.
	vector<pair<int, pair<int, int>>> edges;
	for (int u = 0; u < V; ++u) {
		for (int i = 0; i < adj[u].size(); ++i) {
			int v = adj[u][i].first;
			int cost = adj[u][i].second;
			edges.push_back(make_pair(cost, make_pair(u, v)));
		}
	}

	//가중치 순으로 정렬
	sort(edges.begin(), edges.end());

	//처음에는 각 정점 자체를 하나의 트리로 본다. (disjoint set으로 초기화)
	DisjointSet sets(V);

	//지금부터 크루스칼 알고리즘
	//간선을 정렬된 순서로 검사하면서 서로 다른 컴포넌트에 있다면 둘을 하나의 트리로 합치고
	//그 간선의 가중치를 누적한다.
	for (int i = 0; i < edges.size(); ++i) {
		//간선 (u,v)검사
		int cost = edges[i].first;
		int u = edges[i].second.first;
		int v = edges[i].second.second;

		//이미 같은 컴포넌트에 있다면 무시
		if (sets.find(u) == sets.find(v))
			continue;

		//아니라면 하나로 합치고 가중치 누적
		sets.merge(u, v);
		selected.push_back(make_pair(u, v));
		ret += cost;
	}
	return ret;
}


/*
크루스칼 알고리즘에서는 정렬한 후에 그냥 순서대로 조건만 맞으면 집어넣게 되는데 (즉 뒤에 있는 간선은 신경쓰지 않음)
이를 통해서 greedy algorithm 을 적용한 것이라고 볼 수 있다.

이의 정당성을 증명해보면
이 알고리즘을 통해 선택한 간선들 중에 실제 스패닝 트리 T에 포함되지 않는 간선이 있고 이 중 가장 첫번째 친구를 (u,v)라고 하자

T는 이 간선을 포함하지 않으므로 (u,v)는 T에 있는 다른 경로를 통해서 연결되어 있을꺼야
근데 이 다른 경로를 이루는 간선들 중에 하나는 반드시 (u,v)간선의 가중치보다는 같거나 커야 한다.

왜냐면 이 간선들이 모두 (u,v)보다 가중치가 작다면 간선이 정렬된 순서로 뽑는 크루스칼은 (u,v)보다
먼저 이 친구들을 뽑아서 연결했을 꺼고 , 이미 연결된 친구는 무시하니깐 (u,v)자체가 뽑힐 수 없었을 꺼야

그러므로 이 경로상에서 (u,v)의 가중치보다 큰 가중치를 갖는 간선을 골라서 T에서 지운 다음에 (u,v)를 추가하면
가중치가 줄거나 같으면 같았지 늘어나진 않을꺼고, 여전히 (u,v)가 하나로 묶여서 스패닝 트리를 형성하게 될꺼야

T가 최소 스패닝 트리였으니깐 이렇게 생긴 친구도 최소 스패닝 트리를 형성할 꺼야

이러한 성질이 모든 간선에 대해서 성립하므로 그리디 알고리즘으로 풀 수 있음을 알 수 있어.


크루스칼 알고리즘의 시간복잡도는 우선
disjoint set은 상수시간에 모든 연산이 가능하다고 볼 수 있으므로 실제로 스패닝 트리를 형성하는데 걸리는
시간의 대부분은 for문으로 모든 간선을 체크하는 것에 있으므로 O(|E|)라고 볼 수 있고
전체의 시간복잡도는 간선을 가중치 순으로 정렬하는 O(|E|log|E|)가 지배하게 되므로

크루스칼 알고리즘의 시간복잡도는 O(|E|log|E|)이다.
*/


//마지막에 뽑힌 간선이 MST에서 가장 큰 가중치를 갖는 간선이라는 것도 알 수 있따.


/*
조금만 더 수정을 해보면
MST도 트리이므로 간선의 수는 |V|-1개가 될꺼야 그러니깐 마지막 for문에서
뽑은 간선의 수가 |V|-1개가 되면 종료해도 된다.
*/

#include <stdio.h>

int uf[1000];

int find(int a) {
	if (uf[a] < 0)		//-1로 초기화
		return a;
	return uf[a] = find(uf[a]);
}

bool merge(int a, int b) {
	a = find(a);
	b = find(b);
	if (a == b)
		return false;
	uf[b] = a;
	return true;
}
//간선 구조체 w값을 기준으로 정렬되도록 연산자 오버로딩을 하였다.
struct Edge {
	int u, v, w;
	Edge()
		:Edge(-1, -1, 0) {}
	Edge(int u1, int v1, int w1)
		:u(u1), v(v1), w(w1) {}
	bool operator <(const Edge& O) const {
		return w < O.w;		//<연산을 w를 기준으로 하게끔 한다.
	}
};

int main() {
	int N, M;
	scanf("%d %d", &N, &M);
	Edge e[100000];
	for (int i = 0; i < M: ++i) {
		int a, b, c;
		scanf("%d %d %d", &a, &b, &c);
		e[i] = Edge(a - 1, b - 1, c);
	}

	sort(e, e + M);

	//result 가 가중치의 합, cnt 가 간선의 수
	int result = 0, cnt = 0;
	fill(uf, uf + N, -1);
	for (int i = 0; ; ++i) {
		//merge가 성공하면 true를 반환해준다.
		if (merge(e[i].u, e[i].v)) {
			result += e[i].w;
			if (++cnt == N - 1)
				break;		//N-1개를 뽑으면 끝
		}
	}
	printf("%d\n", result);
}