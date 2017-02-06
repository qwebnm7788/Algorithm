/*
2152 여행계획 세우기

scc로 압축후 위상정렬을 해주면서 구해줄수 있는데

왜 scc 발견의 역순으로 진행하면 성공하지 못하는지 모르겠다.
*/
#include <iostream>
#include <vector>
#include <stack>
#include <queue>
#include <algorithm>
using namespace std;

vector<vector<int>> adj;
vector<int> discovered, sccId;
stack<int> comp;
int sccCnt, counter;

//here을 루트로하는 서브트리에서 갈 수 있는 최소 방문번호를 반환한다.
int scc(int here){
	int ret = discovered[here] = counter++;
	comp.push(here);
	for (int next : adj[here]) {
		if (discovered[next] == -1)
			ret = min(ret, scc(next));
		else if (sccId[next] == -1)
			ret = min(ret, discovered[next]);
	}

	if (ret == discovered[here]) {
		while (true) {
			int x = comp.top();
			comp.pop();
			sccId[x] = sccCnt;
			if (x == here)
				break;
		}
		sccCnt++;
	}
	return ret;
}
int main() {
	freopen("input.txt", "r", stdin);
	ios_base::sync_with_stdio(false);

	int n, m, s, t;
	cin >> n >> m >> s >> t;

	adj.resize(n);
	discovered = sccId = vector<int>(n, -1);

	int a, b;
	for (int i = 0; i < m; ++i) {
		cin >> a >> b;
		adj[a - 1].push_back(b - 1);
	}
	
	for (int i = 0; i < n; ++i)
		if (discovered[i] == -1)
			scc(i);

	//scc 컴포넌트로 이루어진 압축그래프를 새로 만든다.
	vector<vector<int>> sccAdj(sccCnt);
	vector<int> sccSize(sccCnt);
	vector<int> indeg(sccCnt);
	s = sccId[s - 1];			//시작도시가 속한 scc번호로 대체
	t = sccId[t - 1];			//끝 도시 ""


	//위상정렬 전처리
	for (int i = 0; i < n; ++i) {
		int id = sccId[i];
		sccSize[id]++;			//컴포넌트의 수는 그 컴포넌트에 속한 도시의 수 자체이므로 그냥 더한다.
		for (int j : adj[i]) {
			int nextId = sccId[j];
			if (id == nextId)
				continue;
			sccAdj[id].push_back(nextId);
			indeg[nextId]++;
		}
	}

	queue<int> q;
	vector<bool> reachable(sccCnt, false);		//시작점이 속한 컴포넌트에서 도달가능한 컴포넌트의 여부
	vector<int> ans(sccCnt, 0);					//ans[i] = 시작점 ~ i번 컴포넌트까지 갔을때 거칠수 있는 최대의 도시의 갯수
	reachable[s] = true;		//시작컴포넌트는 당연히 true
	for (int i = 0; i < sccCnt; ++i) {
		ans[i] = sccSize[i];			//우선 초기화는 각 컴포넌트의 도시의 수와 같다.
		if (indeg[i] == 0)
			q.push(i);
	}
		

	while (!q.empty()) {
		int curr = q.front();
		q.pop();

		for (int next : sccAdj[curr]) {
			if (reachable[curr]) {			//시작점에서 도달가능한 지점만 이동가능하므로 해준다.
				ans[next] = max(ans[next], ans[curr] + sccSize[next]);		//next 컴포넌트까지 갔을때의 시작점에서 방문가능한 최대의 도시 갯수는 here까지의 최대수 + next컴포넌트의 크기와 같다.
				reachable[next] = true;
			}
			if (--indeg[next] == 0)
				q.push(next);
		}
	}
	if (reachable[t])		//도착도시가 속한 컴포넌트가 시작도시가 속한 컴포넌트에서 도달가능하다면
		printf("%d", ans[t]);
	else
		printf("0");
}