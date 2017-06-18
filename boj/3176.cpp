#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

const int MAXN = 100005;
const int INF = 2e9;

vector<vector<pair<int,int>>> adj;
vector<int> parent;
vector<int> depth;
vector<int> minPath, maxPath;

void dfs(int here){
    for(auto& edge : adj[here]){
        int next = edge.first;
        int nextCost = edge.second;
        if(parent[next] == -1){
            parent[next] = here;
            depth[next] = depth[here] + 1;
            minPath[next] = min(minPath[next],nextCost);
            maxPath[next] = max(maxPath[next],nextCost);
            dfs(next);
        }
    }
}

int main(){
    ios_base::sync_with_stdio(false);
    freopen("input.txt","r",stdin);
    int n;
    cin >> n;

    adj = vector<vector<pair<int,int>>>(n);
    parent = vector<int>(n,-1);
    depth = vector<int>(n,0);
    minPath = vector<int>(n,INF);
    maxPath = vector<int>(n,-1);

    int a,b,c;
    for(int i = 0; i < n-1; ++i){
        cin >> a >> b >> c;
        adj[a-1].push_back({b-1,c});
        adj[b-1].push_back({a-1,c});
    }

    depth[0] = 0;
    dfs(0);

    int k;
    cin >> k;
    for(int i = 0; i < k; ++i){
        int d,e;
        cin >> d >> e;
        d--,e--;

        if(depth[d] <= depth[e]) swap(d,e);

        vector<int> path;
        int x = -1 ,y = -1;
        while((depth[d] != depth[e])){
            for(int j =0; j < adj[d].size(); ++j){
                if(adj[d][j].first == parent[d]){
                    x = adj[d][j].second;
                    break;
                }
            }
            if(x != -1)
                path.push_back(x);

            d = parent[d];
        }

        if(d != e){
            x = -1;
            while(d != e){
                for(int j = 0; j < adj[d].size(); ++j){
                    if(adj[d][j].first == parent[d]){
                        x = adj[d][j].second;
                        break;
                    }
                }
                for(int j = 0; j < adj[e].size(); ++j){
                    if(adj[e][j].first == parent[e]){
                        y = adj[e][j].second;
                        break;
                    }
                }

                d = parent[d];
                e = parent[e];

                if(x != -1)
                    path.push_back(x);
                if(y != -1)
                    path.push_back(y);
            }
        }

        sort(path.begin(),path.end());
        cout << path.front() << " " << path.back() << endl;
    }
}
