/*
한 간선의 양 끝 정점들이 색이 서로 다른 경우에만 루트의 후보가 된다.
모든 루트의 후보들을 체크해봐야 되는데
이렇게 간선에 달린 양쪽 노드의 색이 서로 다른친구들이 왜 후보가 될까?
왜냐면 기본적으로 간선에 양끝에 달린 친구의 색이 다르면 당연히 안되겠었지만
여기서 문제의 조건에 이 친구는 루트와 그 바로밑 자식의 색은 신경쓰지 않는다고 한다.

따라서 이렇게 서로 다른색을 가지는 간선을 가지고도 성립할 수 있는 방법은 서로 다른색을 가진 정점을 잇는 간선들이
모두 루트와 연결된다면 그 밑에 친구들은 그들을 루트로 하는 서브트리에서 같은색을 가진 친구들이 된다.!

만약 이러한 후보 간선이 하나도 없다면 애초에 모든 친구들이 같은색이기 때문에 어떤 정점을 루트로 하던 YES!
*/

#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;


int main() {
	freopen("input.txt", "r", stdin);
	int n;
	cin >> n;

	vector<pair<int, int>> edges;
	int u, v;
	for (int i = 0; i < n - 1; ++i) {
		cin >> u >> v;
		edges.push_back(make_pair(u, v));
	}
	
	vector<int> color(n + 1);
	for (int i = 1; i <= n; ++i)
		cin >> color[i];

	vector<pair<int, int>> candidate;		//루트의 가능성이 있는 친구들을 뽑는다.
	for (auto& x : edges) {
		if (color[x.first] != color[x.second])
			candidate.push_back(x);
	}

	int size = candidate.size();
	if (size == 0) {
		cout << "YES\n1";
		return 0;
	}
	else {
		vector<int> cnt(n + 1); 	//cnt[i] = i번 정점과 연결된 간선중에 색이 다른 정점과 연결된 간선의 수
		for (auto& x : candidate) {
			cnt[x.first]++;
			cnt[x.second]++;
		}
		
		for (int i = 1; i <= n; ++i) {
			if (cnt[i] == size) {			//만약 전체 그래프에서 후보가 되는 간선들이 모두 i번 정점에 이어져 있다면 이 친구를 루트로 한다면 YES!
				cout << "YES\n" << i;
				return 0;
			}
		}
	}
	cout << "NO";
}