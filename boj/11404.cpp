//
// Created by jaewon on 2017-07-17.
//
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

const int INF = 1e9;

int main(){
    ios_base::sync_with_stdio(false);
    freopen("input.txt","r",stdin);
    int n,m;
    cin >> n >> m;

    vector<vector<int>> dist(n,vector<int>(n,INF));

    int u,v,w;
    for(int i = 0; i < m; ++i){
        cin >> u >> v >> w;
        dist[u-1][v-1] = min(dist[u-1][v-1],w);
    }

    for(int i = 0; i < n; ++i) dist[i][i] = 0;

    for(int k = 0; k < n; ++k){
        for(int i = 0; i < n; ++i){
            for(int j = 0; j < n; ++j){
                dist[i][j] = min(dist[i][j],dist[i][k] + dist[k][j]);
            }
        }
    }

    for(int i = 0; i < n; ++i){
        for(int j = 0; j < n; ++j){
            if(dist[i][j] == INF) cout << "0 ";
            else cout << dist[i][j] << " ";
        }
        cout << endl;
    }
}
