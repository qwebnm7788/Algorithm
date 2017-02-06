/*
3665 최종순위

위상정렬

순위에 대해서 5 4 3 2 1 이라면
5->4, 5->3, 5->2, 5->1, 4->3, 4->2, 4->1 이런식으로 모든 그래프를 형성해준다음

서로 뒤바뀌는 친구들을 a,b라고 하면 기존에 a->b였다면 b->a 가 b->a 였다면 a->b가 되도록 그래프를 수정해준 다음
위상정렬을 시켜주면 된다.

이때 큐의 크기가 2가 넘어가면 여러개의 결과가 가능하고
중간에 큐가 비어버리면 사이클이 형성되었음을 알 수 있다.
*/

#include <cstdio>
#include <queue>
#include <vector>
#include <algorithm>
using namespace std;

int arr[501][501];

int main() {
	freopen("input.txt", "r", stdin);
	int test;
	scanf("%d", &test);

	for (int z = 0; z < test; ++z) {
		int n;
		scanf("%d", &n);

		for (int i = 0; i < n; ++i) {
			for (int j = 0; j < n; ++j)
				arr[i][j] = 0;
		}

		vector<int> before(n);
		vector<int> indeg(n);

		for (int i = 0; i < n; ++i)
			scanf("%d", &before[i]);
		
		for (int i = 0; i < n; ++i) {
			for (int j = i + 1; j < n; ++j) {
				arr[before[i]-1][before[j]-1]++;
				indeg[before[j]-1]++;
			}
		}
		int m;
		scanf("%d", &m);

		int a, b;
		for (int i = 0; i < m; ++i) {
			scanf("%d %d", &a, &b);
			a--;
			b--;
			if (arr[a][b]) {
				arr[a][b]--;
				arr[b][a]++;
				indeg[b]--;
				indeg[a]++;
			}
			else {
				arr[a][b]++;
				arr[b][a]--;
				indeg[b]++;
				indeg[a]--;
			}
		}

		queue<int> q;
		for (int i = 0; i < n; ++i) {
			if (indeg[i] == 0)
				q.push(i);
		}

		bool impossible = false;
		bool ambiguous = false;
		vector<int> ans;
		for (int i = 0; i < n; ++i) {
			if (q.empty()) {
				impossible = true;
				break;
			}
			if (q.size() >= 2)
				ambiguous = true;

			int here = q.front();
			q.pop();
			ans.push_back(here);

			for (int i = 0; i < n; ++i) {
				if (!arr[here][i])
					continue;
				if (--indeg[i] == 0)
					q.push(i);
			}
		}

		if (impossible) {
			printf("IMPOSSIBLE\n");
		}
		else if (ambiguous){
			printf("?\n");
		}
		else {
			for (int i = 0; i < ans.size(); ++i) {
				printf("%d ", ans[i]+1);
			}
			printf("\n");
		}
	}
}
