#include <iostream>
#include <algorithm>
#include <cstring>
#include <vector>
using namespace std;

const int MAXN = 1e6 + 1;

vector<vector<int>> adj, child;
vector<bool> visited;
vector<bool> isLeaf;
int memo[MAXN][2];

void dfs(int here) {
	visited[here] = true;
	for (int next : adj[here]) {
		if (!visited[next]) {
			child[here].push_back(next);
			dfs(next);
		}
	}
}

//here�� ��Ʈ�� ����Ʈ���� check�� ǥ���Ҷ� ������ �����ϴ� �ʿ��� �ּ��� �󸮾���� ��
int foo(int here, int check) {
	if (isLeaf[here]) return check;
	int& ret = memo[here][check];
	if (ret != -1) return ret;

	ret = check;
	if (check) {
		//here�� �󸮾���Ͷ��
		//�ڽĵ��� �󸮾����, �󸮾���Ͱ� �ƴ� �� �� �ּҰ����� �������ָ� �ȴ�.
		for (int next : child[here]) {
			ret += min(foo(next, 0), foo(next, 1));
		}
	}
	else {
		//here�� �󸮾���Ͱ� �ƴ϶�� -> �ڽ��� ������ �󸮾���Ͱ� �Ǿ�� �Ѵ�.
		for (int next : child[here]) {
			ret += foo(next, 1);			
		}
	}
	return ret;
}
int main() {
	ios_base::sync_with_stdio(false);
	int n;
	cin >> n;

	adj.resize(n);
	child.resize(n);
	visited.assign(n, false);
	isLeaf.assign(n, false);
	int u, v;
	for (int i = 0; i < n; ++i) {
		cin >> u >> v;
		adj[u - 1].push_back(v - 1);
		adj[v - 1].push_back(u - 1);
	}
	dfs(0);
	memset(memo, -1, sizeof(memo));
	cout << min(foo(0, 0), foo(0, 1));
}