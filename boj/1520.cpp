//
// Created by jaewon on 2017-06-29.
//
#include <iostream>
#include <cstring>
#include <algorithm>
using namespace std;

const int MAXN = 501;
const int MAXM = 501;
const int dr[4] = {-1,0,1,0};
const int dc[4] = {0,1,0,-1};

int adj[MAXM][MAXN];
long long cache[MAXM][MAXN];
int m,n;

long long foo(int row, int col){
    if(row == m-1 && col == n-1) return 1;
    long long& ret = cache[row][col];
    if(ret != -1) return ret;
    ret = 0;
    for(int i = 0; i < 4; ++i){
        int nextRow = row + dr[i];
        int nextCol = col + dc[i];
        if(nextRow < 0 || nextRow >= m || nextCol < 0 || nextCol >= n) continue;
        if(adj[nextRow][nextCol] < adj[row][col])
            ret += foo(nextRow,nextCol);
    }
    return ret;
}

int main(){
    freopen("input.txt","r",stdin);
    cin >> m >> n;
    for(int i = 0; i < m; ++i){
        for(int j = 0; j < n; ++j){
            cin >> adj[i][j];
        }
    }
    memset(cache,-1,sizeof(cache));
    cout << foo(0,0);
}
