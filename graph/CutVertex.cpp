/*
CutVertex

무향그래프에서 
특정 정점 u가 단절점이 되려면 u의 자손들과 u의 조상들이 서로 연결되어있어야 한다.(즉 u가 사라진다면 u의 자손과 u의 조상의 연결이 끊어져야 한다.)

이를 dfs를 이용해서 알아내기 위해서는 dfs함수가 각 정점을 루트로 하는 서브트리에서 갈 수 있는 정점의 최소 깊이 (즉 트리에서 보면 제일 높은 정점 어디까지 갈 수 있는지)를 반환하게 하면 된다.
이때 만약 u의 자손들이 전부다 (쪼개지면 안되니깐 전부다) u의 조상으로 갈 수 있다면 u는 절단점이 아닌게 된다.

u가 스패닝 트리의 루트인 경우가 있는데
대부분의 경우에서는 u가 지워지면 자손들로 다 쪼개지니깐 당연히 단절점이라고 생각할 수 있는데
자식이 하나도 없거나, 자식이 하나뿐인 경우에는 컴포넌트의 수가 1 -> 1이 되어버리니깐 이때는 단절점이 아닌경우가 된다.

즉 루트인 정점은 단절점의 여부를 자손의 수로 결정해야 한다. (최소 높이로 판단하게 되면 u가 스패닝 트리의 루트라면 아무리 높이 올라가도 u까지밖에 못온다. 그러면 위의 기준대로
하게 되면 u의 위로는 못올라가니깐 무조건 단절점이라고 생각하게 된다.)

*/

#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

//그래프의 인접리스트 포현
vector<vector<int>> adj;
//정점의 발견순서 -1로 초기화
vector<int> discovered;
//각 정점의 절단점 여부 저장, false로 초기화
vector<bool> isCutVertex;
int counter = 0;

//here를 루트로 하는 서브트리에 있는 절단점 찾기
//반환값은 해당 서브트리에서 갈수있는 정점 중 가장 먼저 발견된 정점의 발견시점(즉 트리에서 가장 높은 곳에 있는 친구)
//맨 처음 호출 할때는 isRoot = true로 한다. 트리의 루트를 준다.
int findCutVertex(int here, bool isRoot) {
	//발견 순서 기록
	discovered[here] = counter++;
	//우선은 자기자신이 아직까지는 갈 수있는 가장빠른 발견순서이다.
	int ret = discovered[here];

	//루트일때는 자손 서브트리의 수로 판단해야 하므로
	int children = 0;
	//자손서브트리를 모두 순회해보는데
	for (int i = 0; i < adj[here].size(); ++i) {
		int there = adj[here][i];
		//아직 방문 안했으면
		if (discovered[there] == -1) {
			//서브트리의 수를 하나 올리고
			++children;
			//이 서브트리에서 갈 수 있는 가장 높은 정점의 번호를 준다.
			int subtree = findCutVertex(there, false);

			//만약 위에서 얻은 번호가 here보다 더 낮은(같거나) 높이에 있는 친구라면  here은 절단점이야 (루트가 아니고)
			if (!isRoot && subtree >= discovered[here])
				isCutVertex[here] = true;

			ret = min(ret, subtree);		//여기 친구도 반환값을 찾는 중이야 (here를 루트로 한 서브트리에서 올라갈 수 있는 제일 높은 친구를 찾는다., 맨처음에 here의 번호가 제일 높다고 가정하고 그 밑에를 돌아다니면서 더 높이 갈 수 있는지를 본다.)
		}
		else {
			ret = min(ret, discovered[there]);		//이미 방문한 친구라면 그 친구의 방문순서도 한번 체크해 봐 나보다 높은 곳이었는지..? -> 즉 내 위로 가는 친구와 연결된 곳인지??
		}
	}

	//루트면 자식서브트리의 수로 결정
	if (isRoot) {
		isCutVertex[here] = (children >= 2);
	}

	return ret;
}


//단절선을 찾는 알고리즘은 bridge finding 이라고도 하는데

//한 (u,v) 간선을 지울때 컴포넌트가 찢어지는 곳을 말해 이 간선을 bridge라고도 해
/*
우선 가장 중요한 점은 이 간선은 tree edge일 수 밖에 없다는 점이야
만약에 forward이거나(discovered[here] < discovered[there]) back edge라면(discovered[there]<discovered[here] && finished[there] == false) u와 v를 잇는 또다른 경로가 존재한다는 의미가 되는데 그렇게 되면 이 간선은 절대로 bridge가 될 수 없지
((u,v)가 forward edge라면 u가 v의 조상이고 이미 다른 경로를 통해서 v에 한번 도달했었다는 말이되므로 다른 경로가 존재한다는 것! -> 이 간선은 bridge가 아님)
((u,v)가 back edge라면 u가 v의 자손이라는 의미이다. 즉 v의 dfs가 열린 상태로 지금 u에 도달한 것이고 그 경로를 통해서 u와 v는 연결될 수 있으므로 이 간선은 bridge가 아니다.)

따라서 tree edge만을 골라주면 된다. (무방향 그래프일때는 cross edge는 무시하면 되니깐 (내 쪽에서 그쪽을 바라볼수 있다면 무방향에서는 서로 연결이 되버려서 서로 도달이 가능해진다.)

dfs spanning tree에서 u가 v의 부모일때 tree edge(u,v)가 bridge가 되기 위해서는 v를 루트로 하는 서브트리와 이 외의 정점들을 잇는
유일한 간선이 (u,v)여야 한다. 따라서 (u,v)를 제외한 역방향 간선으로 u보다 높은 정점에 도달하지 못한다면 이 간선이 bridge라고 판단해줄수있다.

즉 역방향 간선중에 자신의 부모로 가는 간선을 무시하게 한 다음에 v와 그 자손들에게서 역방향 간선으로 갈 수 있는 제일 높은 정점이 u보다 밑이라면
(u,v)는 bridge라고 생각해줄 수 있다. (무방향 그래프라서 자신의 부모로 가는 간선이 항상 존재하게 되므로 무시해주어야 한다)

이는 위의 dfs함수의 정의를 다음과 같이 변경해주면 된다.

int dfs(int A, int parent) -> A와 A의 자식노드가 A에서 parent로 가는 간선을 사용하지 않고 도달할 수 있는 가장 높은 정점의 번호를 반환한다.
*/

//예제 소스

#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

const int MAXV = 100010;

int V, E;
int counter = 0;
int discovered[MAXV];
bool isCutVertex[MAXV];

vector<vector<int>> adj;
vector<pair<int, int>> edge;

int dfs(int A, int parent) {
	//방문 순서 기록
	discovered[A] = counter++;
	int ret = discovered[A];

	//인접 정점 순회
	for (int i = 0; i < adj[A].size(); ++i) {
		int next = adj[A][i];

		//부모로 가는 정점은 제외
		if (next == parent)
			continue;

		if (!discovered[next]) {
			//방문하지 않은 정점은 그 정점을 루트로 하는 재귀함수를 호출해서
			//그 서브트리가 갈 수 있는 최대 높이를 받는다. (next -> A로 오는 간선은 제외겠지? 그러니깐 그걸 구하고서 맨 처음에 A의 방문순서도 넣었으니깐
			//만약에 이걸 다 돌았는데도 내 위로 못올라간다면 결국 ret에는 A의 방문순서만 기록되어있을 것이고
			//그것은 parent보다는 절대 높지 못하겠지

			int low = dfs(next, A);

			if (low > discovered[A]) {
				edge.push_back(make_pair(min(A, next), max(A, next)));
			}
			ret = min(ret, low);
		}
		else {
			//이미 방문한 정점이다.... ->A의 forward/back edge중에 하나겠지?(cross는 없으니깐)discovered[next] 가 더 작다면 조상이니깐 backedge이고 크다면 forward edge일 꺼야
			ret = min(ret, discovered[next]);
		}
	}

	return ret;
}

