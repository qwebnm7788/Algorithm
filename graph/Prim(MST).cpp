/*
Prim's algorithm

크루스칼과 다른점은 프림 알고리즘에서는 하나의 시작점으로 구성된 트리에서 시작해서
인접한 간선을 트리에 하나씩 추가해 가면서 스패닝 트리가 될때까지 키워나간다. 그러므로 중간과정에서 형성되는
트리또한 항상 연결된 트리를 이루고 있어 (크루스칼은 서로 연결되지 않은 트리를 이어나가는 것 (트리자체가 여러개 존재하고 있다))

*/


/*
우선 가장 간단한 방법은 각 정점이 트리에 포함되었는지 여부를 저장하는 bool값의 배열 added[]를 이용하는 것이다.
매번 간선을 순회하면서 다음에 추가할 간선을 찾아내 주면되는데 이 간선을 추가할때마다 added 배열을 순회하여
그 여부를 검사해야 하니깐 시간복잡도가 O(|V||E|)가 된다 (|V|모든 정점에 대해 O(|E|)만큼의 검사)

*/

/*
위의 알고리즘의 최적화 방법은 한 정점과 연결된 간선이 여러개 일때 모든 간선을 검사하는 것은 의미없다는 점을 이용하면 된다.
만약에 트리에 있는 a라는 정점에서 연결된 모든 간선을 확인할때 (a,b)간선은 가중치가 1이고 (a,c)간선은 가중치가 3이라면
(a,c)간선은 의미가 없는 친구가된다. 즉 연결된 간선들 중에 가장 작은 가중치를 갖는 친구만이 필요하다.
그렇게 되면 O(|E|)만큼의 검사는 필요없어지고 인접 정점만을 체크하면 되니깐 각 정점에서 간선을 추가할때마다 O(|V|)가 된다.

트리와 한 정점을 연결하는 간선의 최소 가중치를 minWeight[]에 유지하고 있는다.
그러면 이 배열은 트리에 정점을 추가할때마다 그 정점에 인접한 간선을 순회하면서 갱신하게 된다. (새로운 가능한 간선들이 더 작은 가중치를 가질수 있으니깐)
추가할 새 정점을 찾는것은 O(|V|)이고 (아직 트리에 추가안된지의 여부), 모든 간선은 (u,v)때 한번 , (v,u)때 한번 처럼 두번씩 검사되므로

전체 시간복잡도는 O(|V|^2 + |E|)가 된다. 만약에 그래프가 모든 정점들 사이에 간선이 존재하는 밀집 그래프라면 O(|E|) ~~ O(|V|^2)이 되므로
전체 시간복잡도가 O(|V|^2)이 되어서 크루스칼 알고리즘보다 빠르게 동작한다.
*/

#include <vector>
#include <algorithm>
using namespace std;

const int MAX_V = 100;
const int INF = 9876543321;

int V;

vector<pair<int, int>> adj[MAX_V];

int prim(vector<pair<int, int>>& selected) {
	int ret = 0;		//가중치의 합 저장
	selected.clear();

	//정점이 트리에 포함되었는지의 여부
	vector<bool> added(V, false);
	//트리에 인접한 간선들 중에 해당 정점에 연결되는 가중치가 가장 작은 간선의 정보를 저장
	vector<int> minWeight(V, INF);		//즉 minWeight[i]는 i번 정점과 트리를 잇는 간선들 중에 가중치가 최소인 간선의 가중치
	vector<int> parent(V, -1);

	//프림 알고리즘은 시작점이 있는데 우선은 0번정점을 무조건 시작정점으로 한다. -> 즉 트리에 가장먼저 추가된다.
	minWeight[0] = parent[0] = 0;

	for (int iter = 0; iter < V; ++iter) {
		//다음번에 트리에 추가할 정점 u를 찾는다.
		int u = -1;
		//모든 정점을 찾아보는데
		for (int v = 0; v < V; ++v) {
			if (!added[v] && (u == -1 || minWeight[u] > minWeight[v])) {
				//아직 트리에 추가되지 않았고, 검사하지 않은 친구거나 트리와 그 친구와 연결된 최소 가중치가 가장 작은 친구를 찾는다.
				u = v;
			}
		}

		//(parent[u], u)를 트리에 추가한다. -> ..?
		if (parent[u] != u)
			selected.push_back(make_pair(parent[u], u));

		ret += minWeight[u];
		added[u] = true;

		//u에 인접한 간선(u,v)를 검사해서 minWeight를 갱신해준다.
		for (int i = 0; i < adj[u].size(); ++i) {
			int v = adj[u][i].first;
			int weight = adj[u][i].second;
			if (!added[v] && minWeight[v] > weight) {
				//아직 추가되지 않은 정점과 연결된 간선 들 중에
				//minWeight보다 더 적은 가중치로 연결될 수 있다면 갱신한다.
				parent[v] = u;		//그때는 v는 나랑 연결된 간선을 이용하고
				minWeight[v] = weight;		//minWeight도 갱신된다.
			}
		}
	}
	return ret;
}



/*
어떤 경로에서 모든 간선의 가중치가 어떤 값 U이거나 그보다 작을때 U값을 이 경로의 "상한" 이라고 하고
반대로 모든 간선의 가중치가 어떤 값 L이거나 그보다는 클때 L값을 이 경로의 "하한"이라고 하자.
그리고 이때 최대 하한값과 최소 상한값의 차이를 경로의 너비라고 정의하고

이때 두 정점을 잇는 최소 너비경로를 찾는 방법을 알아보자.
*/

/*
이런 문제를 풀때 동시에 상한과 하한을 찾아내지 말고 하나가 주어졌을때 다른 하나를 찾아내는 방식으로 접근하는것이 좋다.

예를 들면 minUpperBound(low) 를 하한이 low일때 시작~도착점을 연결하는 경로의 최소 상한을 반환하는 함수로 정의하는 것

위의 함수를 정의하게 된다면 최소 너비경로를 찾는 문제를 푸는 방법은
가능한 모든 하한값 (그래프 간선을 하나하나씩 설정해가면서)에 대해서 모든 최소상한값을 얻어서 이때의 최소상한-최대하한값을
구해서 이를 최소화 시키는 경로를 찾는 방법으로 할 수 있다.
*/

const int INF = 987654321;
int V, E;

vector<pair<int, int>> adj[MAX_V];

//모든 간선의 가중치 목록 (정렬된 상태로 둔다.)
vector<int> weights;

//가중치가 weights[low]이상인 간선으로 시작점과 도착점을 연결하는
//경로를 만드는데 필요한 경로의 최소 상한을 계산한다., 두정점이 연결될 수 없다면 큰 값을 반환

int minUpperBound(int low);

//0과 V-1을 연결하는 경로중에 가중치의 상한-하한의 차이의 최소값을 반환한다.
int minWeightDifference() {
	int ret = INF;
	for (int i = 0; i < weights.size(); ++i) {
		ret = min(ret, minUpperBound(i) - weights[i]);		//i번 간선을 하한값으로 두고 너비를 계산한다. (너비의 최소값을 찾는다.)
	}
	return ret;
}


/*
위의 minUpperBound를 구현하기 위해서 알아야 할 점은
주어진 하한 값보다 작은 가중치를 갖는 간선들은 그래프에서 아예 지워버려도 된다는 점이야 
그러한 그래프를 만들어 내면 이제 두 정점을 잇는 간선들 중에 가중치의 최대값을 가진 간선의 가중치를 최소화하는 문제가 된다.
*/

//0과 V-1을 잇는 경로중에 사용하는 가중치의 범위가 [lo,hi]안에 있는 경로가 존재하는가?
//이 함수는 DFS나 BFS를 이용해서 lo, hi안에 들어가는 간선만 연결되었다고 가정해서 (조건으로 제껴가면서) 탐색을 해서
//시작점과 끝점이 서로 연결되어 있는지를 보면 된다. (0번에서 시작해서 한번 한다음에 V번이 visited되었는지 보면 될 꺼같다.)
bool hasPath(int lo, int hi);

//이분 탐색을 이용한 구현
//low가 하한일때 최소상한값을 반환
int binarySearchMinUpperBound(int low) {
	//[weights[low],weights[lo]] 범위의 간선을 사용하면 두 정점을 연결할 수 없다.
	//[weights[low], weights[hi]] 범위의 간선을 사용하면 두 정점을 연결할 수 있다.

	int lo = low - 1;
	int hi = weights.size();
	//lo는 안되는 최대값, hi는 되는 최소값
	while (lo + 1 < hi) {
		int mid = (lo + hi) / 2;

		if (hasPath(weights[low], weights[mid]))
			hi = mid;
		else
			lo = mid;
	}
	if (hi == weights.size())
		return INF;		//만약에 hi가 (즉 최소상한값이) 한번도 갱신되지 못한다면 시작점 - 도착점 사이에 가능한 경로가 없으므로 INF를 리턴
	return weights[hi];		//가능한 최소 상한값.
}


/*
minUpperBound(int low)를 다른 방법으로 생각해보면
크루스칼이나 프림알고리즘은 간선을 정렬한다음에 가중치가 작은 친구부터 연결하니깐
시작점과 도착점이 연결되는 순간에 추가된 간선이 스패닝 트리에서 가장 큰 가중치를 갖는 간선이 되기 때문에 이 값이 최소상한 값이 된다. (가장 작은 최대값 -> 왜냐면 MST는 최소한의 비용으로 전부 연결하고 싶어서 그래)

이때는 시간복잡도가 크루스칼에 지배되어서 O(ElogE)인데 우리는 minweightDifference에서 보았듯이 모든 간선에 대해서 반복하고
크루스칼에서 사용되는 정렬된 값은 계속해서 고정되기 떄문에 정렬을 한번만 시행하면 되니깐 나머지에서는 조금더 빠르게 O(E)에 해결할 수 있어서 좀더 빨라진다.
*/

struct DisjointSet {
	vector<int> parent;
	vector<int> rank;
	DisjointSet(int n)
		:parent(n), rank(n, 1) {
		for (int i = 0; i < n; ++i)
			parent[i] = i;
	}

	int find(int u) {
		if (u == parent[u])
			return u;
		return parent[u] = find(parent[u]);
	}

	void merge(int u, int v) {
		u = find(u);
		v = find(v);

		if (u == v)
			return;

		if (rank[u] > rank[v])
			swap(u, v);
		
		parent[u] = v;
		if (rank[u] == rank[v])
			++rank[v];
		parent[u] = v;
	}
};

//(가중치,(정점1,정점2))로 우선 한번만 정렬해놓는다.
vector<pair<int, pair<int, int>>> edges;

int kruskalMinUpperBound(int low) {
	DisjointSet sets(V);
	for (int i = 0; i < edges.size(); ++i) {
		if (edges[i].first < weights[low])
			continue;	//하한보다 작은 간선은 필요없엉
		//edges[i]는 이제 추가되는 친구니깐 그래프에 넣는다.
		sets.merge(edges[i].second.first, edges[i].second.second);

		//만약에 0(시작점)과 V-1(도착점)이 연결되었으면 마지막에 추가한 가중치를 반환한다.
		if (sets.find(0) == sets.find(V - 1))
			return edges[i].first;
	}
	return INF;
}



/*
brute한 방법으로 푼다면
모든 가능한 하한, 상한의 쌍을 다 테스트 해봐서 시작점 - 도착점으로 가는경로가 있는지의 여부를 체크해주면 된다.
이렇게 되면 hasPath에서 BFS를 O(|E|^2)번 수행하므로써 전체 시간복잡도가 O(|E|^3)에 수렴하게 된다.
*/


int brute() {
	int ret = INF;
	for (int lo = 0; lo < weights.size(); ++lo) {
		for (int hi = lo; hi < weights.size(); ++hi) {
			if (hasPath(weights[lo], weights[hi])) {
				ret = min(ret, weights[hi] - weights[lo]);
				break;		//이것보다 더 돌면 어차피 더 큰 상한값을 대입하니깐 돌 필요가 없다. (어차피 갱신안되요)
			}
		}
	}
	return ret;
}


/*
위의 알고리즘을 개선하는 방법은
우선 간선의 가중치가 10,20,30,40,50 이었다고 할때 하한을 10으로 했을때 경로가 존재하는 최소상한이 40이라고 하면
위의 코드는 하한을 20으로 넘어가서 다시 또 검사하게 되는데 이때 앞에서 구한 최소상한 40보다 작은 30이 최소상한이 될 수 있을까?
하한이 10일때 최소상한이 40이라는 말은 하한 10 상한 30인 경로는 존재하지 않는다는 것이야
그런데 하한이 20으로 올라가고 (그러면 간선이 줄면 줄었지 늘진 않아) 상한이 30인 경로는 존재할 수가 없어
그래서 이때 앞에서 구한 최소상한값을 쭉 끌고 간다면 불필요한 검사를 줄일 수 있어.
*/

int optimized() {
	//foundPathUsing = 경로를 찾을때 마지막으로 사용했던 최소상한의 위치를 저장
	int ret = INF;
	int foundPathUsing = 0;
	for (int lo = 0; lo < weights.size(); ++lo) {
		//이 lo 하한에 대해서 경로를 발견했는지의 여부 저장
		bool foundPath = false;
		for (int hi = lo; hi < weights.size(); ++hi) {
			if (hasPath(weights[lo], weights[hi])) {
				ret = min(ret, weights[hi] - weights[lo]);
				foundPath = true;
				foundPathUsing = hi;		//위치로 기록 (index로)
				break;
			}
		}
		//이 하한값에서 경로를 찾지 못하면 종료한다. (여기서도 못찾았는데 하한을 높이면 더 못찾겠지용)
		if (!foundPath)
			break;
	}
	return ret;
}

//위의 알고리즘을 좀더 깔끔하게 다듬으면 다음과 같다. 그냥 훑고 지나가는 방법
int scanning() {
	int lo = 0, hi = 0, ret = INF;
	while (lo < weights.size() && hi < weights.size()) {
		if (hasPath(weights[lo], weights[hi])) {
			ret = min(ret, weights[hi] - weights[lo]);
			lo++;
		}
		else {
			hi++;
		}
	}
}

