//
// Created by jaewon on 2017-07-02.
//
#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
using namespace std;

const int INF = 2e9;
const int MAXN = 100005;

int main(){
    int n,k;
    cin >> n >> k;

    vector<bool> visited(MAXN,false);
    queue<int> q;
    q.push(n);
    visited[n] = true;
    int size, level = 0;
    bool found = false;
    while(!q.empty()){
        size = q.size();
        for(int i = 0; i < size; ++i){
            int here = q.front();
            q.pop();
            if(here == k){
                found = true;
                break;
            }
            if(here + 1 < MAXN && !visited[here+1]){
                visited[here+1] = true;
                q.push(here+1);
            }
            if(here - 1 >= 0 && !visited[here-1]){
                visited[here-1] = true;
                q.push(here-1);
            }
            if(here*2 < MAXN && !visited[here*2]){
                visited[here*2] = true;
                q.push(here*2);
            }
        }
        if(found) break;
        level++;
    }
    cout << level;
}
