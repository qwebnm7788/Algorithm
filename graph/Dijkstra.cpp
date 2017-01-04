/*
dijkstra algorithm
단일 시작점 최단경로 알고리즘

bfs를 응용하여 시작점 ~ 모든 정점까지의 최단경로를 구해준다.
*/

#include <vector>
#include <queue>
using namespace std;

//최대 정점의수
const int MAX_V = 1000;
const int INF = 987654321;
//정점의 수
int V;		
//인접리스트 (연결된 정점번호, 가중치)의 쌍으로 저장
vector<pair<int, int>> adj[MAX_V];

//src에서 시작하는 다익스트라 함수를 구현 결과를 반환(모든 정점까지의 최단경로 배열)
vector<int> dijkstra(int src) {
	vector<int> dist(V, INF);
	dist[src] = 0;		//시작 점 까지의 거리는 0 임이 자명하다
	priority_queue<pair<int, int>> pq;
	//혹은 min heap으로 만들어 주고 싶다면
	//priority_queue<pair<int,int>, vector<pair<int,int>>, greater<pair<int,int>> pq; 로 선언해야 한다.
	pq.push(make_pair(0, src));		//시작정점을 우선순위 큐에 삽입( 앞으로 방문해야할 정점 리스트에 추가)
	while (!pq.empty()) {
		//혹은
		/*
		do{
			int here = pq.top().second;
			pq.pop();
			here이 이미 방문한 정점이라면 무시한다.
		}while(!pq.empty() && visited[here])
		*/
		int cost = -pq.top().first;		//원래의 부호로 되돌려 준다.
		int here = pq.top().second;
		pq.pop();

		
		if (dist[here] < cost)		//이미 here정점에 방문한 적이 있는데 그 때 얻은 경로가 지금의 것보다 짧다면 무시해준다.
			continue;	//즉 dist[u]가 cost보다 작다는 것은 이 간선을 통해서 가는 것보다 다른경로를 이용하는것이 더 짧다는 것이므로

		//인접 정점 검사
		for (int i = 0; i < adj[here].size(); ++i) {
			int nextcost = adj[here][i].first;
			int next = adj[here][i].second;

			//next로 가는 길이보다 더 짧은 경로가 here -> next 간선으로 가능하다면 이 간선을 이용하는게
			//더 짧은 경로이므로 갱신해준다.
			if (dist[next] > cost + nextcost) {
				dist[next] = cost + nextcost;
				pq.push(make_pair(-dist[next], next));
			}
		}
	}
	return dist;
}

//시간복잡도는 O(ElogV)가 된다. 우선순위 큐에 원소 추가/삭제가 logE에 된다.(우선순위 큐의 크기가 최대 E까지 커지므로)

/*
위에서 주석으로 해놓았듯이 한번 방문한 정점에 대해서는
더이상 체크를 하지 않고 있는데
그 이유는 다익스트라에 대해서 한번 정점을 방문하게 되면 그 정점에 대한
최단경로는 구해지고 그 이후로도 변하지 않기 때문이야

dist값을 제대로 계산하지 못하는 u라는 정점이 있다고 하자(dist값이 최단경로가 아니게 되는 친구)
우선 시작정점에 대해서는 항상 정확하게 답을 구할수 있어 0이야 ! 그렇다면 u는 시작정점은 아니겠지?

그러면 다익스트라 알고리즘으로 u를 방문하게 되는 순간 그래프를 u 이전에 방문한 정점들과
아직 방문하지 못한 정점들로 나누어 보자.

dist[u]가 이때에도 최단경로를 제대로 계산하지 못한다는 의미는 아직 방문하지 않은 정점들을 통해서
u로 가는 더 짧은 경로를 만들어 낼 수 있다는 말이 된다.

그러면 그러한 더 짧은 경로에 대해서 그 경로상에서 이미 방문한 정점을 p라 하고
아직 방문하지 못한 바로 다음 정점을 q라고 하자

그러면 q까지의 최단경로는 dist[p] + (w,q)가 된다 이떄 p는 이미 방문한 상태이기 떄문에
dist[q]에는 최단거리가 들어가 있고 그에 따라서 우선순위 큐에 이미 들어있을꺼야 (왜냐면 p를 방문하는 도중에
인접한 정점을 모두 체크하고 q는 아직 가보지 못한 정점이라서 무조건 체크하면서 우선순위 큐로 들어간다.)

여기서 u가 우선순위큐에서 먼저 꺼내졌다는 얘기가 되는데(q보다) 그 말은 dist[u] <= dist[p]라는 말이 되는거야
w(p,q) = 0인경우 등호가 성립, 그렇게 된다면 p->q로 시작하는 경로가 dist[u]보다 더 짧다는 말은 모순이 된다.
아무리 모든 간선의 가중치가 0이라고 해도 최대 dist[u]와 "같다" 까지 밖에 안되기 때문이지


*/