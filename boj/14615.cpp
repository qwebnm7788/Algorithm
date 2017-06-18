//
// Created by jaewon on 2017-06-15.
//
#include <cstdio>
#include <vector>
#include <algorithm>
using namespace std;

void dfs(vector<bool>& visited, vector<vector<int>>& adj, int here){
    visited[here] = true;
    for(int next : adj[here]){
        if(!visited[next]) dfs(visited, adj, next);
    }
}


int main(){
    freopen("input.txt","r",stdin);
    int n,m;
    scanf("%d %d", &n, &m);

    vector<vector<int>> adj(n);
    vector<vector<int>> rAdj(n);
    vector<bool> visited(n,false);
    vector<bool> rVisited(n,false);

    int x,y;
    for(int i = 0; i < m; ++i){
        scanf("%d %d", &x, &y);
        adj[x-1].push_back(y-1);
        rAdj[y-1].push_back(x-1);
    }

    dfs(visited,adj,0);
    dfs(rVisited,rAdj,n-1);

    int t,in;
    scanf("%d", &t);
    for(int i = 0; i < t; ++i){
        scanf("%d", &in);
        in--;
        if(visited[in] && rVisited[in]) printf("Defend the CTP\n");
        else printf("Destroyed the CTP\n");
    }
}

