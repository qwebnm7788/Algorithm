//
// Created by jaewon on 2017-07-11.
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

        if(dist[here] < cost) continue;

        for(auto& edge : adj[here]){
            int next = edge.first;
            int nextCost = edge.second;
            if(dist[next] > dist[here] + nextCost){
                dist[next] = dist[here] + nextCost;
                parent[next] = here;
                pq.push({-dist[next],next});
            }
        }
    }

    int original = dist[n-1];

    vector<pair<int,int>> usedPath;
    for(int i = n-1; i != 0; i = parent[i]){
        usedPath.push_back({parent[i],i});
    }

    int numOfPossible = usedPath.size();
    int ans = 0;
    for(int i = 0; i < numOfPossible; ++i){
        dist.assign(n,INF);
        dist[0] = 0;
        pq.push({0,0});
        while(!pq.empty()){
            int here = pq.top().second;
            int cost = -pq.top().first;
            pq.pop();

            if(dist[here] < cost) continue;

            for(auto& edge : adj[here]){
                int next = edge.first;
                int nextCost = edge.second;
                if((here == usedPath[i].first && next == usedPath[i].second) || (here == usedPath[i].second && next == usedPath[i].first)) continue;
                if(dist[next] > dist[here] + nextCost){
                    dist[next] = dist[here] + nextCost;
                    pq.push({-dist[next],next});
                }
            }
        }

        ans = max(ans, dist[n-1]);
    }

    if(ans == INF) cout << "-1";
    else cout << ans - original;
}
