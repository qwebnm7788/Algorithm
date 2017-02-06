/*
11437 LCA

LCA기본문제
*/
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <vector>
using namespace std;

const int MAX_HEIGHT = 16;
const int MAX_N = 50000;

//인접 리스트
vector<vector<int>> adj;
vector<int> depth;
int parent[MAX_N][MAX_HEIGHT];

//dfs로 스패닝 트리 구현, parent[i][0]로 i번 정점의 2^0번째 조상을 초기화 + depth초기화
void dfs(int here) {
	for (int next : adj[here]) {
		if (depth[next] != -1)
			continue;
		parent[next][0] = here;
		depth[next] = depth[here] + 1;
		dfs(next);
	}
}
int main() {
	freopen("input.txt", "r", stdin);
	int n;
	scanf("%d", &n);

	adj.resize(n);

	int a, b;
	for (int i = 0; i < n - 1; ++i) {
		scanf("%d %d", &a, &b);
		adj[a - 1].push_back(b - 1);
		adj[b - 1].push_back(a - 1);
	}

	//트리 형성
	depth = vector<int>(n, -1);
	memset(parent, -1, sizeof(parent));

	depth[0] = 0;
	dfs(0);

	//bottom-up 으로 parent배열 만들기
	for (int k = 0; k < MAX_HEIGHT; ++k) {
		for (int i = 0; i < n; ++i) {
			if (parent[i][k] != -1)
				parent[i][k + 1] = parent[parent[i][k]][k];		//2^(k+1) = 2^k + 2^k 즉 2^k을 두번 간것과 같다.
		}
	}

	//query
	int m;
	scanf("%d", &m);
	for (int i = 0; i < m; ++i) {
		scanf("%d %d", &a, &b);
		a--;
		b--;

		//a의 깊이가 더 크도록 항상 만들어 주자.
		if (depth[a] < depth[b])
			swap(a, b);

		int diff = depth[a] - depth[b];
		for (int k = 0; k < MAX_HEIGHT; ++k) {
			if (diff % 2)
				a = parent[a][k];
			diff /= 2;
		}

		if (a != b) {
			for (int k = MAX_HEIGHT - 1; k >= 0; --k) {
				if (parent[a][k] != -1 && parent[a][k] != parent[b][k]) {
					a = parent[a][k];
					b = parent[b][k];
				}
			}
			a = parent[a][0];
		}
		printf("%d\n", a+1);
	}
}