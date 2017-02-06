/*
3977 축구전술

scc압축후 indegree가 0인 정점이 단 하나 있어야한다.
없다면 Confused 하나뿐이라면 그 scc컴포넌트에 속한 정점을 정렬 후 뿌려준다.

*/
#include <iostream>
#include <stack>
#include <queue>
#include <vector>
#include <algorithm>
using namespace std;

vector<vector<int>> adj, sccAdj, sccComp;
vector<int> discovered, sccId;
vector<bool> visited;
stack<int> st;
int counter, sccCnt;

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
			sccComp[sccCnt].push_back(x);
			if (x == here)
				break;
		}
		sort(sccComp[sccCnt].begin(), sccComp[sccCnt].end());
		sccCnt++;
	}
	return ret;
}
int main() {
	ios_base::sync_with_stdio(false);

	int test;
	cin >> test;
	for (int z = 0; z < test; ++z) {
		int n, m;
		cin >> n >> m;

		adj = sccComp = vector<vector<int>>(n);
		discovered = sccId = vector<int>(n, -1);
		counter = sccCnt = 0;

		int a, b;
		for (int i = 0; i < m; ++i) {
			cin >> a >> b;
			adj[a].push_back(b);
		}

		for (int i = 0; i < n; ++i)
			if (discovered[i] == -1)
				scc(i);

		sccAdj = vector<vector<int>>(sccCnt);
		vector<int> indegree(sccCnt);

		for (int i = 0; i < n; ++i) {
			int id = sccId[i];
			for (int j : adj[i]) {
				int nextId = sccId[j];
				if (id == nextId)
					continue;
				sccAdj[id].push_back(nextId);
				indegree[nextId]++;
			}
		}

		int start, cnt = 0;
		for (int i = 0; i < sccCnt; ++i) {
			if (indegree[i] == 0) {
				cnt++;
				start = i;
			}
		}

		if (cnt == 1)
			for (int i = 0; i < sccComp[start].size(); ++i)
				printf("%d\n", sccComp[start][i]);
		else
			printf("Confused\n");
		printf("\n");
	}
}