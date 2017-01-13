#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int parent[1001];

int find(int x) {
	if (parent[x] == x)
		return x;
	return parent[x] = find(parent[x]);
}

bool merge(int a, int b) {
	a = find(a);
	b = find(b);
	if (a == b)
		return false;
	parent[b] = a;
	return true;
}

int main() {
	ios_base::sync_with_stdio(false);
	freopen("input.txt", "r", stdin);
	int n, m;
	cin >> n >> m;

	for (int i = 0; i < n; ++i)
		parent[i] = i;

	vector<pair<int, pair<int, int>>> edges;
	int a, b, c;
	for (int i = 0; i < m; ++i) {
		cin >> a >> b >> c;
		edges.push_back(make_pair(c, make_pair(a, b)));
	}

	sort(edges.begin(), edges.end());

	int ans = 0;
	int cnt = 0;
	for (int i = 0; i < edges.size(); ++i) {
		int u = edges[i].second.first;
		int v = edges[i].second.second;
		int w = edges[i].first;

		if (merge(u, v)) {
			ans += w;
			cnt++;
		}
		if (cnt == n - 1)
			break;
	}

	cout << ans;
}