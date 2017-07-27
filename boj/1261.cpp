//
// Created by jaewon on 2017-07-10.
//
#include <iostream>
#include <queue>
#include <vector>
#include <algorithm>
using namespace std;

const int dr[4] = {-1,0,1,0};
const int dc[4] = {0,1,0,-1};
const int INF = 2e9;

int main(){
    freopen("input.txt","r",stdin);
    ios_base::sync_with_stdio(false);
    int n,m;
    cin >> m >> n;

    vector<vector<char>> adj(n,vector<char>(m));
    for(int i = 0; i < n; ++i){
        for(int j = 0; j < m; ++j){
            cin >> adj[i][j];
        }
    }

    vector<vector<int>> dist(n,vector<int>(m,INF));
    priority_queue<pair<int,pair<int,int>>> pq;
    pq.push({0,{0,0}});
    dist[0][0] = 0;
    while(!pq.empty()){
        int row = pq.top().second.first;
        int col = pq.top().second.second;
        int cost = -pq.top().first;
        pq.pop();

        if(dist[row][col] < cost) continue;

        for(int i = 0; i < 4; ++i){
            int nextRow = row + dr[i];
            int nextCol = col + dc[i];
            if(nextRow < 0 || nextRow >= n || nextCol < 0 || nextCol >= m) continue;
            if(adj[nextRow][nextCol] == '1'){
                if(dist[nextRow][nextCol] > dist[row][col] + 1){
                    dist[nextRow][nextCol] = dist[row][col] + 1;
                    pq.push({-dist[nextRow][nextCol],{nextRow,nextCol}});
                }
            }else{
                if(dist[nextRow][nextCol] > dist[row][col]){
                    dist[nextRow][nextCol] = dist[row][col];
                    pq.push({-dist[nextRow][nextCol],{nextRow,nextCol}});
                }
            }
        }
    }

    cout << dist[n-1][m-1];
}
