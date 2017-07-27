//
// Created by jaewon on 2017-07-02.
//
#include <iostream>
#include <cstring>
#include <algorithm>
using namespace std;

const int MAXN = 10005;

int cache[MAXN][3];
int amount[MAXN];
int n;

//~current까지 before 잔을 연속해서 마셨을때 최대한 많이 마실 수 있는 포도주의 양
int foo(int current, int before){
    if(current == n) return 0;
    int& ret = cache[current][before];
    if(ret != -1) return ret;
    ret = foo(current+1,0);
    if(before < 2)
        ret = max(ret,foo(current+1,before+1) + amount[current]);
    return ret;
}

int main(){
    freopen("input.txt","r",stdin);
    cin >> n;
    memset(cache,-1,sizeof(cache));
    for(int i = 0; i < n; ++i) cin >> amount[i];
    cout << foo(0,0);
}
