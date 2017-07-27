//
// Created by jaewon on 2017-06-21.
//
#include <iostream>
#include <queue>
#include <vector>
#include <algorithm>
using namespace std;

const int INF = 2e9;

int n,e;
vector<vector<pair<int,int>>> adj;

//start -> target's shortest path
//return INF if there's no path
int dijkstra(int start, int target){
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
    return dist[target];
}

int main() {
    ios_base::sync_with_stdio(false);
    freopen("input.txt", "r", stdin);
    cin >> n >> e;

    adj.resize(n);

    int u, v, w;
    for (int i = 0; i < e; ++i) {
        cin >> u >> v >> w;
        adj[u - 1].push_back({v - 1, w});
        adj[v - 1].push_back({u - 1, w});
    }

    int a, b;
    cin >> a >> b;

    int ans;
    int x, y, z;
    x = dijkstra(0, a - 1);
    y = dijkstra(a - 1, b - 1);
    z = dijkstra(b - 1, n - 1);
    if (x == INF || y == INF || z == INF) ans = INF;
    else ans = x + y + z;

    x = dijkstra(0, b - 1);
    y = dijkstra(b - 1, a - 1);
    z = dijkstra(a - 1, n - 1);
    if (x == INF || y == INF || z == INF) ans = min(ans, INF);
    else ans = min(ans, x + y + z);

    if(ans == INF) cout << "-1";
    else cout << ans;
}