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

    int u,v,b;
    for(int i = 0; i < m; ++i){
        cin >> u >> v >> b;
        if(b){
            dist[u-1][v-1] = dist[v-1][u-1] = 0;
        }else{
            dist[u-1][v-1] = 0;
            dist[v-1][u-1] = 1;
        }
    }

    for(int i = 0; i < n; ++i) dist[i][i] = 0;

    for(int k = 0; k < n; ++k){
        for(int i = 0; i < n; ++i){
            for(int j = 0; j < n; ++j){
                dist[i][j] = min(dist[i][j],dist[i][k] + dist[k][j]);
            }
        }
    }
    int k;
    cin >> k;

    int s,e;
    for(int i = 0; i < k; ++i){
        cin >> s >> e;
        cout << dist[s-1][e-1] << endl;
    }
}