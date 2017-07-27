//
// Created by jaewon on 2017-06-19.
//
#include <iostream>
#include <cstring>
using namespace std;

const int MAXN = 68;

long long cache[MAXN];

long long koong(int n){
    long long& ret = cache[n];
    if(ret != -1) return ret;
    if(n < 2) return 1;
    else if(n ==2) return 2;
    else if(n ==3) return 4;
    else return ret = koong(n-1) + koong(n-2) + koong(n-3) + koong(n-4);
}
int main(){
    freopen("input.txt","r",stdin);
    int test;
    cin >> test;
    memset(cache,-1,sizeof(cache));
    while(test--){
        int n;
        cin >> n;
        cout << koong(n) << endl;
    }
}
