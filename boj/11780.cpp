//
// Created by jaewon on 2017-07-17.
//
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

const int INF = 1e9;

vector<vector<int>> dist;
vector<vector<int>> parent;

void print(int start, int end, vector<int>& path){
    if(parent[start][end] == -1){
        path.push_back(start);
        if(start != end)
            path.push_back(end);
    }else{
        print(start,parent[start][end],path);
        path.pop_back();
        print(parent[start][end],end,path);
    }
}

int main(){
    freopen("input.txt","r",stdin);
    int n,m;
    cin >> n >> m;

    dist.assign(n,vector<int>(n,INF));
    parent.assign(n,vector<int>(n,-1));

    for(int i = 0; i < n; ++i) dist[i][i] = 0;

    int u,v,w;
    for(int i = 0; i < m; ++i){
        cin >> u >> v >> w;
        if(dist[u-1][v-1] > w){
            dist[u-1][v-1] = w;
        }
    }


    for(int k = 0; k < n; ++k){
        for(int i = 0; i < n; ++i){
            for(int j = 0; j < n; ++j){
                if(dist[i][j] > dist[i][k] + dist[k][j]){
                    dist[i][j] = dist[i][k] + dist[k][j];
                    parent[i][j] = k;
                }
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

    vector<int> path;
    for(int i = 0; i < n; ++i){
        for(int j = 0; j < n; ++j){
            if(i == j){
                cout << "0";
            }else{
                print(i,j,path);
                cout << path.size() << " ";
                for(int k = 0; k < path.size(); ++k) cout << path[k] + 1 << " ";
                path.clear();
            }
            cout << endl;
        }
    }
}