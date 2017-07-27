//
// Created by jaewon on 2017-07-11.
//
#include <iostream>
#include <algorithm>
#include <cstring>
using namespace std;

const int MAXN = 501;
const int INF = 2e9;

int cache[MAXN][MAXN];
int pSum[MAXN];

//[start:end]를 합치는데 필요한 최소의 비용을 반환한다.
int foo(int start, int end){
    if(start == end) return 0;
    int& ret = cache[start][end];
    if(ret != -1) return ret;
    ret = INF;
    for(int k = start; k < end; ++k){
        ret = min(ret, foo(start,k)+foo(k+1,end) + (pSum[end]-(start == 0 ? 0 : pSum[start-1])));
    }
    return ret;
}

int main(){
    freopen("input.txt","r",stdin);
    int test;
    cin >> test;
    while(test--){
        int k;
        cin >> k;
        for(int i = 0; i < k; ++i){
            cin >> pSum[i];
            if(i)
                pSum[i] += pSum[i-1];
        }
        memset(cache,-1,sizeof(cache));
        cout << foo(0,k-1) << endl;
    }
}
