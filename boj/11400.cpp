#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

vector<vector<int>> adj;
vector<int> discovered;
vector<pair<int,int>> ans;

int counter = 0;

int dfs(int here, int parent){
	discovered[here] = counter++;
	int ret = discovered[here];

	for(int i = 0; i < adj[here].size(); ++i){
		int next = adj[here][i];

		if(discovered[next] == -1){
			int highest = dfs(next,here);

			if(highest >= discovered[here])
				ans.push_back(min(here,next),max(here,next));

			ret = min(ret, highest);
		}else{
			ret = min(ret, discovered[next]);
		}
	}

	return ret;
}
int main (){
	int v,e;
	cin >> v >> e;

	int a,b;
	for(int i = 0; i< e; ++i){
		cin >> a >> b;
		adj[a-1].push_back(b-1);
		adj[b-1].push_back(a-1);
	}

	cout << ans.size() << endl;
	for(int i = 0; i < ans.size(); ++i){
		cout << ans[i].first << " " << ans[i].second << endl;
	}

}

