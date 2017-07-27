//
// Created by jaewon on 2017-06-29.
//
#include <iostream>
#include <algorithm>
using namespace std;

const int MAXN = 101;
const int MAXK = 10005;
const int INF = 2e9;

int coin[MAXN];
int cache[MAXK];

int main(){
    freopen("input.txt","r",stdin);
    int n,k;
    cin >> n >> k;
    for(int i = 0; i < n; ++i) cin >> coin[i];
    cache[0] = 0;
    for(int i = 1; i <= k; ++i) cache[i] = INF;
    for(int i = 0; i < n; ++i){
        for(int j = 1; j <= k; ++j){
            if(j>=coin[i])
                cache[j] = min(cache[j],cache[j-coin[i]] + 1);
        }
    }
    if(cache[k] == INF) cout << "-1";
    else cout << cache[k];
}
