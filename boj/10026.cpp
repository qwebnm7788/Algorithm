//
// Created by jaewon on 2017-06-29.
//
#include <iostream>
#include <cstring>
using namespace std;

const int MAXN = 101;
const int dr[4] = {-1,0,1,0};
const int dc[4] = {0,1,0,-1};

int n;
int visited[MAXN][MAXN];
char ma[MAXN][MAXN];

void dfs(int row, int col){
    visited[row][col] = 1;
    for(int i = 0; i < 4; ++i){
        int nextRow = row + dr[i];
        int nextCol = col + dc[i];
        if(nextRow < 0 || nextRow >= n || nextCol < 0 || nextCol >= n) continue;
        if((visited[nextRow][nextCol] == 0) && (ma[nextRow][nextCol] == ma[row][col]))
            dfs(nextRow,nextCol);
    }
}

int main(){
    freopen("input.txt","r",stdin);
    cin >> n;
    for(int i = 0; i < n; ++i){
        for(int j = 0; j < n; ++j){
            cin >> ma[i][j];
        }
    }

    int x = 0, y = 0;
    memset(visited,0,sizeof(visited));
    for(int i = 0; i < n; ++i){
        for(int j = 0; j < n; ++j){
            if(!visited[i][j]){
                x++;
                dfs(i,j);
            }
        }
    }

    for(int i = 0; i < n; ++i){
        for(int j = 0; j < n; ++j){
            if(ma[i][j] == 'R') ma[i][j] = 'G';
        }
    }
    memset(visited,0,sizeof(visited));
    for(int i = 0; i < n; ++i){
        for(int j = 0; j < n; ++j){
            if(!visited[i][j]){
                y++;
                dfs(i,j);
            }
        }
    }
    cout << x << " " << y;
}