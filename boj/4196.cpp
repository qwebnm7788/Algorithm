/*
4196 도미노

SCC로 압축한 후에 indegree = 0인 정점의 수를 출력하면 된다.
scc로 압축한 컴포넌트 내의 모든 친구들은 하나만 건드리면 모두 순회가능하기 때문에 모두 넘어뜨릴수 있다.
*/
#include <iostream>
#include <stack>
#include <queue>
#include <vector>
#include <algorithm>
using namespace std;

vector<vector<int>> adj;
vector<int> discovered, sccId;
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
			if (x == here)
				break;
		}
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

		vector<vector<int>> sccAdj(sccCnt);
		vector<int> indeg(sccCnt);
		for (int i = 0; i < n; ++i) {
			int id = sccId[i];
			for (int j : adj[i]) {
				int nextId = sccId[j];
				if (id == nextId)
					continue;
				sccAdj[id].push_back(nextId);
				indeg[nextId]++;
			}
		}
		int ans = 0;
		for (int i = 0; i < sccCnt; ++i)
			if (indeg[i] == 0)
				ans++;

		printf("%d\n", ans);
	}
}