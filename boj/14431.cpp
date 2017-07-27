//
// Created by jaewon on 2017-07-10.
//
#include <iostream>
#include <vector>
#include <cmath>
#include <cstring>
#include <algorithm>
#include <queue>
using namespace std;

const int MAXPRIME = 5000;
const int INF = 2e9;

bool isPrime[MAXPRIME];

void findPrime(){
    isPrime[0] = isPrime[1] = false;
    for(int i = 2; i <= MAXPRIME; ++i){
        if(isPrime[i]){
            for(int j = 2*i; j <= MAXPRIME; j += i){
                isPrime[j] = false;
            }
        }
    }
}

int getDistance(pair<int,int>& a, pair<int,int>& b){
    return (int)sqrt((a.first-b.first)*(a.first-b.first)+(a.second-b.second)*(a.second-b.second));
}

int main(){
    ios_base::sync_with_stdio(false);
    freopen("input.txt","r",stdin);
    memset(isPrime,1,sizeof(isPrime));
    findPrime();

    int startX,startY,endX,endY;
    cin >> startX >> startY >> endX >> endY;

    int n;
    cin >> n;

    vector<vector<pair<int,int>>> adj(n+2);
    vector<pair<int,int>> town(n+2);
    int x,y;
    for(int i = 1; i <= n; ++i){
        cin >> x >> y;
        town[i] = {x,y};
    }

    town[0] = {startX,startY};
    town[n+1] = {endX,endY};

    for(int i = 0; i < n+2; ++i){
        for(int j = 0; j < n+2; ++j){
            if(i==j) continue;
            adj[i].push_back({j,getDistance(town[i],town[j])});
            adj[j].push_back({i,getDistance(town[i],town[j])});
        }
    }

    vector<int> dist(n+2,INF);
    priority_queue<pair<int,int>> pq;
    dist[0] = 0;
    pq.push({0,0});
    while(!pq.empty()){
        int here = pq.top().second;
        int cost = -pq.top().first;
        pq.pop();

        if(dist[here] < cost) continue;

        for(auto& edge : adj[here]){
            if(dist[edge.first] > dist[here] + edge.second && isPrime[edge.second]){
                dist[edge.first] = dist[here] + edge.second;
                pq.push({-dist[edge.first],edge.first});
            }
        }
    }

    if(dist[n+1] == INF) cout << "-1";
    else cout << dist[n+1];
}
