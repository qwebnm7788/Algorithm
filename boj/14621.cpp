//
// Created by jaewon on 2017-06-15.
//

#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

vector<int> parent;

int find(int x){
    if(parent[x] < 0) return x;
    else return parent[x] = find(parent[x]);
}

bool merge(int a, int b){
    a = find(a);
    b = find(b);
    if(a == b) return false;
    parent[a] = b;
    return true;
}

int main(){
    freopen("input.txt","r",stdin);
    int n,m;
    cin >> n >> m;

    vector<bool> type(n,false);         //M = true, W = false
    vector<vector<pair<int,int>>> adj(n);
    vector<pair<int,pair<int,int>>> edge;

    parent = vector<int>(n,-1);

    char in;
    for(int i = 0; i < n; ++i){
        cin >> in;
        if(in == 'M') type[i] = true;
    }

    int u,v,d;
    for(int i = 0; i < m; ++i){
        cin >> u >> v >> d;
        adj[u-1].push_back({v-1,d});
        adj[v-1].push_back({u-1,d});
        edge.push_back({d,{u-1,v-1}});
    }

    sort(edge.begin(),edge.end());

    bool check = false;
    int ans = 0, cnt = 0;
    for(int i = 0; i < m; ++i){
        u = edge[i].second.first;
        v = edge[i].second.second;
        d = edge[i].first;
        if(type[u] == type[v]) continue;
        if(merge(u,v)){
            ans += d;
            if(++cnt == n-1){
                break;
            }
        }
    }
    if(cnt == n-1) cout << ans << endl;
    else cout << "-1\n";
}