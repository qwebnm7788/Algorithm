//
// Created by jaewon on 2017-06-27.
//
#include <iostream>
#include <queue>
#include <cstring>
#include <algorithm>
using namespace std;

const int MAXL = 301;
const int INF = 2e9;

const int dr[8] = {-1,-2,-2,-1,1,2,2,1};
const int dc[8] = {-2,-1,1,2,2,1,-1,-2};

bool visited[MAXL][MAXL];
int l,sr,sc,tr,tc;

int main(){
    freopen("input.txt","r",stdin);
    ios_base::sync_with_stdio(false);
    int test;
    cin >> test;
    while(test--){
        cin >> l >> sr >> sc >> tr >> tc;
        memset(visited,0,sizeof(visited));
        queue<pair<int,int>> q;
        q.push({sr,sc});
        visited[sr][sc] = true;
        int size, level = 0;
        bool finish = false;
        while(!q.empty()){
            size = q.size();
            for(int i = 0; i < size; ++i){
                int row = q.front().first;
                int col = q.front().second;
                q.pop();
                if(row == tr && col == tc){
                    finish = true;
                    break;
                }
                for(int j = 0; j < 8; ++j) {
                    int nextRow = row + dr[j];
                    int nextCol = col + dc[j];
                    if(nextRow < 0 || nextRow >= l || nextCol < 0 || nextCol >= l) continue;
                    if(!visited[nextRow][nextCol]){
                        visited[nextRow][nextCol] = true;
                        q.push({nextRow,nextCol});
                    }
                }
            }
            if(finish) break;
            level++;
        }
        cout << level << endl;
    }
}
