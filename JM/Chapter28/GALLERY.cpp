#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

const int UNWATCHED = 0;
const int WATCHED = 1;
const int INSTALLED = 2;

int V, H, installed;
vector<vector<int>> adj;
vector<bool> visited;

//dfs(here) = here에서 DFS하고 here의 최종 상태를 반환한다.
int dfs(int here){
	visited[here] = true;
	int children[3] = {0};			//자식들의 상태마다의 수를 체크
	for(int i = 0; i < adj[here].size(); ++i){
		int next = adj[here][i];
		if(!visited[next])
			children[dfs(next)]++;			//인접 정점들은 다 내 children이니깐 상태체크
	}

	//자손들중 감시 안되는 친구가 하나라도 있다면 내가 감시해줘야지
	if(children[UNWATCHED]){
		installed++;
		return INSTALLED;
	}

	//자식들이 다 감시가 되고 나를 감시할 친구도 있다면 나는 설치할 필요없다.
	if(children[INSTALLED])
		return WATCHED;

	//그렇지 않으면 나는 아직 감시가 안되는 친구야
	return UNWATCHED;
}

//정답을 구한다.
int installCamera(){
	installed = 0;
	visited = vector<bool>(V,false);
	for(int i = 0; i < V; ++i){
		if(!visited[i] && dfs(i) == UNWATCHED)		//내가 고르고 들어간 루트도 최종 체크 한번 해줘야된다. (UNWATCHED에 대해서는)
			installed++;
	}
	return installed;
}

int main(){
	ios_base::sync_with_stdio(false);

	int test;
	cin >> test;

	for(int z = 0; z < test; ++z){
		cin >> V >> H;

		adj = vector<vector<int>>(V);

		int u,v;
		for(int i = 0; i < H; ++i){
			cin >> u >> v;
			adj[u].push_back(v);
			adj[v].push_back(u);
		}
		cout << installCamera() << endl;
	}
}