/*
2623 음악 프로그램

위상정렬
*/
#include <cstdio>
#include <vector>
#include <queue>
using namespace std;

int main() {
	freopen("input.txt", "r", stdin);
	int n, m;
	scanf("%d %d", &n, &m);

	vector<vector<int>> adj(n);
	vector<int> indeg(n, 0);

	int cnt, prev, curr;
	for (int i = 0; i < m; ++i) {
		scanf("%d", &cnt);
		for (int j = 0; j < cnt; ++j) {
			if (j) {
				prev = curr;
				scanf("%d", &curr);
				adj[prev - 1].push_back(curr - 1);
				indeg[curr - 1]++;
			}
			else {
				scanf("%d", &curr);
			}
		}
	}

	queue<int> q;
	vector<int> ans;

	for (int i = 0; i < n; ++i) {
		if (indeg[i] == 0)
			q.push(i);
	}

	bool check = true;
	for (int i = 0; i < n; ++i) {
		if (q.empty()) {
			check = false;
			break;
		}

		int here = q.front();
		q.pop();
		ans.push_back(here);

		for (int next : adj[here]) {
			if (--indeg[next] == 0)
				q.push(next);
		}
	}
	if (check) {
		for (int i = 0; i < ans.size(); ++i)
			printf("%d\n", ans[i]+1);
	}
	else {
		printf("0");
	}
}