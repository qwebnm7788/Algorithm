/*
13306번 트리

결국에는 모든 에지를 제거하게 되므로 맨 마지막에는 각 정점들이 개별적인 정점하나로 구성된
트리를 만든다.

입력된 쿼리를 모두 저장한 후에 거꾸로 진행한다.

union-find를 활용하여 진행하면 되는데
만약 에지를 지우는 쿼리의 경우 두 정점을 merge를 하고 둘의 연결성을 묻는다면 find연산을 통해 확인해줄 수 있다.

이렇게 쿼리를 들어올때 바로 처리하는것이 아닌 나중에 처리하는 것을 오프라인 쿼리라고 한다.;
*/
#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;

vector<int> parent;
vector<int> hasParent;

int find(int x) {
	if (x == parent[x]) return x;
	return parent[x] = find(parent[x]);
}

void merge(int a, int b) {
	a = find(a);
	b = find(b);
	if (a == b) return;
	parent[b] = a;
}

int main() {
	ios_base::sync_with_stdio(false);
	int n, q;
	cin >> n >> q;

	hasParent.resize(n);
	parent.resize(n);

	hasParent[0] = 0;
	for (int i = 1; i < n; ++i) {
		cin >> hasParent[i];
		hasParent[i]--;
	}
	for (int i = 0; i < n; ++i) parent[i] = i;

	vector<pair<int, pair<int, int>>> query;
	int a, b, c;
	for (int i = 0; i < n - 1 + q; ++i) {
		cin >> a;
		if (a == 0) {
			cin >> b;
			query.push_back(make_pair(a, make_pair(b - 1, 0)));
		}
		else {
			cin >> b >> c;
			query.push_back(make_pair(a, make_pair(b - 1, c - 1)));
		}
	}

	reverse(query.begin(), query.end());
	vector<bool> ans;
	for (int i = 0; i < n - 1 + q; ++i) {
		if (query[i].first == 0)
			merge(query[i].second.first, hasParent[query[i].second.first]);
		else {
			if (find(query[i].second.first) == find(query[i].second.second)) ans.push_back(true);
			else ans.push_back(false);
		}
	}
	reverse(ans.begin(), ans.end());
	for (int i = 0; i < q; ++i) cout << (ans[i] ? "YES\n" : "NO\n");
}