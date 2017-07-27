//
// Created by jaewon on 2017-07-19.
//
#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
using namespace std;

const int INF = 2e9;

int main(){
    freopen("input.txt","r",stdin);
    ios_base::sync_with_stdio(false);
    int n,m;
    cin >> n >> m;

    vector<vector<pair<int,int>>> adj(n);
    int u,v,w;
    for(int i = 0; i < m; ++i){
        cin >> u >> v >> w;
        adj[u-1].push_back({v-1,w});
        adj[v-1].push_back({u-1,w});
    }

    vector<int> parent(n,-1);
    vector<int> dist(n,INF);
    priority_queue<pair<int,int>> pq;
    dist[0] = 0;
    pq.push({0,0});
    while(!pq.empty()){
        int here = pq.top().second;
        int cost = -pq.top().first;
        pq.pop();

        if(dist[here] > cost) continue;

        for(auto& edge : adj[here]){
            int next = edge.first;
            int nextCost = edge.second;
            if(dist[next] > cost + nextCost){
                dist[next] = cost + nextCost;
                parent[next] = here;
                pq.push({-dist[next],next});
            }
        }
    }
    vector<pair<int,int>> path;
    for(int i = n-1; i != -1; i = parent[i]){
        path.push_back({parent[i],i});
    }

    int size = path.size();
    int answer = -1;

    for(int i = 0; i < size; ++i){
        dist.assign(n,INF);
        dist[0] = 0;
        pq.push({0,0});
        while(!pq.empty()){
            int here = pq.top().second;
            int cost = -pq.top().first;
            pq.pop();

            if(dist[here] > cost) continue;

            for(auto& edge : adj[here]){
                int next = edge.first;
                int nextCost = edge.second;
                if((here == path[i].first && next == path[i].second) || (here == path[i].second && next == path[i].first)) continue;
                if(dist[next] > cost + nextCost){
                    dist[next] = cost + nextCost;
                    pq.push({-dist[next],next});
                }
            }
        }
        if(dist[n-1] != INF)
            answer = max(answer,dist[n-1]);
    }
    cout << answer;
}
