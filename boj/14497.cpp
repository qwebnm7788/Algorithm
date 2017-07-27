//
// Created by jaewon on 2017-07-19.
//
#include <iostream>
#include <vector>
using namespace std;

const int dr[4] = {-1,0,1,0};
const int dc[4] = {0,1,0,-1};

vector<vector<char>> adj;
vector<vector<bool>> visited;
int n,m;

bool dfs(int row, int col){
    bool ret = false;
    visited[row][col] = true;
    for(int i = 0; i < 4; ++i) {
        int nextRow = row + dr[i];
        int nextCol = col + dc[i];
        if(nextRow < 0 || nextRow >= n || nextCol < 0 || nextCol >= m || visited[nextRow][nextCol]) continue;
        if(adj[nextRow][nextCol] == '1'){
            visited[nextRow][nextCol] = true;
            adj[nextRow][nextCol] = '0';
        }else if(adj[nextRow][nextCol] == '#'){
            ret = true;
        }else{
            ret |= dfs(nextRow,nextCol);
        }
    }
    return ret;
}

int main(){
    ios_base::sync_with_stdio(false);
    freopen("input.txt","r",stdin);
    int x1,x2,y1,y2;
    cin >> n >> m;
    cin >> x1 >> y1 >> x2 >> y2;

    adj.assign(n,vector<char>(m));
    visited.assign(n,vector<bool>(m,false));
    for(int i = 0; i < n; ++i){
        for(int j = 0; j < m; ++j){
            cin >> adj[i][j];
        }
    }
    int answer = 0;

    if(x1 == x2 && y1 == y2){
        cout << "0";
    }else{
        while(!dfs(x1-1,y1-1)){
            visited.assign(n,vector<bool>(m,false));
            answer++;
        }
        cout << answer + 1;
    }
}


