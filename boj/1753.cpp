//
// Created by jaewon on 2017-07-10.
//
#include <iostream>
#include <queue>
#include <algorithm>
#include <vector>
using namespace std;

const int INF = 2e9;

int main(){
    freopen("input.txt","r",stdin);
    ios_base::sync_with_stdio(false);
    int v,e;
    cin >> v >> e;

    int start;
    cin >> start;

    vector<vector<pair<int,int>>> adj(v);
    int a,b,c;
    for(int i = 0; i < e; ++i){
        cin >> a >> b >> c;
        adj[a-1].push_back({b-1,c});
    }

    vector<int> dist(v,INF);
    priority_queue<pair<int,int>> pq;
    dist[start-1] = 0;
    pq.push({-dist[start-1],start-1});

    while(!pq.empty()){
        int here = pq.top().second;
        int cost = -pq.top().first;
        pq.pop();

        if(cost > dist[here]) continue;

        for(auto& edge : adj[here]){
            int next = edge.first;
            int nextCost = edge.second;
            if(dist[next] > dist[here] + nextCost){
                dist[next] = dist[here] + nextCost;
                pq.push({-dist[next],next});
            }
        }
    }

    for(int i = 0; i < v; ++i){
        if(dist[i] == INF) cout << "INF\n";
        else cout << dist[i] << endl;
    }
}
