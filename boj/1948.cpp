/*
DAG������ ����Ÿ��� dp�� �̿��Ͽ� ������ �� �ִ�. (�ƴ� ��� np�Ϻ� ������� �Ѵ�)
��� ģ������ �����ϴ� �ð��� �ٽø��ϸ� ���������� �������������� �������� ���̶�� �� �� �ִ�.

���� ���������� �����ϸ� dp�� �̿��Ͽ� ����Ÿ��� ������ָ� �ȴ�.

���� �� ���� ������ ���� ���������� Ȯ���ϴ� �����
here���� ������ ������ dist[here]�� ���� ������ ���� next�� ���� next������ �������� dist[next]�� ����������
���θ� �Ǵ����ָ� �ȴ�.
dist[here] + cost == dist[next] ��� here->next������ �����ο� ���ԵǴ� ������ �ȴ�.
�ߺ��Ǵ� ��츦 �����ϱ� ���Ͽ� 2���� �迭�� ���Ͽ� �ߺ��� ���Ͽ���.
*/
#include <iostream>
#include <queue>
#include <vector>
#include <algorithm>
using namespace std;

int main() {
	ios_base::sync_with_stdio(false);
	int n, m;
	cin >> n >> m;

	vector<vector<pair<int, int>>> adj(n), revAdj(n);
	vector<int> indegree(n, 0);

	int u, v, w;
	for (int i = 0; i < m; ++i) {
		cin >> u >> v >> w;
		adj[u - 1].push_back({ v - 1,w });
		revAdj[v - 1].push_back({ u - 1,w });
		indegree[v - 1]++;
	}

	int start, end;
	cin >> start >> end;
	start--, end--;

	vector<int> dist(n, 0);
	queue<int> q;
	dist[start] = 0;
	q.push(start);
	while (!q.empty()) {
		int here = q.front();
		q.pop();
		for (auto& edge : adj[here]) {
			int next = edge.first;
			int cost = edge.second;
			dist[next] = max(dist[next], dist[here] + cost);
			if (--indegree[next] == 0)
				q.push(next);
		}
	}

	while (!q.empty())
		q.pop();

	vector<vector<bool>> check(n, vector<bool>(n, false));
	int answer = 0;
	q.push(end);
	while (!q.empty()) {
		int here = q.front();
		q.pop();
		if (here == start) continue;
		for (auto& edge : revAdj[here]) {
			int before = edge.first;
			int cost = edge.second;
			if (dist[before] + cost == dist[here] && !check[before][here]) {
				check[before][here] = true;
				answer++;
				q.push(before);
			}
		}
	}
	cout << dist[end] << endl << answer;
}
//ctrl + k + c �ּ�
//#include <iostream>
//#include <queue>
//#include <vector>
//#include <algorithm>
//using namespace std;
//
//const int INF = 2e9;
//
//int main() {
//	ios_base::sync_with_stdio(false);
//	int n, m;
//	cin >> n >> m;
//
//	vector<vector<pair<int, int>>> adj(n);
//	int u, v, w;
//	for (int i = 0; i < m; ++i) {
//		cin >> u >> v >> w;
//		adj[u - 1].push_back({ v - 1,-w });
//	}
//
//	int start, end;
//	cin >> start >> end;
//	start--, end--;
//
//	priority_queue<pair<int, int>> pq;
//	vector<int> dist(n, INF);
//	vector<vector<int>> prev(n);
//	dist[start] = 0;
//	pq.push({ 0,start });
//	while (!pq.empty()) {
//		int here = pq.top().second;
//		int cost = pq.top().first;
//		pq.pop();
//		if (dist[here] < cost) continue;
//		for (auto& edge : adj[here]) {
//			int next = edge.first;
//			int nextCost = edge.second;
//			if (dist[next] > cost + nextCost) {
//				dist[next] = cost + nextCost;
//				prev[next].clear();
//				prev[next].push_back(here);
//				pq.push({ dist[next],next });
//			}
//			else if (dist[next] == cost + nextCost) {
//				prev[next].push_back(here);
//			}
//		}
//	}
//
//	vector<bool> visited(n, false);
//	vector<vector<bool>> edgeCheck(n, vector<bool>(n, false));
//	queue<int> q;
//	visited[end] = true;
//	q.push(end);
//	int answer = 0;
//	while (!q.empty()) {
//		int here = q.front();
//		q.pop();
//		if (here == start) continue;
//		for (int before : prev[here]) {
//			if (!visited[before]) {
//				visited[before] = true;
//				q.push(before);
//			}
//			if (!edgeCheck[before][here]) {
//				edgeCheck[before][here] = true;
//				answer++;
//			}
//		}
//	}
//	cout << -dist[end] << endl << answer;
//}
