#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
using namespace std;

class Graph {
public:
	int N;		//number of nodes
	vector<vector<int>> adj;		//adjacent list

	//constructor
	Graph()
		:N(0) {}
	Graph(int n)
		:N(n) {
		adj.resize(n);
	}

	//adding (u,v) edge
	//undirected edge
	void addEdge(int u, int v) {
		adj[u].push_back(v);
		adj[v].push_back(u);
	}

	//sorting adjacent list
	void sortList() {
		for (int i = 0; i < N; ++i) {
			sort(adj[i].begin(), adj[i].end());
		}
	}


	//BFS implement
	void bfs() {
		vector<bool> visited(N, false);
		queue<int> Q;
		Q.push(0);
		visited[0] = true;
		
		while (!Q.empty()) {
			int curr = Q.front();
			Q.pop();
			cout << "node " << curr << " visited" << endl;
			for (int next : adj[curr]) {
				if (!visited[next]) {
					visited[next] = true;
					Q.push(next);
				}
			}
		}
	}
};



///////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////


//adjacent list
vector<vector<int>> adj;

//start부터 이 그래프를 bfs로 순환하고 방문순서를 리턴한다.
vector<int> bfs(int start) {
	//방문여부 초기화
	vector<int> discovered(adj.size(), false);

	//앞으로 방문해야될 정점의 리스트 저장을 위한 큐
	queue<int> q;

	//정점의 방문정보
	vector<int> order;
	discovered[start] = true;
	q.push(start);

	while (!q.empty()) {
		int here = q.front();
		q.pop();

		//here을 방문
		order.push_back(here);

		//인접정점 확인하며 큐에 리스트를 추가한다.
		for (int i = 0; i < adj[here].size(); ++i) {
			int there = adj[here][i];

			if (!discovered[there]) {
				q.push(there);
				discovered[there] = true;
			}
		}
	}

	return order;
}

//인접 리스트로 구현시 모든 정점/간선을 체크하므로 O(|V|+|E|), 인접 행렬로 구현시 O(|V|^2)

//최단경로를 계산해내는 bfs
//start를 시작으로 bfs를 진행해서 start ~ 각정점까지의 최단거리와
//너비우선탐색 스패닝 트리를 계산한다.
//distance[i] 는 start~i까지의 최단경로
//parent[i] 는 너비우선탐색 스패닝 트리에서 i번 정점의 부모의 번호, 루트일때는 자기자신의 번호로 한다.

void bfs2(int start, vector<int>& distance, vector<int>& parent) {
	distance = vector<int>(adj.size(), -1);
	parent = vector<int>(adj.size(), -1);

	//방문예정 리스트
	queue<int> q;
	distance[start] = 0;		//시작정점까지의 거리는 0 이겠죵
	parent[start] = start;			//시작점을 루트로 하는 bfs spanning tree 형성 트리는 서로 "하나"의 간선으로만 이루어 지므로 이런식으로 저장이 가능하다.
	q.push(start);

	while (!q.empty()) {
		int here = q.front();
		q.pop();

		//인접 정점 체크
		for (int i = 0; i < adj[here].size(); ++i) {
			int there = adj[here][i];

			if (distance[there] == -1) {
				q.push(there);
				distance[there] = distance[here] + 1;		//여기선 간선에 가중치가 없어서 그냥 1로 두었다. (몇 level을 거치는지 체크) 그래서 값을 보면 최단거리를 알 수 있도록
				parent[there] = here;		//here이 there의 부모
			}
		}
	}
}

//start ~ v 까지의 최단경로를 반환한다.
vector<int> shortestPath(int v, const vector<int>& parent) {
	vector<int> path(1, v);		//자기자신을 우선 넣공
	while (parent[v] != v) {
		//루트까지 올라가자 (즉 시작점)
		v = parent[v];
		path.push_back(v);
	}
	//v~start을 넣었으니깐 start~v로 보여주려면 뒤집어야 겠죵
	reverse(path.begin(), path.end());
	return path;
}