//
// Created by jaewon on 2017-07-10.
//
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <queue>
using namespace std;

const int INF = 2e9;

int calc(const string& a, const string& b){
    int ret = 0, len = a.length();
    for(int i = 0; i < len; ++i){
        ret += (a[i]-b[i])*(a[i]-b[i]);
    }
    return ret;
}

int main(){
    freopen("input.txt","r",stdin);
    ios_base::sync_with_stdio(false);
    int n;
    cin >> n;

    vector<string> robot(n);
    for(int i = 0; i < n; ++i) cin >> robot[i];

    int start, end;
    cin >> start >> end;
    start--, end--;

    vector<vector<pair<int,int>>> adj(n);
    for(int i = 0; i < n; ++i){
        for(int j = 0; j < n; ++j){
            if(i == j) continue;
            int cost = calc(robot[i],robot[j]);
            adj[i].push_back({j,cost});
            adj[j].push_back({i,cost});
        }
    }

    vector<int> dist(n,INF);
    priority_queue<pair<int,int>> pq;
    dist[start] = 0;
    pq.push({0,start});
    while(!pq.empty()){
        int here = pq.top().second;
        int cost = -pq.top().first;
        pq.pop();

        if(here == end) break;
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
    cout << dist[end];
}
