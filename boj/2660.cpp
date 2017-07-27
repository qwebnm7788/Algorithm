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
    int n;
    cin >> n;

    vector<vector<int>> dist(n,vector<int>(n,INF));

    int u,v;
    while(cin >> u >> v){
        if(u == -1 && v == -1) break;
        dist[u-1][v-1] = dist[v-1][u-1] = 1;
    }

    for(int i = 0; i < n; ++i) dist[i][i] = INF;

    for(int k = 0; k < n; ++k) {
        for(int i = 0; i < n; ++i){
            for(int j = 0; j < n; ++j){
                dist[i][j] = min(dist[i][j], dist[i][k] + dist[k][j]);
            }
        }
    }

    vector<int> ans;
    int temp = 0, ansVal = INF;
    for(int i = 0; i < n; ++i){
        temp = 0;
        for(int j = 0; j < n; ++j){
            if(i == j) continue;
            if(dist[i][j] == INF){
                temp = INF;
                break;
            }
            temp = max(temp,dist[i][j]);
        }
        if(temp < ansVal){
            ans.clear();
            ans.push_back(i);
            ansVal = temp;
        }else if(temp == ansVal){
            ans.push_back(i);
        }
    }

    cout << ansVal << " " << ans.size() << endl;
    for(int i = 0; i < ans.size(); ++i) cout << ans[i] + 1 << " ";
}
