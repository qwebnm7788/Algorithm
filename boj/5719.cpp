//
// Created by jaewon on 2017-07-11.
//
#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
using namespace std;

//처음 다익스트라로 최단거리를 구하고
//bfs로 탐색하며 dist[next] == dist[here] + cost[here][next] 라면 최단경로에 속하는 친구이므로
//이 경로는 삭제되어야 한다. 이러한 경로를 모두 수집해놓고
//이 친구들을 모두 지워준 다음에 다익스트라를 다시한번 돌려주면 된당

const int INF = 2e9;

int main(){
    freopen("input.txt","r",stdin);
    freopen("output.txt","w",stdout);
    ios_base::sync_with_stdio(false);
    while(true){
        int n,m;
        cin >> n >> m;
        if(n == 0 && m == 0) break;

        int start, end;
        cin >> start >> end;

        vector<vector<pair<int,int>>> adj(n);

        int u,v,p;
        for(int i = 0; i < m; ++i){
            cin >> u >> v >> p;
            adj[u].push_back({v,p});
        }

        vector<vector<int>> parent(n);
        vector<int> dist(n,INF);
        priority_queue<pair<int,int>> pq;
        dist[start] = 0;
        pq.push({0,start});
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
                    parent[next].clear();
                    parent[next].push_back(here);
                    pq.push({-dist[next],next});
                }else if(dist[next] == dist[here] + nextCost){
                    parent[next].push_back(here);
                }
            }
        }

        int shortest = dist[end];

        vector<vector<bool>> isDeleted(n,vector<bool>(n,false));
        queue<int> q;
        q.push(end);
        while(!q.empty()){
            int here = q.front();
            q.pop();
            if(here == start) continue;
            for(int before : parent[here]){
                isDeleted[before][here] = true;
                q.push(before);
            }
        }

        dist.assign(n,INF);
        dist[start] = 0;
        pq.push({0,start});
        while(!pq.empty()){
            int here = pq.top().second;
            int cost = -pq.top().first;
            pq.pop();

            if(dist[here] < cost) continue;

            for(auto& edge : adj[here]){
                int next = edge.first;
                int nextCost = edge.second;

                if(isDeleted[here][next]) continue;

                if(dist[next] > dist[here] + nextCost){
                    dist[next] = dist[here] + nextCost;
                    pq.push({-dist[next],next});
                }
            }
        }

        if(dist[start] == INF || dist[end] == INF) cout << "-1\n";
        else cout << dist[end] << endl;
    }
}
