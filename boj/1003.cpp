//
// Created by jaewon on 2017-06-29.
//
#include <iostream>
#include <cstring>
using namespace std;

int one[41], zero[41];

int one_fibo(int x){
    int& ret = one[x];
    if(ret != -1) return ret;
    if(x == 0) return ret = 0;
    else if(x == 1) return ret = 1;
    return ret = one_fibo(x-1) + one_fibo(x-2);
}

int zero_fibo(int x){
    int& ret = zero[x];
    if(ret != -1) return ret;
    if(x == 0) return ret = 1;
    else if(x == 1) return ret = 0;
    return ret = zero_fibo(x-1) + zero_fibo(x-2);
}

int main(){
    freopen("input.txt","r",stdin);
    int test;
    cin >> test;
    memset(zero,-1,sizeof(zero));
    memset(one,-1,sizeof(one));

    while(test--){
        int n;
        cin >> n;
        zero_fibo(n);
        one_fibo(n);
        cout << zero[n] << " " << one[n] << endl;
    }
}