//
// Created by jaewon on 2017-07-10.
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
    int n,k;
    cin >> n >> k;

    int maxLen = max(n,k) + 5;

    vector<int> dist(maxLen,INF);
    vector<int> parent(maxLen,-1);

    priority_queue<pair<int,int>> pq;
    dist[n] = 0;
    pq.push({0,n});
    while(!pq.empty()){
        int here = pq.top().second;
        int cost = -pq.top().first;
        pq.pop();

        if(dist[here] < cost) continue;

        if(here >= 1){
            if(dist[here-1] > dist[here] + 1){
                dist[here-1] = dist[here] + 1;
                parent[here-1] = here;
                pq.push({-dist[here-1],here-1});
            }
        }
        if(here + 1 < maxLen){
            if(dist[here+1] > dist[here] + 1){
                dist[here+1] = dist[here] + 1;
                parent[here+1] = here;
                pq.push({-dist[here+1],here+1});
            }
        }
        if(here*2 < maxLen){
            if(dist[here*2] > dist[here] + 1){
                dist[here*2] = dist[here] + 1;
                parent[here*2] = here;
                pq.push({-dist[here*2],here*2});
            }
        }
    }

    cout << dist[k] << endl;

    vector<int> ans;
    for(int i = k; i != -1; i = parent[i])
        ans.push_back(i);

    for(int i = ans.size()-1; i >= 0; --i) cout << ans[i] << " ";
}
