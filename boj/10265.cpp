/*
10265 MT

i번 친구가 xi가 없으면 안된다는 내용을 xi->i 로의 간선을 추가해줌으로써 의존관계로 표현해주자.
그렇게 되면 그래프에는 사이클이 형성되는 그룹이 생기는데 이 친구들은 한명이 타면 그 그룹 전부가 동시에 타야한다.

이를 간단하게 SCC 그래프로 압축시켜주자.

이렇게 되면 indegree가 0인 친구들을 먼저 태워주어야 그에 연결된 무리들도 태울 수 있는 가능성이 (안태워도 되고) 생기게 되므로
위상정렬을 indegree가 0인 친구들을 모두 잡아주자.

이때 이 친구를 태울때 가능한 모든 인원의 수는 그 정점의 SCC컴포넌트 크기 ~ 그 SCC정점으로 시작되는 연결그래프의 총 정점의 수 까지가 된다.
즉 indegree=0인 친구를 태우는 순간 그 SCC컴포넌트의 크기만큼은 무조건이고 이제 그 SCC를 따라가면서 한명씩 늘려볼수도 있고 그 것의 최대는 그 그래프의 총 정점 수와같다.

따라서 모든 경우를 시도해보면 되는데 N이 1000으로 작기 떄문에 1000*1000 = 10^6으로 다이나믹 프로그래밍을 이용하면
좀 더 빠르게 문제를 해결할 수 있다.

이 문제의 핵심 포인트는 가능한 인원의 수의 범위를 알아차리는 것 + 다이나믹 프로그래밍을 활용하는것. (안써도 되지 않을까? 10^6인데)
*/
#include <iostream>
#include <string.h>
#include <queue>
#include <vector>
#include <stack>
#include <algorithm>
using namespace std;

const int MAX_N = 1001;
const int MAX_K = 1001;

vector<vector<int>> adj, sccAdj;
vector<int> discovered, sccId;
vector<pair<int, int>> target;
stack<int> st;
int n, k, counter, sccCnt;
int cache[MAX_N][MAX_K];

//here에서 올라갈 수 있는 가장 빠른 발견순서를 반환한다.
int dfs(int here) {
	int ret = discovered[here] = counter++;

	st.push(here);
	for (int next : adj[here]) {
		if (discovered[next] == -1)
			ret = min(ret, dfs(next));
		else if (sccId[next] == -1)
			ret = min(ret, discovered[next]);
	}

	if(ret == discovered[here]){
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

//here에서 시작해서 방문가능한 연결그래프의 크기를 반환한다.
void dfs2(int here, vector<bool>& visited) {
	visited[here] = true;
	for (int next : sccAdj[here]) {
		if (!visited[next])
			dfs2(next,visited);
	}
}

//index번 SCC가 있는 그래프내에서 vacant의 공백이 있을때 가능한 최대의 수를 반환한다.
int foo(int index, int vacant) {
	if (index == target.size()) return 0;

	int first = target[index].first;
	int second = target[index].second;

	int& ret = cache[index][vacant];
	if (ret != -1) return ret;
	ret = foo(index + 1, vacant);		//안 태우거나.

	//가능한 모든 범위를 다 태워보거나.!
	for (int i = first; i <= second; ++i) {
		if (vacant >= i)
			ret = max(ret, foo(index + 1, vacant - i) + i);
	}
	return ret;
}

int main() {
	freopen("input.txt", "r", stdin);

	cin >> n >> k;
	
	adj.resize(n);
	discovered = sccId = vector<int>(n, -1);

	int x;
	for (int i = 0; i < n; ++i) {
		cin >> x;
		adj[x - 1].push_back(i);
	}

	for (int i = 0; i < n; ++i) {
		if (discovered[i] == -1)
			dfs(i);
	}

	sccAdj.resize(sccCnt);
	vector<int> indeg(sccCnt), sccSize(sccCnt), maxSize(sccCnt);

	for (int i = 0; i < n; ++i) {
		int id = sccId[i];
		sccSize[id]++;
		for (int j : adj[i]) {
			int nextId = sccId[j];
			if (id == nextId)
				continue;
			sccAdj[id].push_back(nextId);
			indeg[nextId]++;
		}
	}
	
	
	//indegree=0인 점이 포함된 연결그래프의 크기를 계산한다.
	for (int i = 0; i < sccCnt; ++i) {
		if (indeg[i] == 0) {
			vector<bool> visited(sccCnt, false);
			dfs2(i, visited);
			for (int j = 0; j < sccCnt; ++j) {
				if (visited[j])
					maxSize[i]++;
			}
			target.push_back(make_pair(sccSize[i], sccSize[i] + maxSize[i] - 1));
		}
	}


	//knapsack 처럼 계산 !
	memset(&cache, -1, sizeof(cache));
	cout << foo(0, k);
}