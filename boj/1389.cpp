//
// Created by jaewon on 2017-07-02.
//
#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;

const int INF = 1e9;

int main(){
    freopen("input.txt","r",stdin);
    int n,m;
    cin >> n >> m;

    vector<vector<int>> dist(n,vector<int>(n,INF));
    int u,v;
    for(int i = 0; i < m; ++i){
        cin >> u >> v;
        dist[u-1][v-1] = dist[v-1][u-1] = 1;
    }

    for(int k = 0; k < n; ++k){
        for(int i = 0; i < n; ++i){
            for(int j = 0; j < n; ++j){
                if(dist[i][j] > dist[i][k] + dist[k][j]){
                    dist[i][j] = dist[i][k] + dist[k][j];
                }
            }
        }
    }

    int minVal = INF, temp, ans;
    for(int i = 0; i < n; ++i){
        temp = 0;
        for(int j = 0;j < n; ++j){
            if(i == j) continue;
            temp += dist[i][j];
        }
        if(minVal > temp){
            minVal = temp;
            ans = i + 1;
        }
    }
    cout << ans;
}
