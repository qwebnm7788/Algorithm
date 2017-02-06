/*
9470 
Strahler 순서
위상정렬
..? 왜맞았는지 잘 모르겠다.
*/
#include <cstdio>
#include <vector>
#include <algorithm>
#include <queue>
using namespace std;

int main() {
	freopen("input.txt", "r", stdin);
	int test;
	scanf("%d", &test);
	for (int z = 0; z < test; ++z) {
		int k, m, p;
		scanf("%d %d %d", &k, &m, &p);

		vector<vector<int>> adj(m);
		vector<int> indeg(m);
		vector<int> rank(m);

		int u, v;
		for (int i = 0; i < p; ++i) {
			scanf("%d %d", &u, &v);
			adj[u - 1].push_back(v - 1);
			indeg[v - 1]++;
		}

		queue<int> q;
		for (int i = 0; i < m; ++i) {
			if (indeg[i] == 0) {
				q.push(i);
				rank[i] = 1;
			}
		}

		//rank[i] = i번 노드의 Strahler 순서이다.

		for (int i = 0; i < m; ++i) {
			int current = q.front();
			q.pop();

			for (int next : adj[current]) {
				//indeg가 1보다 크다면 rank[next]의 값은
				//들어가는 친구의 rank+1이거나 아니면 그냥 이어진 최대값 친구들중 하나겠지?
				//1이 2개 2가 2개였다면 자연스럽게 2+1이 들어갈꺼야
				//1이 2개 2가 1개면 1+1로 갔다가 else로도 가봐서 2로도 갈꺼야.
				//순서대로 있기 때문에 +1 이상 차이 나지 않아서 이렇게 해도
				//성공하는 것 같다.
				if (indeg[next] > 1)
					rank[next] = max(rank[next], rank[current] + 1);
				else
					rank[next] = max(rank[next], rank[current]);
				if (--indeg[next] == 0)
					q.push(next);
			}
		}

		sort(rank.begin(), rank.end());
		printf("%d %d\n", k, rank.back());
	}
}

/*
다른사람들은 지금까지 알려진 최대의 순서 번호와 그 것의 갯수를 끌고가면서
업데이트 시켜주는 방법을 이용하였다.

*/