//
// Created by jaewon on 2017-06-16.
//


#include <iostream>
#include <cstring>
#include <algorithm>
#include <vector>

using namespace std;

const int MAXN = 100;
const int MAXK = 501;
const int INF = 2e9;

int cache[MAXN][MAXK];
vector<vector<int>> adj;
vector<int> height;

int foo(int here, int cnt){
    if(cnt == 0) return height[here];
    int& ret = cache[here][cnt];
    if(ret != -1) return ret;
    ret = INF;
    for(int next : adj[here]){
        ret = min(ret,foo(next,cnt-1));
    }
    return ret;
}

int main(){
    ios_base::sync_with_stdio(false);
    freopen("input.txt","r",stdin);

    int n,m;
    cin >> n >> m;

    height.resize(n);
    adj.resize(n);
    memset(cache,-1,sizeof(cache));

    for(int i = 0; i < n; ++i) cin >> height[i];

    int u,v;
    for(int i = 0; i < m; ++i){
        cin >> u >> v;
        adj[u-1].push_back(v-1);
        adj[v-1].push_back(u-1);
    }

    int t;
    cin >> t;
    while(t--){
        int a,k;
        cin >> a >> k;
        a--;
        int ans = foo(a,k);
        if(ans == INF) cout << "-1\n";
        else cout << ans << endl;
    }
}