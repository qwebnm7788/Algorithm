//
// Created by jaewon on 2017-07-10.
//
#include <iostream>
#include <string>
#include <queue>
#include <algorithm>
#include <vector>
using namespace std;

const int INF = 2e9;

int main(){
    freopen("input.txt","r",stdin);
    ios_base::sync_with_stdio(false);
    int n;
    cin >> n;

    string road;
    cin >> road;

    vector<vector<pair<int,int>>> adj(n);
    for(int i = 0; i < n; ++i){
        for(int j = i + 1; j < n; ++j){
            if(road[i] == 'B' && road[j] == 'O'){
                adj[i].push_back({j,(j-i)*(j-i)});
            }else if(road[i] == 'O' && road[j] == 'J'){
                adj[i].push_back({j,(j-i)*(j-i)});
            }else if(road[i] == 'J' && road[j] == 'B'){
                adj[i].push_back({j,(j-i)*(j-i)});
            }
        }
    }

    vector<int> dist(n,INF);
    priority_queue<pair<int,int>> pq;
    dist[0] = 0;
    pq.push({0,0});
    while(!pq.empty()){
        int here = pq.top().second;
        int cost = -pq.top().first;
        pq.pop();

        if(here == n-1) break;
        if(dist[here] < cost) continue;

        for(auto& edge : adj[here]){
            int next = edge.first;
            int nextCost = edge.second;
            if(dist[next] > dist[here] + nextCost){
                dist[next] = dist[here] + nextCost;
                pq.push({-dist[next],next});
            }
        }
    }

    if(dist[n-1] == INF) cout << "-1";
    else cout << dist[n-1];
}
