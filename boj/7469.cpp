//
// Created by jaewon on 2017-06-21.
//
/*
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main(){
    ios_base::sync_with_stdio(false);
    freopen("input.txt","r",stdin);
    int n,m;
    cin >> n >> m;

    vector<pair<int,int>> array(n);
    for(int i = 0; i < n; ++i){
        cin >> array[i].first;
        array[i].second = i;
    }

    sort(array.begin(),array.end());

    int a,b,k,cnt,ans;
    for(int i = 0; i < m; ++i){
        cnt = 0;

        cin >> a >> b >> k;
        a--,b--;

        for(int j = 0; j < n; ++j){
            if(array[j].second >= a && array[j].second <= b){
                cnt++;
                ans = array[j].first;
            }
            if(cnt == k) break;
        }
        cout << ans << endl;
    }
}
*/


//segment tree + parametric search 풀이

#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

const int INF = 2e9;

vector<vector<int>> segment;
vector<int> array;

vector<int> init(int node, int nodeLeft, int nodeRight){
    if(nodeLeft == nodeRight) return segment[node] = vector<int>(1,array[nodeLeft]);
    int mid = (nodeLeft + nodeRight) / 2;
    vector<int> left = init(node*2, nodeLeft, mid);
    vector<int> right = init(node*2+1,mid + 1, nodeRight);
    segment[node] = left;
    for(int i = 0; i < right.size(); ++i) segment[node].push_back(right[i]);
    sort(segment[node].begin(),segment[node].end());
    return segment[node];
}

int query(int left,int right, int node, int nodeLeft, int nodeRight, int val){
    if(right < nodeLeft || left > nodeRight) return 0;
    if(left <= nodeLeft && nodeRight <= right) return upper_bound(segment[node].begin(),segment[node].end(),val) - segment[node].begin();
    int mid = (nodeLeft + nodeRight) / 2;
    return query(left, right, node*2, nodeLeft, mid, val) + query(left, right, node*2 + 1, mid + 1, nodeRight, val);
}

int main(){
    ios_base::sync_with_stdio(false);
    freopen("input.txt","r",stdin);
    int n,m;
    cin >> n >> m;

    segment.resize(4*n);
    array.resize(n);
    for(int i = 0; i < n; ++i) cin >> array[i];

    init(1,0,n-1);

    int a,b,k;
    for(int i = 0; i < m; ++i){
        cin >> a >> b >> k;
        a--, b--;
        int lo = -INF, hi = INF;
        while(lo + 1 < hi){
            long long mid = (lo + hi) / 2;
            int cnt = query(a,b,1,0,n-1,mid);
            if(cnt < k) lo = mid;
            else hi = mid;
        }
        cout << hi << endl;
    }
}