//
// Created by jaewon on 2017-07-17.
//
#include <iostream>
#include <cstring>
using namespace std;

const int MAXN = 1001;
const int MOD = 1e9 + 7;

long long cache[MAXN][MAXN];
int n,m;

//foo(i,j) = (i,j) -> (n,m)으로 가는 경우의 수
long long foo(int i, int j){
    if(i == n - 1 && j == m - 1) return 1;
    if(i >= n || j >= m) return 0;
    long long& ret = cache[i][j];
    if(ret != -1) return ret;
    return ret = (foo(i,j+1) + foo(i+1,j) + foo(i+1,j+1)) % MOD;
}

int main(){
    cin >> n >> m;
    memset(cache,-1,sizeof(cache));
    cout << foo(0,0);
}
