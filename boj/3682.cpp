/*
3682
동치 증명

ㅜㅜ

명제들이 동치라는 말은 하나의 SCC로 묶인다는 말과 같다. (즉 이 명제들을 정점으로 표현했을때 전체를 포함하는 사이클이 형성된다는 것과 같다.)

우선 주어진 명제로 이미 사이클을 형성하는 친구들을 찾는 방법은 간단하다.
주어진 그래프를 이용해서 SCC를 형성하도록 하면 같은 컴포넌트에 속하는 친구들이 바로 그런 애들이다.
이런 친구들은 더이상 신경쓰지 않아도 된다.

이렇게 생긴 SCC를 이용해서 새로운 압축된 그래프를 만들어주자.
이 그래프는 DAG인데 이 친구가 사이클이 생기게 되려면 어떤 간선을 만들어 주어야 할까?

압축된 그래프에서 압축된 정점에 대해서 indegree와 outdegree를 계산해주자.
이때 indegree[i] == 0 이거나 outdegree[i] == 0인 정점의 수를 생각해보자. 
이러한 정점이 존재하기는 할까? -> DAG이기 때문에 최소한 시작점과 끝점은 이러한 조건을 만족할 것이고 압축 전의 그래프가 연결그래프가 아닐 수 있기 때문에
압축된 그래프 또한 연결되지 않을 수 있다. 따라서 컴포넌트가 여러개과 되어서도 이러한 조건을 만들 수 있다.

indegree==0인 정점과 outdegree==0인 정점은 잘 생각해보면 한 컴포넌트에서의 시작부분과 끝부분일 것이다.
만약 둘의 갯수가 같았다면 둘을 잘 대응시켜서 연결해주게 되면 사이클을 형성해줄 수 있음을 알 수 있다.

만약에 둘의 갯수가 달랐다면 어떨까?

indegree==0인 정점이 더 많다고 생각해보자.
예를 들면 1->3, 2->3인 상황을 보자. 위 처럼 3->1을 그어주기만 하면 전체가 사이클이 되지 못하고 일부분만 형성되게 된다.
따라서 outdegree가 0이었던 친구가 하나의 간선뿐아니라 남아있는 친구들도 전부다 이어주어서
3->1, 3->2를 그어주어야지 전체가 SCC가 되면서 원하는 그래프가 된다.

outdegree==0인 정점이 더 많은 경우는 어떨까?
예제입력에 주어진 경우가 바로 그런 경우인데 
1->2, 1->3 인경우이다. 이럴때는 그냥 outdegree==0 인 친구들을 모두 indegree==0이었던 곳에 최대한 퍼지게 해준다음 남은 친구들은 indegree==0이었던
아무곳에나 꽂혀지면된다.

둘 중 하나가 0인 경우가 있을까?
DAG에서는 그럴수 없다.!

이 때 예외가 하나 있는데
SCC로 압축한 새로운 그래프에 컴포넌트가 1개만 있는 경우에는 이친구들은 나의 끝부분이 나의 머리에 다시 꽂힐 필요가 없다.
따라서 이때는 0을 출력해주면 된다.

*/
#include <iostream>
#include <stack>
#include <queue>
#include <algorithm>
#include <vector>
using namespace std;

vector<vector<int>> adj, sccAdj;
vector<int> sccId, discovered;
vector<bool> visited;
stack<int> st;
int counter, sccCnt;

void dfs(int here) {
	visited[here] = true;
	for (int next : sccAdj[here]) {
		if (!visited[next]) {
			dfs(next);
		}
	}
}

int scc(int here) {
	int ret = discovered[here] = counter++;
	st.push(here);
	for (int next : adj[here]) {
		if (discovered[next] == -1)
			ret = min(ret, scc(next));
		else if (sccId[next] == -1)
			ret = min(ret, discovered[next]);
	}
	if (ret == discovered[here]) {
		while (true) {
			int x = st.top();
			st.pop();
			sccId[x] = sccCnt;
			if (x == here)
				break;
		}
		sccCnt++;
	}
	return ret;
}

int main() {
	ios_base::sync_with_stdio(false);
	freopen("input.txt", "r", stdin);

	int test;
	cin >> test;

	for (int z = 0; z < test; ++z) {
		int n, m;
		cin >> n >> m;

		adj = vector<vector<int>>(n);
		discovered = sccId = vector<int>(n, -1);
		counter = sccCnt = 0;

		int a, b;
		for (int i = 0; i < m; ++i) {
			cin >> a >> b;
			adj[a - 1].push_back(b - 1);
		}

		for (int i = 0; i < n; ++i)
			if (discovered[i] == -1)
				scc(i);

		//graph condensation
		sccAdj = vector<vector<int>>(sccCnt);
		vector<int> indeg(sccCnt);
		vector<int> outdeg(sccCnt);

		for (int i = 0; i < n; ++i) {
			int id = sccId[i];
			for (int j : adj[i]) {
				int nextId = sccId[j];
				if (id == nextId)
					continue;
				sccAdj[id].push_back(nextId);
				indeg[nextId]++;
				outdeg[id]++;
			}
		}

		int in = 0, out = 0;
		for (int i = 0; i < sccCnt; ++i) {
			if (indeg[i] == 0)
				in++;
			if (outdeg[i] == 0)
				out++;
		}
		
		if (sccCnt == 1)
			printf("0\n");
		else
			printf("%d\n", max(in, out));
	}
}
