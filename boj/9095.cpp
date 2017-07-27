//
// Created by jaewon on 2017-06-29.
//
#include <iostream>
#include <cstring>
using namespace std;

const int MAXN = 12;
int cache[MAXN];

int foo(int x){
    if(x < 0) return 0;
    else if(x == 0) return 1;

    int& ret = cache[x];
    if(ret != -1) return ret;
    ret = foo(x-1);
    if(x >= 2) ret += foo(x-2);
    if(x >= 3) ret += foo(x-3);
    return ret;
}

int main(){
    freopen("input.txt","r",stdin);
    int test;
    cin >> test;
    memset(cache,-1,sizeof(cache));
    while(test--){
        int x;
        cin >> x;
        cout << foo(x) << endl;
    }
}
