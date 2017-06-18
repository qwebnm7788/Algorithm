/*
6091번 핑크 플로이드

주어진 인접행렬을 이용하여 트리를 재구성하는 문제

트리는 항상 두 정점사이에 하나의 경로만이 존재하기 때문에 최단거리를 표현한 것인 플로이드의 결과를
그리디하게? 찾아주면 된다.

즉 입력된 간선들을 정렬한 후 거리가 가장 작은 간선을 확인한다.
만약 간선이 연결하는 두 정점이 아직 연결되지 않았다면 이어주고
이미 연결되어 있다면 무시한다. 왜냐면 둘이 이미 이어져 있다면(union find에서 하나의 집합에 들어간다면)
그것들의 경로를 이용하여 움직이면 지금 보고 있는 거리가 된다. (왜냐면 트리의 경로는 단 1개이므로)
*/
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

vector<int> parent;

int find(int x) {
	if (x == parent[x]) return x;
	return parent[x] = find(parent[x]);
}

bool merge(int a, int b) {
	a = find(a);
	b = find(b);
	if (a == b) return false;
	parent[b] = a;
	return true;
}

int main() {
	ios_base::sync_with_stdio(false);
	freopen("input.txt", "r", stdin);
	int n;
	cin >> n;

	parent.resize(n);
	for (int i = 0; i < n; ++i) parent[i] = i;

	vector<pair<int, pair<int, int>>> edge;
	int x;
	for (int i = 0; i < n; ++i) {
		for (int j = i + 1; j < n; ++j) {
			cin >> x;
			edge.push_back(make_pair(x, make_pair(i, j)));
		}
	}

	sort(edge.begin(), edge.end());

	vector<vector<int>> adj(n);
	for (int i = 0; i < edge.size(); ++i) {
		int u = edge[i].second.first;
		int v = edge[i].second.second;
		if (merge(u, v)) {
			adj[u].push_back(v);
			adj[v].push_back(u);
		}
	}

	for (int i = 0; i < n; ++i){
		cout << adj[i].size() << " ";
		sort(adj[i].begin(), adj[i].end());
		for (int j = 0; j < adj[i].size(); ++j){
			cout << adj[i][j] + 1 << " ";
		}
		cout << endl;
	}
}