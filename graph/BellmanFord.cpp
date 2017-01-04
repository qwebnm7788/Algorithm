/*
BellmanFord algorithm
음의 간선이 있을경우 사용 가능한 최단경로 알고리즘이다. (단일 시작점 알고리즘)
dist[i]를 시작점 ~ i정점까지의 최단경로라고 하고
upper[i]를 시작점 ~ i정점까지의 경로중 최단경로의 상한값으로 정의하자

그렇게 되면 upper[start] = 0 이라고 할 수 있고, 다른 모든 정점은 upper를 INF로 초기화 한뒤에
이 upper를 relaxation 하면서 최단경로를 찾는 과정이다.

upper가 dist의 값에 가까워 지기 위해서는 다음의 특성을 이용하는데
dist[v] <= dist[u] + w(u,v) 라는 것이다.
dist[v]가 dist[u]보다 크다면 v까지 가는 다른 경로가 있다는 것인데 그렇게 되면 u->v로 가는 간선을 이용해서
dist[v]의 값이 더 작은 경로를 얻을 수 있기 떄문에 dist[v]가 최단경로라는 가정에 모순이 생기게 된다.

이를 이용해보면
우선 upper[v] > upper[u] + w(u,v)인 상태를 보면 upper[u] >= dist[u]이기 때문에 dist[u] + w(u,v) <= upper[u] + w(u,v)임을 알 수 있어
게다가 upper[v] >= dist[v] 이고 dist[v] <= dist[u] + w(u,v) 이기 때문에 dist[v] <= upper[u] + w(u,v)이고
dist[v] <= upper[v] <=(~) upper[u] + w(u,v)가 되기 떄문에 upper[v]를 upper[u]+w(u,v)로 줄일 수 있음을 알 수 있다.

이러한 과정을 통해서 upper[v]를 줄여 나가는 과정을 relax(완화) 한다고 한다.

벨만포드 알고리즘은 이렇게 모든 간선에 대해서 완화과정을 반복적으로 시행해서 최단거리를 구해준다.

맨 처음 한번 이 과정을 반복하면 처음 알고 있는 dist의 값은 시작정점 뿐이므로 다음에 dist값을 확정지을수 있는 친구들은
시작점에 인접한 정점이다. 
예를 들어서 s(시작정점)과 a(인접정점)이라고 하면 한번 이 과정을 진행하면 모든 간선에 대해서 수행하였기 때문에
(s,a)또한 완화과정을 진행하였을 꺼야

그렇게 되면 위해서 얻은 값처럼 upper[a] <= upper[s] + w(s,a)가 항성 성립한다. 이때 upper[s] = 0이기 때문에
upper[a] <= w(s,a)가 된다. s -> a 로 가는 최단경로가 이 간선을 통한것이라면 이 간선이 s~~~a까지의 최단거리임을 알 수 있어.?

이제 다음번 과정을 시도하면 a의 인접정점까지의 dist값을 얻을 수 있다.

즉 이 과정을 x번 반복하게 되면 x개 이하의 간선을 이용하는 최단경로를 모두 찾을 수 있음을 알 수 있어
그러므로 모든 간선에 대해서 완화과정이 실패할때까지 반복한다면 모든 정점에 대해서 최단경로를 찾을 수 있어

그래프에 V개의 정점이 존재한다면 최단경로는 같은 정점을 두번이상 반복해서 지나지 않으므로 최단경로는 최대 V-1개의 간선을 지나게 되니깐
이 과정을 V-1번 반복해주면 된다.
*/


/*
음의 사이클 판정 방법
음의 사이클이 없다면 모든 정점에 대해서 V-1번의 완화과정으로 최단경로를 찾을 수 있는데
이때 한번 더 완화과정을 진행했을때 완화과정이 성공하는 친구가 있다면 그 친구는 음의 사이클에 존재하는 것이 된다.
*/


#include <vector>
using namespace std;

const int MAX_V = 1000;
const int INF = 987654321;
//정점의 수
int V;

// 인접리스트 (인접정점의 번호, 가중치)
vector<pair<int, int>> adj[MAX_V];

int parent[MAX_V];			//i번 정점의 바로 직전 들른 정점을 저장한다.

//음수 사이클이 있다면 빈 벡터 반환
vector<int> bellmanFord(int src) {
	//시작점 제외 모든 정점의 upper값을 INF로 둔다.
	vector<int> upper(V, INF);
	upper[src] = 0;
	bool updated;		//완화가 성공한적이 있는지
	//V번 반복한다.
	for (int iter = 0; iter < V; ++iter) {
		updated = false;
		//모든 간선을 순회한다.
		for (int here = 0; here < V; ++here) {
			for (int i = 0; i < adj[here].size(); ++i) {
				int there = adj[here][i].first;
				int cost = adj[here][i].second;
				//(here,there)간선을 완화시도 해본다.
				if (upper[there] > upper[here] + cost) {
					//완화가 성공
					parent[there] = here;		//이런식으로 최단 "경로"를 구해준다.
					upper[there] = upper[here] + cost;
					updated = true;
				}
			}
		}
		//만약에 V-1번 전에 모든 완화가 실패했다면 최단경로를 모두 구한것이 되니깐 그냥 종료해도 된다.
		if (!updated)
			break;
	}

	//V번째의 순회에도 updated= true이라면 음의 사이클이 있다.
	if (updated)
		upper.clear();
	return upper;
}

//시간복잡도는 바깥의 iter이 V번을 돌고 내부의 2중 for문으로 모든 간선을 검사하므로 O(E)번 수행된다.
//따라서 O(|V||E|)가 된다.


/*
벨만포드 알고리즘으로 최단거리를 다 계산했을때 start ~ i 까지의 경로가 존재하는지의 여부(reachability)를 체크할때
그냥 단순히 upper[i]가 INF인지를 검사하면 안될수도 있어
왜냐면 음의 간선이 존재한다면 s, a,b인 세개의 정점인 그래프에서 (a->b,-2), (b->a,1)인 간선만이 존재한다고 할때
간선 (a,b),(b,a)에 대해서 완화를 진행하면 upper[b] > upper[a]+w(a,b)이기 때문에 (w(a,b)가 음수라서 upper[a]=upper[b]=INF이지만 upper[a]+w(a,b)가 더 작아진다)
upper[b] = INF-2가 되고
(b,a)에 대해서 upper[a] > upper[b] + w(b,a) (upper[b] = INF-2이고 w(b,a)는 1밖에 안되서 둘이 더해서 INF보다는 작다 INF-1!!)
그래서 upper[a] = INF-1이 됨을 알 수 있어

그래서 INF인지로 체크를 하면 이 친구들이 도달 가능성이 다른값을 얻을 수 있어

따라서 upper[x] < INF-X인지로 체크를 해주어야 도달가능성을 알 수 있다 (M이 적당히 큰 값이라고 한다면)
*/