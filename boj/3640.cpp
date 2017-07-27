#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
using namespace std;

const int INF = 2e9;

int main(){
    freopen("input.txt","r",stdin);
    ios_base::sync_with_stdio(false);
    int v,e;
    cin >> v >> e;

    vector<vector<pair<int,int>>> adj(v);
    int a,b,c;
    for(int i = 0; i < e; ++i){
        cin >> a >> b >> c;
        adj[a-1].push_back({b-1,c});
    }

    vector<int> dist(v,INF), parent(v,-1);
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
            if(dist[next] > cost + nextCost){
                dist[next] = cost + nextCost;
                parent[next] = here;
                pq.push({-dist[next],next});
            }
        }
    }

    cout << dist[v-1] << endl;

    vector<bool> check(v,false);
    for(int i = v-1; i != -1; i = parent[i]){
        check[i] = true;
        for(int j = 0; j < adj[parent[i]].size(); ++j){
            if(adj[parent[i]][j].first == i){
                adj[parent[i]][j].second = INF;
                break;
            }
        }
    }

    check[0] = check[v-1] = false;

    dist.assign(v,INF);
    dist[0] = 0;
    pq.push({0,0});
    while(!pq.empty()){
        int here = pq.top().second;
        int cost = -pq.top().first;
        pq.pop();

        if(dist[here] < cost || check[here]) continue;

        for(auto& edge : adj[here]){
            int next = edge.first;
            int nextCost = edge.second;
            if(check[next]) continue;
            if(dist[next] > cost + nextCost){
                dist[next] = cost + nextCost;
                pq.push({-dist[next],next});
            }
        }
    }

    cout << dist[v-1];
}