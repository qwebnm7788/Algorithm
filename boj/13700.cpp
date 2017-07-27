//
// Created by jaewon on 2017-06-28.
//
#include <iostream>
#include <algorithm>
#include <vector>
#include <cstring>
using namespace std;

const int MAXN = 100005;
const int INF = 2e9;

int cache[MAXN];
int n,s,d,f,b,k;
vector<int> police;

int foo(int current){
    if(current < 0 || current > n) return INF;
    int& ret = cache[current];
    if(ret != -1) return ret;
    if(current == d) return ret = 0;
    ret = INF;
    for(int i = 0; i < k; ++i)
        if(current == police[i]) return INF;
    ret = min(ret, foo(current+f) + 1);
    ret = min(ret, foo(current-b) + 1);
    return ret;
}

int main(){
    freopen("input.txt","r",stdin);
    cin >> n >> s >> d >> f >> b >> k;
    police.resize(k);
    memset(cache,-1,sizeof(cache));
    for(int i = 0; i < k; ++i) cin >> police[i];
    int ans = foo(s);
    if(ans == INF) cout << "BUG FOUND";
    else cout << ans;
}