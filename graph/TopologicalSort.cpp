#include <vector>
using namespace std;

//adj를 인접행렬 표현이라고 보자. [i][j]사이의 간선이 존재하면 1 아니면 0
vector<vector<int> > adj;

//방문 여부를 저장 1이면 방문 0이면 안방문
vector<int> seen;

//방문되었던 순서를 기록한다.
vector<int> order;

void dfs(int here) {
	seen[here] = 1;
	for (int there = 0; there < adj[here].size(); ++there) {
		//here - there 간선이 존재하며 there를 아직 방문하지 않았다면
		if (adj[here][there] && !seen[there]) {
			dfs(there);
		}
	}
	//here의 모든 인접 정점을 모두 방문한 후에 order에 추가한다.
	order.push_back(here);
}

//adj에 주어진 그래프의 위상정렬 결과를 반환한다.
//주어진 그래프가 DAG가 아니면 빈 벡터를 반환
vector<int> topologicalSort() {
	//변수 초기화
	int n = adj.size();
	seen = vector<int>(n, 0);
	order.clear();

	//dfsALL과 같다.
	for (int i = 0; i < n; ++i) {
		if (!seen[i])
			dfs(i);
	}

	//DFS의 방문결과를 뒤집은 것이 위상정렬의 결과이다.
	reverse(order.begin(), order.end());

	for (int i = 0; i < n; ++i) {
		for (int j = i+1; j < n; ++j) {
			//만약 그래프에 order의 j번 (j > i)에서 i번으로 즉 뒤쪽꺼에서 앞쪽으로 갈 수 있는 간선이 존재한다면 DAG가 아닌것이 되므로
			if (adj[order[j]][order[i]])
				return vector<int>();		//빈 벡터를 반환한다.
		}
	}

	return order;		
}


//////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////


/*
이번에는 좀 더 직관적인 방법을 이용해보면
1. indegree=0인 정점을 큐에 모두 넣는다
2. 큐의 front를 꺼내서 그 정점에서 나가는 간선을 모두 지운다. -> 이때 새롭게 indegree = 0인 정점이 생기면 큐에 또 집어넣는다. --이 과정을 정점 개수만큼 반복해준다.
3. 이 때 큐에서 꺼내는 순서가 위상정렬의 결과이다.

이때 2번 루프를 V번(정점의 수)만큼 돌기 전에 큐가 비어진다면 위상정렬이 불가능하다는 의미이다. -> 즉 싸이클이 생긴다(싸이클에 속하는 정점은 indegree = 0인 점이 없으므로)
또 루프 도중에 큐의 크기가 2 이상인 경우는 위상정렬의 결과가 2개 이상이라는 의미가 된다. 이때는 큐에서 아무거나 빼도 된다( 근데 큐는 순서대로 나와서 뭐. 딱히)

간선을 지우는 작업은 그냥 그 맞은편 정점의 indegree의 값을 하나 줄이는 방법으로 구현해 줄 수 있다.
*/
#include <cstdio>
#include <vector>
#include <queue>
using namespace std;

int main() {
	int N, M;
	int indegree[1000] = { 0 };
	scanf("%d %d", &N, &M);
	
	for (int i = 0; i < M; ++i) {
		int K, prev, curr;
		scanf("%d", &K);
		if (K == 0)
			continue;

		scanf("%d", &prev);
		for (int i = 1; i < K; ++i) {
			scanf("%d", &curr);
			indegree[curr - 1]++;
			adj[prev - 1].push_back(curr - 1);
			prev = curr;
		}
	}

	int result[1000];
	queue<int> Q;

	//우선 맨 처음 indegree = 0인 모든 정점을 큐에 넣는다.
	for (int i = 0; i < N; ++i) {
		if (indegree[i] == 0)
			Q.push(i);
	}

	//위상정렬
	//정점의 개수만큼 루프를 돈다.
	for (int i = 0; i < N; ++i) {
		//중간에 큐가 빈다면 DAG인것이양

		if (Q.empty()) {
			puts("0");
			return 0;
		}

		int curr = Q.front();
		Q.pop();
		result[i] = curr + 1;

		//인접 정점을 순회하면서 indegree를 1씩 감소시킨다(즉 간선을 지운다.)
		//이때 0 이 된다면 큐에 집어넣음
		for (int next : adj[curr]) {
			if (--indegree[next] == 0) {
				Q.push(next);
			}
		}
	}


	//결과 출력
	for (int i = 0; i < N: ++i) {
		printf("%d\n", result[i]);
	}
}