//
// Created by jaewon on 2017-07-02.
//
#include <iostream>
#include <cstring>
#include <algorithm>
using namespace std;

const int MAXN = 1001;
const int MOD = 10007;

int cache[MAXN];

int foo(int n){
    if(n < 0) return 0;
    if(n == 0) return 1;
    int& ret = cache[n];
    if(ret != -1) return ret;
    ret = (foo(n-1) + foo(n-2)) % MOD;
    return ret;
}

int main(){
    int n;
    cin >> n;
    memset(cache,-1,sizeof(cache));
    cout << foo(n);
}
