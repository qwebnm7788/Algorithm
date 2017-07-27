//
// Created by jaewon on 2017-07-14.
//
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main(){
    freopen("input.txt","r",stdin);
    ios_base::sync_with_stdio(false);
    long long n,m;
    cin >> n >> m;

    vector<long long> play(m);
    for(int i = 0; i < m; ++i) cin >> play[i];

    if(n <= m){
        cout << n;
    }else{
        long long lo = 0, hi = 20000000005LL;
        while(lo + 1 < hi){
            long long mid = (lo + hi) / 2LL;
            long long time = m;
            for(int i = 0; i < m; ++i){
                time += (mid / play[i]);
            }
            if(time >= n)
                hi = mid;
            else
                lo = mid;
        }

        long long temp = m;
        for(int i = 0; i < m; ++i){
            temp += (lo/play[i]);
        }

        for(int i = 0; i < m; ++i){
            if((hi % play[i]) == 0)
                temp++;
            if(temp == n){
                cout << i + 1;
                break;
            }
        }
    }
}
