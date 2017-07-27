//
// Created by jaewon on 2017-07-19.
//
#include <iostream>
#include <cstring>
using namespace std;

const int MAXN = 117;

long long cache[MAXN];

long long fibo(int n){
    long long& ret = cache[n];
    if(ret != -1) return ret;
    if(n == 1 || n == 2 || n == 3) return ret = 1;
    else return ret = fibo(n-1) + fibo(n-3);
}

int main(){
    int n;
    cin >> n;
    memset(cache,-1,sizeof(cache));
    cout << fibo(n);
}
