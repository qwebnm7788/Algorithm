/*
1944 복제로봇

지나갈수 있는 위치를 정점으로 생각해보자 각 정점은 상하좌우로 최대 4개의 정점과 연결될 수 있다.
이때 모든 간선의 가중치를 1이라고 생각해보면 한친구가 다른친구로 갈 수 있는 최단거리는 어떤 경로를 통해서 가더라도
방향만 대강 맞아주면 어떤 경로를 타도 같은 거리가 나온다.

이문제에서 원하는 것은 S와 모든 K를 잇는 MST를 구하는것인데 모든 K와 S에서 원하는 만큼 로봇을 복제할 수 있으므로
예제에서 보면 S에서 2개를 복제해서 각K를 목표로 출발시키면 된다.

그냥 필요한대로 알아서 K에서 복제된다고 생각해보면 그냥 각 S와 K정점들 사이를 최단거리로 이동하는 경로만을 생각해보면 된다.

이제 모든 S,K 사이의 최단거리를 모두 계산해주고 그것을 간선으로 모두 연결했다고 생각하자
(즉 이제 grid로 표시된 친구말고 s-k1 s-k2 k1-k2 이렇게 최단거리 간선으로 모두 연결해주자)

이 그래프를 이용해서 크루스칼이나, 프림 알고리즘을 이용해서 MST를 뽑아내서 MST의 가중치를 반환해준 것이 원하는 결과가 된다.
*/

//크루스칼이 O(ElogE)가 걸리고, BFS가 O(|V|+|E|)이 걸린다. 근데 BFS를 (m+1)번을 돌리니깐 그리고 |E|의 수는 대략 n^2이니깐
//O((m+1)n^2)이 걸리지 않을깡? m이 n보다 최대 5배 크다. 약 O(n^3)정도 걸리는것 같다. 근데 n = 50이라서 10^5정도라서
//1초안에 충분히 끝낼 수 있다.. 맞나?

#include <stdio.h>
#include <vector>
#include <algorithm>
#include <queue>
using namespace std;

vector<int> parent;
char arr[51][51];
bool visited[51][51];
int index[51][51];				//arr[i][j]='S','K'가 있는 친구들을 구분지어줘야 되는데 그냥 이렇게 배열을 만들어서 구분했다. [i][j]에 있는 K가 다른 i`,j`에 있는 K와 구분되어야 하니깐
int dx[4] = { -1,0,1,0 };
int dy[4] = { 0,1,0,-1 };

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
	freopen("input.txt", "r", stdin);

	int n, m;
	scanf("%d %d", &n, &m);
	getchar();
	vector<pair<int, int>> startWith;			//필요한 정점은 S,K가 있는 정점이되므로 이곳에 넣어준당
	int cnt = 1;
	for (int i = 0; i < n; ++i) {
		for (int j = 0; j < n; ++j) {
			scanf("%c", &arr[i][j]);
			if (arr[i][j] == 'S' || arr[i][j] =='K') {
				startWith.push_back(make_pair(i, j));
				if (arr[i][j] == 'S')
					index[i][j] = 0;
				else
					index[i][j] = cnt++;
			}
		}
		getchar();
	}

	vector<pair<int, pair<int, int>>> edges;
	for (int w = 0; w < startWith.size(); ++w) {
		int startR = startWith[w].first;
		int startC = startWith[w].second;

		for (int i = 0; i < n; ++i) {
			for (int j = 0; j < n; ++j)
				visited[i][j] = false;
		}
		int level = 0, size;

		queue<pair<int, int>> q;
		q.push(make_pair(startR, startC));
		visited[startR][startC] = true;

		while (!q.empty()) {
			size = q.size();
			for (int z = 0; z < size; ++z) {
				int currentR = q.front().first;
				int currentC = q.front().second;
				q.pop();

				if (arr[currentR][currentC] == 'S' || arr[currentR][currentC] == 'K') {
					if ((currentR != startR) || (currentC != startC))
						edges.push_back(make_pair(level, make_pair(index[startR][startC], index[currentR][currentC])));
				}

				for (int i = 0; i < 4; ++i) {
					int nextR = currentR + dx[i];
					int nextC = currentC + dy[i];
					if ((nextR >= 0 && nextR < n) && (nextC >= 0 && nextC < n)) {
						if (!visited[nextR][nextC] && arr[nextR][nextC] != '1') {
							visited[nextR][nextC] = true;
							q.push(make_pair(nextR, nextC));
						}
					}
				}
			}
			level++;
		}

		//S에서 모든 K에 도달할 수 없다면 모든 키를 찾을 수 없는 것이 되어 -1을 출력한다.
		//이렇게 말고 다른방법이 있지않을까?..
		if (arr[startR][startC] == 'S') {
			for (int i = 0; i < n; ++i) {
				for (int j = 0; j < n; ++j) {
					if (arr[i][j] == 'K') {
						if (!visited[i][j]) {
							printf("-1");
							return 0;
						}
					}
				}
			}
		}
	}
	
	//요기서부턴 크루스칼 알고리즘 이용
	//정점의 수는 key의 수와 시작점 S이므로 m+1개가 된다.
	parent = vector<int>(m + 1, -1);

	sort(edges.begin(), edges.end());

	cnt = 0;
	int ans = 0;
	for (int i = 0; i < edges.size(); ++i) {
		int u = edges[i].second.first;
		int v = edges[i].second.second;
		int w = edges[i].first;

		if (merge(u, v)) {
			ans += w;
			cnt++;
			if (cnt == m)
				break;
		}
	}

	printf("%d", ans);
}