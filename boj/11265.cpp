//
// Created by jaewon on 2017-07-17.
//
#include <iostream>
#include <vector>
#include <algorithm>
#include <climits>
using namespace std;

const long long INF = numeric_limits<long long>::max() / 2;

int main(){
    freopen("input.txt","r",stdin);
    ios_base::sync_with_stdio(false);
    int n,m;
    cin >> n >> m;

    vector<vector<long long>> dist(n,vector<long long>(n,INF));

    for(int i = 0; i < n; ++i){
        for(int j = 0; j < n; ++j){
            cin >> dist[i][j];
        }
    }

    for(int k = 0; k < n; ++k){
        for(int i = 0; i < n; ++i){
            for(int j = 0; j < n; ++j){
                dist[i][j] = min(dist[i][j],dist[i][k] + dist[k][j]);
            }
        }
    }

    int a,b,c;
    for(int i = 0; i < m; ++i){
        cin >> a >> b >> c;
        if(dist[a-1][b-1] <= c){
            cout << "Enjoy other party\n";
        }else{
            cout << "Stay here\n";
        }
    }
}
