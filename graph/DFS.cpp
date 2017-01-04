#include <iostream>
#include <vector>
using namespace std;

//그래프의 인접리스트 표현
vector<vector<int> > adj;

//방문 여부 표현
vector<bool> visited;

void dfs(int here) {
	cout << "DFS visits " << here << endl;
	visited[here] = true;

	//모든 인접 정점을 순회한다.
	for (int i = 0; i < adj[here].size(); ++i) {
		int there = adj[here][i];

		//아직 방문하지않은 인접정점이 있다면 방문한다.
		if (!visited[there])
			dfs(there);
	}
	
	//더 이상 방문할 정점이 없으므로 재귀호출이 종료되면서 이전 방문 정점으로 돌아간다.
}

//모든 정점을 방문한다.
void dfsAll() {
	//visited를 모두 false로 초기화
	visited = vector<bool>(adj.size(), false);
	
	//모든 정점을 순회하면서, 아직 방문한 적이 없다면 깊이우선탐색을 실시한다.
	//여기서 모든 정점은 0~size-1로 묘사되었다고 가정한다.
	for (int i = 0; i < adj.size(); ++i) {
		if (!visited[i])
			dfs(i);
	}
}



/////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////

#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

class Graph {
public:
	int N;		//정점의 개수
	vector<vector<int>> adj;		//인접리스트
	vector<bool> visited;		//방문여부

	//생성자.
	Graph()
		:N(0) {}
	Graph(int n)
		:N(n) {
		adj.resize(N);
		visited.resize(N);
	}

	//간선 추가 함수 (무방향 그래프)
	void addEdge(int u, int v) {
		adj[u].push_back(v);
		adj[v].push_back(u);
	}

	//모든 정점에서 각 정점의 인접리스트를 번호순으로 정렬
	void sortList() {
		for (int i = 0; i < N; ++i) {
			sort(adj[i].begin(), adj[i].end());
		}
	}

	//깊이 우선 탐색
	void dfs() {
		fill(visited.begin(), visited.end(), false);
		dfs(0);
	}
private:
	void dfs(int curr) {
		visited[curr] = true;
		cout << "node " << curr << " visited" << endl;
		for (int next : adj[curr]) {
			if (!visited[next])
				dfs(next);
		}
	}

	//dfsAll을 정의하여 컴포넌트의 수를 반환
	int dfsAll() {
		int components = 0;
		fill(visited.begin(), visited.end(), false);
		for (int i = 0; i < N; ++i) {
			if (!visited[i]) {
				cout << "-- new DFS begins --" << endl;
				dfs(i);
				components++;
			}
		}
		return components;
	}

	//각 컴포넌트의 갯수를 구하기 위해서 dfs 함수를 수정해보면
	int dfs2(int curr) {
		//이제 dfs2는 curr에서 dfs를 통해서 방문한 정점의 수를 반환한다.
		int nodes = 1;		//자기 자신부터 세므로 1
		visited[curr] = true;
		cout << "node " << curr << " visited" << endl;
		for (int next : adj[curr]) {
			if (!visited[next])
				nodes += dfs2(next);
		}
		return nodes;
	}
};


//dfs를 이용하여 싸이클 정점을 찾아내는 방법
/*
방법은 한 정점의 방문이 시작되었는지를 체크하는 배열과 (visited)
그 정점의 방문이 완전히 끝났는지를 체크하는 배열을 (finished) 이용한다.

1. visited[next] = false, finished[next] = false
--> 아직 방문하지 않은 정점
2. visited[next] = true, finished[next] = false
--> here 정점과 next정점이 하나의 싸이클에 속함을 알 수 있다.
--> 왜냐면 next는 방문되었는데 아직 끝나지 않은 상태에서 here에 도착해있으므로 next에서 DFS로 들어오니 here이 있던거고
--> here에서 다시 인접정점을 살펴보았는데 next가 다시 있으니깐 이 친구들은 한번의 dfs로 reachable 한 친구들이에요 그러므로 이 친구들은 한 싸이클에 있다.!
3. visited[next] = false, finished[next] =true
--> 이런 경우는 없어 왜냐면 시작을 안했는데 끝이 났다는 거니깐
4. visited[next] = true, finished[next] = true
--> next는 이미 모든 탐색이 끝난것이므로 (DFS로 다 뒤진거) here이랑 next는 같은 싸이클에 있을 수 없다.
*/

#include <cstdio>
#include <vector>
#include <algorithm>
using namespace std;

//S[i] 는 i정점이 가리키는 친구 (여기서는 한 정점이 최대 한개의 정점과 연결되었다고 본다.)
int N, S[100000], cnt;		//cnt를 싸이클에 속하는 정점의 수라고 하자.
bool visited[100000], finished[100000];

void dfs(int curr) {
	visited[curr] = true;		//방문 시작 표시
	int next = S[curr];
	if (visited[next]) {
		if (!finished[next]) {
			//visited[next] =true, finished[next] =false인 경우 !
			//curr ~ next까지의 모든 친구들이 한 싸이클을 이룬다. 
			//즉 한 정점에서 시작해서 curr까지 왔는데 이게 이미 시작을 했고 끝이 안난 (즉 이번 dfs싸이클에 속한 친구)친구를 만난다면
			//이제 계속 삥글삥글 돌꺼야 그래서 커팅해주고 끝내면 되용~
			for (int temp = next; temp != curr; temp = S[temp])
				cnt++;
		}
	}
	else {
		dfs(next);
	}
	finished[curr] = true;
}

int main() {
	int T;
	scanf("%d", &T);
	for (int t = 0; t < T; ++t) {
		scanf("%d", &N);
		for (int i = 0; i < N; ++i) {
			scanf("%d", S + i);
			S[i]--;
		}

		fill(visited, visited + N, false);
		fill(finished, finished + N, false);
		cnt = 0;
		for (int i = 0; i < N; ++i) {
			if (!visited[i])
				dfs(i);
		}
		printf("%d\n", N - cnt);

	}


}


//////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////


//DFS spanning tree의 간선을 이용하여 만드는 싸이클의 여부를 저장하는 방법


#include <iostream>
#include <vector>
using namespace std;

//인접리스트 표현
vector<vector<int> > adj;

//discovered[i] = i번 정점의 방문 순서 -> -1로 초기화
//finished[i] = dfs(i)가 종료되었으면 1 아니면 0 -> 0으로 초기화
vector<int> discovered, finished;

//지금까지 방문한 정점의 수
int counter;

void dfs2(int here) {
	discovered[here] = counter++;

	//모든 인접정점을 순회
	for (int i = 0; i < adj[here].size(); ++i) {
		int there = adj[here][i];
		cout << "(" << here << ", " << there << ") is a ";
		//아직 there을 방문한 적이 없다면 방문한다.
		if (discovered[there] == -1) {
			cout << "tree edge" << endl;
			dfs2(there);
		}
		//there은 이미 방문한 정점인데 + here보다는 늦게 방문된 정점이라면 
		else if (discovered[here] < discovered[there]) {
			cout << "forward edge" << endl;
		}
		//there은 이미 방문한 정점이고 here보다 먼저 방문된 정점일때
		else if (finished[there] == 0) {
			//만약 there의 방문은 시작되었지만 끝이 나지 않았다면
			//there의 dfs순회중에 here에 도착한거니깐 there은 here의 조상이 된다.
			//즉 이 간선은 역방향간선이 된다.
			//u점에서 처음 사이클이 시작된다고 보면 u -> ... -> u가 될꺼야
			//u에서 dfs를 시작했다면 ...에 있는 친구들은 u의 dfs 중간에 방문하게 될텐데 이 친구들이 dfs를
			//재귀적으로 타게 되면 결국에는 u를 만나게 될꺼고 그때 만난 u는 맨처음 시작에서 이미 열렸으므로
			//discovered =true 이고 finished = false인 역방향 간선으로 분류가 될꺼야
			//그러니깐 이렇게 재귀적으로 돌다가 역방향 간선들은 모두 한 사이클에 들어가는 친구야
			cout << "back edge" << endl;
		}
		else {
			//there의 방문이 시작되었고 이미 끝난상태라면 (here보다 먼저 발견되었고)
			//이 간선은 교차간선이 된다. (조상도, 자손도 아닌상태가 되므로)
			cout << "cross edge" << endl;
		}
	}

	finished[here] = 1;
}

//무방향 그래프에서 사이클 찾기
//dfs에서 자신의 바로 위 부모를 제외하고 이미 방문한 정점에 도달한다면 사이클을 갖는다.

/*
dfsAll(G){
	//초기화
	for each vertex v of G{
		color[v] = "white";		//visited
		parent[v] = null;		//자신의 부모가 누구인지 저장
	}

	//아직 방문하지 못한 정점이 있다면 dfs
	//DFS함수는 사이클이 있다면 true를 리턴한다.
	for each vertex v of G{
		if( color[v] == "white")
			if(DFS(v)){
				print("Cycle detected"); exit;
			}
	}
	print("No cycle detected");
}

boolean DFS(v){
	color[v] = "Gray";		//방문했다고 표시
	//인접 정점 순회
	for( each vertex w adjacent to v){
		//방문 하지 않은 점이면 방문
		if(color[w] == 'white'){
			parent[w] = v;
			DFS(w);
		}
		else if(color[w] == "gray" and parent[w] != v){
			//이미 방문한 점이고 그 점이 나의 부모가 아니라면(부모라면 그냥 이어진 친구라고 볼수도 있으므로 사이클은 아니야)
			return true;	//참
		}
	}
	color[v] = "black";		//이미 확인한 친구라고 표시
	return false;		//사이클은 없다고 반환
}
*/

//위의 알고리즘은 방향그래프에서는 성립하지 않는데 왜냐면 바로위 부모가 아닌 이미 방문된 정점에 도달한다고 해서
//항상 사이클이라는 보장이 없기 때문이야
// (1,2), (1,3), (2,4), (3,4) 그래프에서 1번정점에서 dfs를 하면 2번, 4번을 방문하고 다시 올라와서
//3번을 타고 4번을 체크하게 되는데 4번이 이미 방문된 정점이고 3번의 바로위 부모도 아니지만 이건 사이클이 아니야
//방향성이 있기 때문이징

//또한 (1,2), (2,1) 그래프에서는 정점 2번에서 자신 바로위의 조상을 제외하고는 이미 방문한 점을 갈 수 있는게 없어서
//위의 알고리즘으로는 false를 리턴하겠지만 이건 사이클이 있는 그래프임이 명확해

//directed 그래프에서는 back edge가 있다면 사이클이 존재함이 명확해
//왜냐면 위에서 죽죽 내려오다가 아직 열려있는 dfs의 주인 정점에 도달할 수 있다는것이 back edge인데
//그렇게 되면 그걸 타고 올라가면 다시 또 내려올수 있으니깐 이건 사이클이 되는거야

/*
dfsAllVertices(G){
	color all vertices white;		//초기화
	for (each v in V){
		if(v is white){
			if(DFS(v)){
				print("Cycle detected");
			}
		}
	}
	print("No Cycle detected")
}

boolean DFS(v){
	color[v] = 'gray';
	for(each w adjacent to v){
		if(color[w] == 'gray')		//back edge
			return true;
		if(color[w] == 'white')
			DFS(w)
	}
	color[v] = black;
	return false;
}
*/