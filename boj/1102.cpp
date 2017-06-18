//
// Created by jaewon on 2017-06-18.
//

#include <iostream>
#include <algorithm>
#include <string>
#include <cstring>
using namespace std;

const int MAXN = 16;
const int INF = 2e9;

int cost[MAXN][MAXN];
int cache[1 << MAXN];
int n,p;

int bitCount(int n) {
    int ret = 0;
    while(n){
        ret += n % 2;
        n /= 2;
    }
    return ret;
}

int foo(int fixed){
    if(bitCount(fixed) >= p) return 0;
    int& ret = cache[fixed];
    if(ret != -1) return ret;
    ret = INF;
    for(int i = 0; i < n; ++i){
        if(fixed & (1 << i)){
            for(int j = 0; j < n; ++j){
                if(i == j || (fixed & (1 << j))) continue;
                ret = min(ret,foo(fixed | (1 << j)) + cost[i][j]);
            }
        }
    }
    return ret;
}
int main(){
    freopen("input.txt","r",stdin);
    cin >> n;
    for(int i = 0; i < n; ++i){
        for(int j = 0; j < n; ++j){
            cin >> cost[i][j];
        }
    }

    string x;
    cin >> x;
    int fixed = 0;
    for(int i = 0; i < x.length(); ++i){
        if(x[i] == 'Y') fixed |= (1 << i);
    }

    cin >> p;

    memset(cache,-1,sizeof(cache));
    int ans = foo(fixed);
    if(ans == INF) cout << "-1\n";
    else cout << ans;
}