//
// Created by jaewon on 2017-07-11.
//
#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
using namespace std;

const int INF = 2e9;

int main(){
    freopen("input.txt","r",stdin);
    ios_base::sync_with_stdio(false);
    int n,m,k;
    cin >> n >> m >> k;

    vector<vector<pair<int,int>>> adj(n);

    int u,v,w;
    for(int i = 0; i < m; ++i){
        cin >> u >> v >> w;
        adj[u-1].push_back({v-1,w});
        adj[v-1].push_back({u-1,w});
    }

    vector<vector<int>> dist(n,vector<int>(k+1,INF));
    priority_queue<pair<int,pair<int,int>>> pq;
    dist[0][0] = 0;
    pq.push({0,{0,0}});
    while(!pq.empty()){
        int here = pq.top().second.first;
        int cnt = pq.top().second.second;
        int cost = -pq.top().first;
        pq.pop();

        if(dist[here][cnt] < cost) continue;

        for(auto& edge : adj[here]){
            int next = edge.first;
            int nextCost = edge.second;

            if(dist[next][cnt] > dist[here][cnt] + nextCost){
                dist[next][cnt] = dist[here][cnt] + nextCost;
                pq.push({-dist[next][cnt],{next,cnt}});
            }

            if(cnt < k){
                if(dist[next][cnt+1] > dist[here][cnt]){
                    dist[next][cnt+1] = dist[here][cnt];
                    pq.push({-dist[next][cnt+1],{next,cnt+1}});
                }
            }
        }
    }

    int ans = INF;
    for(int i = 0; i <= k; ++i){
        ans = min(ans,dist[n-1][i]);
    }
    cout << ans;
}
