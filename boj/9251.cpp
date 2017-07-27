//
// Created by jaewon on 2017-06-29.
//
#include <iostream>
#include <string>
#include <cstring>
#include <algorithm>
using namespace std;

const int MAXN = 1001;

int cache[MAXN][MAXN];
string a,b;

int foo(int x, int y){
    if(x < 0 || y < 0) return 0;
    int& ret = cache[x][y];
    if(ret != -1) return ret;
    if(a[x] == b[y])
        ret = foo(x-1,y-1) + 1;
    else
        ret = max(foo(x-1,y),foo(x,y-1));
    return ret;
}

int main(){
    freopen("input.txt","r",stdin);
    cin >> a >> b;
    memset(cache,-1,sizeof(cache));
    cout << foo(a.length()-1, b.length()-1);
}
