/*
2637 장난감 조립

위상정렬의 순서대로 필요한 부품의 수를 누적해서 끌고 올라가면 마지막 최종 완성품을
만드는데 필요한 모든 부품의 수를 알 수 있다. (현재 완성물에 필요한 중간부품의 수 X 그 중간부품을 만드는데 필요한 각 재료)
*/
#include <cstdio>
#include <algorithm>
#include <vector>
#include <queue>
using namespace std;

//arr[i][j] = i번 부품을 만드는데 j번 부품이 몇개 필요한지
int arr[101][101];

int main() {
	freopen("input.txt", "r", stdin);
	int n;
	scanf("%d", &n);

	//adj[i] = i번 부품이 adj[i][j].first 제품을 만드는데 adj[i][j].second개 필요하다.
	vector<vector<pair<int,int>>> adj(n);
	vector<int> indeg(n);
	vector<bool> basic(n, false);

	int m;
	scanf("%d", &m);

	int a, b, c;
	for (int i = 0; i < m; ++i) {
		scanf("%d %d %d", &a, &b, &c);
		adj[b - 1].push_back(make_pair(a - 1, c));
		indeg[a - 1]++;
	}

	queue<int> q;
	for (int i = 0; i < n; ++i) {
		if (indeg[i] == 0) {
			q.push(i);
			arr[i][i] = 1;
			basic[i] = true;
		}
	}

	for (int i = 0; i < n; ++i) {
		int current = q.front();
		q.pop();
	
		for (auto& next : adj[current]) {
			for (int i = 0; i < n; ++i)
				arr[next.first][i] += (next.second*arr[current][i]);

			if (--indeg[next.first] == 0)
				q.push(next.first);
		}
	}

	for (int i = 0; i < n; ++i) {
		if (basic[i])
			printf("%d %d\n", i + 1, arr[n - 1][i]);
	}
}