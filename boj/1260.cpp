#include <iostream>
#include <queue>
#include <vector>
#include <algorithm>
using namespace std;

vector<vector<int>> adj;
vector<bool> visited;

void dfs(int here){
	visited[here] = true;
	cout << here + 1 << " ";
	for(int next : adj[here]){
		if(!visited[next]) dfs(next);
	}
}

void bfs(int start){
	queue<int> q;
	q.push(start);
	visited[start] = true;
	while(!q.empty()){
		int here = q.front();
		q.pop();
		cout << here + 1 << " ";
		for(int next : adj[here]){
			if(!visited[next]){
				visited[next] = true;
				q.push(next);
			}
		}
	}
}

int main(){
	int n,m,v;
	cin >> n >> m >> v;

	adj.resize(n);
	visited.resize(n,false);
	int x,y;
	for(int i = 0; i < m; ++i){
		cin >> x >> y;
		adj[x-1].push_back(y-1);
		adj[y-1].push_back(x-1);
	}

	for(int i = 0; i < n; ++i)
		sort(adj[i].begin(),adj[i].end());

	dfs(v-1);
	visited = vector<bool>(n,false);
	cout << endl;
	bfs(v-1);
}
