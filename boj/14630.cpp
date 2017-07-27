//
// Created by jaewon on 2017-06-23.
//
#include <iostream>
#include <queue>
#include <vector>
#include <string>
#include <cmath>
#include <algorithm>
using namespace std;

const int INF = 2e9;

int main(){
    ios_base::sync_with_stdio(false);
    freopen("input.txt","r",stdin);
    int n;
    cin >> n;

    vector<string> in(n);
    for(int i = 0; i < n; ++i) cin >> in[i];

    int len = in[0].length();

    vector<vector<int>> cost(n,vector<int>(n,0));
    for(int i = 0; i < n; ++i){
        for(int j = 0; j < n; ++j){
            if(i == j) continue;
            for(int k = 0; k < len; ++k) {
                cost[i][j] += pow((in[i][k] - '0') - (in[j][k] - '0'), 2);
            }
        }
    }
    vector<vector<pair<int,int>>> adj(n);
    for(int i = 0; i < n; ++i){
        for(int j = 0; j < n; ++j){
            if(i == j) continue;
            adj[i].push_back({j,cost[i][j]});
            adj[j].push_back({i,cost[j][i]});
        }
    }

    int start, end;
    cin >> start >> end;
    start--, end--;

    priority_queue<pair<int,int>> pq;
    vector<int> dist(n,INF);
    dist[start] = 0;
    pq.push({-dist[start],start});
    while(!pq.empty()){
        int here = pq.top().second;
        int cost = -pq.top().first;
        pq.pop();

        if(dist[here] < cost) continue;

        for(auto& edge : adj[here]){
            int next = edge.first;
            int nextCost = edge.second;
            if(dist[next] > cost + nextCost){
                dist[next] = cost + nextCost;
                pq.push({-dist[next],next});
            }
        }
    }

    cout << dist[end];
}