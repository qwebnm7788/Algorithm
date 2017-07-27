//
// Created by jaewon on 2017-07-19.
//
#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
using namespace std;

int main(){
    freopen("input.txt","r",stdin);
    ios_base::sync_with_stdio(false);
    int start, end;
    cin >> start >> end;
    start--,end--;

    int n,m;
    cin >> n >> m;

    vector<vector<int>> adj(n);
    int u,v;
    for(int i = 0; i < m; ++i){
        cin >> u >> v;
        adj[u-1].push_back(v-1);
        adj[v-1].push_back(u-1);
    }

    queue<int> q;
    vector<int> dist(n, -1);
    vector<bool> visited(n,false);
    visited[start] = true;
    dist[start] = 0;
    q.push(start);

    while(!q.empty()){
        int here = q.front();
        q.pop();
        for(int next : adj[here]){
            if(!visited[next]){
                dist[next] = dist[here] + 1;
                visited[next] = true;
                q.push(next);
            }
        }
    }

    if(visited[end]) cout << dist[end];
    else cout << "-1";
}
