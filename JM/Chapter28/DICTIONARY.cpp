#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
using namespace std;

//인접리스트 표현
//i->j간선이 존재한다면 adj[i][j] = 1로 표현한다.
//(i,j)간선은 i번 알파벳이 j번보다 먼저 와야 한다는 의미.
vector<vector<int>> adj;
vector<int> seen, order;		//seen[i] = i번 정점의 방문 여부(1이면 방문 0이면 안방문), order[i] = i번째 종료된 정점의 번호.

//주어진 단어들로부터 알파벳의 전후관계를 이용한 방향그래프를 형성한다.
void makeGraph(const vector<string>& words) {
	adj = vector<vector<int>>(26, vector<int>(26, 0));		//알파벳의 갯수로 초기화
	//i j ... 처럼 인접한 두 친구만을 비교한다.
	for (int j = 1; j < words.size(); ++j) {
		int i = j - 1;
		int len = min(words[i].size(), words[j].size());
		
		//words[i]가 words[j]보다 앞에 있는 이유를 찾는다. (즉 둘이 다른 글자를 앞에서부터 찾아본다.)
		for (int k = 0; k < len; ++k) {
			if (words[i][k] != words[j][k]) {
				int a = words[i][k] - 'a';
				int b = words[j][k] - 'a';
				adj[a][b] = 1;		//a가 b보다 먼저와야 되니깐 간선을 추가한다.
				break;
			}
		}
	}
}

void dfs(int here) {
	seen[here] = 1;
	for (int there = 0; there < adj[here].size(); ++there) {
		if (adj[here][there] && !seen[there])
			dfs(there);
	}
	order.push_back(here);			//dfs를 빠져나오면서 order에 집어넣어준다. 즉 종료되는 순서대로 들어간다. (가장 먼저 종료되는 친구가 제일 앞에 있다.)
}

vector<int> topologicalSort() {
	int n = adj.size();
	seen = vector<int>(n, 0);
	order.clear();
	for (int i = 0; i < n; ++i)
		if (!seen[i])
			dfs(i);
	reverse(order.begin(), order.end());

	//만약에 DAG가 성립하지 않는다면 왼쪽으로 가는 간선이 존재한다.
	for (int i = 0; i < n; ++i) {
		for (int j = i + 1; j < n; ++j) {
			if (adj[order[j]][order[i]])
				return vector<int>();
		}
	}
	return order;
}
int main() {
	freopen("input.txt", "r", stdin);

	int test;
	cin >> test;

	for (int z = 0; z < test; ++z) {
		int n;
		cin >> n;

		vector<string> words(n);
		for (int i = 0; i < n; ++i)
			cin >> words[i];

		makeGraph(words);
		vector<int> ans = topologicalSort();

		if (ans.size()) {
			for (int i = 0; i < ans.size(); ++i)
				cout << (char)(ans[i]+'a');
			cout << endl;
		}
		else
			cout << "INVALID HYPOTHESIS\n";
	}
}