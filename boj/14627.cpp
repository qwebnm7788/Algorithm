//
// Created by jaewon on 2017-06-28.
//

//??
#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;

int main(){
    freopen("input.txt","r",stdin);
    ios_base::sync_with_stdio(false);
    int s,c;
    cin >> s >> c;

    vector<long long> pa(s);
       for(int i = 0; i < s; ++i){
        cin >> pa[i];
    }

    long long lo = 1, hi = 1e9 + 5;
    long long ans = 0;
    while(lo + 1 < hi){
        long long mid = (lo + hi) / 2;
        long long cnt = 0;
        ans = 0;
        for(int i = 0; i < s; ++i){
            cnt += (pa[i]/mid);
            ans += (pa[i]%mid);
        }
        if(cnt >= c)
            lo = mid;
        else
            hi = mid;
    }
    ans = 0;
    for(int i = 0; i < s; ++i) ans += (pa[i] % lo);
    cout << ans;
}
