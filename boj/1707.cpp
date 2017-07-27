#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
using namespace std;

vector<vector<int>> adj;
vector<int> check;
vector<bool> visited;

void dfs(int here, int color){
    visited[here] = true;
    check[here] = color;
    for(int next : adj[here]){
        if(!visited[next]){
            dfs(next,(color == 1 ? 2 : 1));
        }
    }
}
int main(){
    int test;
    cin >> test;
    while(test--){
        int v,e;
        cin >> v >> e;

        adj = vector<vector<int>>(v);
        int x,y;
        for(int i = 0; i < e; ++i){
            cin >> x >> y;
            adj[x-1].push_back(y-1);
            adj[y-1].push_back(x-1);
        }

        visited = vector<bool>(v,false);
        check = vector<int>(v,0);

        for(int i = 0; i < v; ++i){
            if(!visited[i]) dfs(i,1);
        }

        bool ans = true;
        for(int i = 0; i < v; ++i){
            for(int next : adj[i]){
                if(check[i] == check[next]) ans = false;
            }
        }
        if(ans) cout << "YES\n";
        else cout << "NO\n";
    }
}

