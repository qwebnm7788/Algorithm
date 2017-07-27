//
// Created by jaewon on 2017-07-02.
//
#include <iostream>
#include <vector>
#include <queue>
using namespace std;

const int dr[4] = {-1,0,1,0};
const int dc[4] = {0,1,0,-1};

int main(){
    freopen("input.txt","r",stdin);
    int n,m;
    cin >> n >> m;

    vector<vector<char>> adj(n,vector<char>(m));
    vector<vector<vector<bool>>> visited(n,vector<vector<bool>>(m,vector<bool>(2,false)));
    for(int i = 0; i < n; ++i){
        for(int j = 0; j < m; ++j){
            cin >> adj[i][j];
        }
    }
    queue<pair<pair<int,int>,int>> q;
    q.push({{0,0},0});
    visited[0][0][0] = true;
    int size, level = 1;
    bool found = false;
    while(!q.empty()){
        size = q.size();
        for(int i = 0; i < size; ++i){
            int row = q.front().first.first;
            int col = q.front().first.second;
            int fortune = q.front().second;
            q.pop();
            if(row == n-1 && col == m-1){
                found = true;
                break;
            }
            for(int j = 0; j < 4; ++j){
                int nextRow = row + dr[j];
                int nextCol = col + dc[j];
                if(nextRow < 0 || nextRow >= n || nextCol < 0 || nextCol >= m) continue;
                if(!visited[nextRow][nextCol][fortune]){
                    if(adj[nextRow][nextCol] == '0'){
                        visited[nextRow][nextCol][fortune] = true;
                        q.push({{nextRow,nextCol},fortune});
                    }else if(fortune == 0){
                        visited[nextRow][nextCol][fortune+1] = true;
                        q.push({{nextRow,nextCol},fortune+1});
                    }
                }
            }
        }
        if(found) break;
        level++;
    }
    if(found)
        cout << level;
    else
        cout << "-1";
}
