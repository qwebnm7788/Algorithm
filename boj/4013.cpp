/*
4013 ATM

SCC 압축한 그래프에서 start부터 시작해서
도달 가능한 정점에 대해서 그 정점까지 가져갈 수 있는 최대의 액수를 업데이트 해준다.
마지막에 도달가능하고 && 그 SCC컴포넌트에 레스토랑이 있다면 그 값이 정답이 된다.
*/

#include <iostream>
#include <stack>
#include <queue>
#include <algorithm>
#include <vector>
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
	freopen("input.txt", "r", stdin);
	ios_base::sync_with_stdio(false);

	int n, m;
	cin >> n >> m;

	adj.resize(n);
	discovered = sccId = vector<int>(n, -1);

	vector<int> cash(n);
	vector<bool> rest(n);

	int a, b;
	for (int i = 0; i < m; ++i) {
		cin >> a >> b;
		adj[a - 1].push_back(b - 1);
	}
	for (int i = 0; i < n; ++i)
		cin >> cash[i];

	int s, p;
	cin >> s >> p;
	for (int i = 0; i < p; ++i) {
		cin >> a;
		rest[a - 1] = true;
	}

	for (int i = 0; i < n; ++i) {
		if (discovered[i] == -1)
			scc(i);
	}
		
	vector<vector<int>> sccAdj(sccCnt);
	vector<int> indeg(sccCnt);
	vector<long long> sccCash(sccCnt);
	vector<bool> sccRest(sccCnt);

	for (int i = 0; i < n; ++i) {
		int id = sccId[i];
		sccCash[id] += cash[i];
		if (rest[i])
			sccRest[id] = true;
		for (int j : adj[i]) {
			int nextId = sccId[j];
			if (id == nextId)
				continue;
			sccAdj[id].push_back(nextId);
		}
	}

	vector<long long> dist(sccCnt);
	vector<bool> visited(sccCnt);
	queue<int> q;
	s = sccId[s - 1];
	q.push(s);
	for (int i = 0; i < sccCnt; ++i)
		dist[i] = sccCash[i];
	visited[s] = true;

	while (!q.empty()) {
		int curr = q.front();
		q.pop();

		for (int next : sccAdj[curr]) {
			visited[next] = true;
			if (dist[next] < dist[curr] + sccCash[next]) {
				dist[next] = dist[curr] + sccCash[next];
				q.push(next);
			}
		}
	}
	long long ret = 0;
	for (int i = 0; i < sccCnt; ++i) {
		if (visited[i] && sccRest[i])
			ret = max(ret, dist[i]);
	}
	cout << ret;
}