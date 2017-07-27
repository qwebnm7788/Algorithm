//
// Created by jaewon on 2017-06-29.
//
#include <iostream>
#include <cstring>
using namespace std;

const int MAXN = 91;

long long cache[MAXN][2];

int main(){
    int n;
    cin >> n;

    cache[1][0] = 0;
    cache[1][1] = 1;
    for(int i = 2; i <= n; ++i){
        cache[i][0] = cache[i-1][1] + cache[i-1][0];
        cache[i][1] = cache[i-1][0];
    }
    cout << cache[n][0] + cache[n][1];
}
