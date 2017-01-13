#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

vector<int> parent;

int find(int x) {
	if (parent[x] < 0)
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
	while (true) {
		int m, n;
		cin >> m >> n;

		if (m == 0 && n == 0)
			break;

		vector<pair<int, pair<int, int>>> edges;
		parent = vector<int>(m, -1);

		int x, y, z;
		int total = 0;

		for (int i = 0; i < n; ++i) {
			cin >> x >> y >> z;
			edges.push_back(make_pair(z, make_pair(x, y)));
			total += z;
		}

		sort(edges.begin(), edges.end());

		int cnt = 0;

		for (int i = 0; i < edges.size(); ++i) {
			int u = edges[i].second.first;
			int v = edges[i].second.second;
			int cost = edges[i].first;

			if (merge(u, v)) {
				cnt++;
				total -= cost;
			}

			if (cnt == m - 1)
				break;
		}

		cout << total << endl;
	}
	
}