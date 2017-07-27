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
    int test;
    cin >> test;
    while(test--){
        int n,m,t,s,g,h;
        cin >> n >> m >> t >> s >> g >> h;
        s--, g--, h--;

        vector<vector<pair<int,int>>> adj(n);
        int a,b,d;
        for(int i = 0; i < m; ++i){
            cin >> a >> b >> d;
            adj[a-1].push_back({b-1,d});
            adj[b-1].push_back({a-1,d});
        }

        vector<int> target(t);
        for(int i = 0; i < t; ++i){
            cin >> target[i];
            target[i]--;
        }

        sort(target.begin(),target.end());

        vector<vector<int>> dist(n,vector<int>(2,INF));
        priority_queue<pair<int,pair<int,int>>> pq;
        dist[s][0] = 0;
        pq.push({0,{s,0}});
        while(!pq.empty()){
            int here = pq.top().second.first;
            int pass = pq.top().second.second;
            int cost = -pq.top().first;
            pq.pop();

            if(dist[here][pass] > cost) continue;

            for(auto& edge : adj[here]){
                int next = edge.first;
                int nextCost = edge.second;

                if(pass == 0){
                    if((here == g && next == h) || (here == h && next == g)){
                        if(dist[next][pass+1] > dist[here][pass] + nextCost){
                            dist[next][pass+1] = dist[here][pass] + nextCost;
                            pq.push({-dist[next][pass+1],{next,pass+1}});
                        }
                    }
                }
                if(dist[next][pass] > dist[here][pass] + nextCost){
                    dist[next][pass] = dist[here][pass] + nextCost;
                    pq.push({-dist[next][pass],{next,pass}});
                }
            }
        }
        for(int i = 0; i < t; ++i){
            if(dist[target[i]][1] != INF){
                if(dist[target[i]][0] == INF || dist[target[i]][0] >= dist[target[i]][1]) cout << target[i] + 1 << " ";
            }
        }
        cout << endl;
    }
}
