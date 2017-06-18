//
// Created by jaewon on 2017-06-16.
//

#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>

using namespace std;

struct line{
    int sx,sy,dx,dy;
};

int main(){
    ios_base::sync_with_stdio(false);
    freopen("input.txt","r",stdin);
    int n;
    cin >> n;

    vector<line> radio(n);
    for(int i = 0; i < n; ++i)
        cin >> radio[i].sx >> radio[i].sy >> radio[i].dx >> radio[i].dy;

    int m;
    cin >> m;

    vector<double> laser(m);
    int x,y;
    for(int i = 0; i < m; ++i){
        cin >> x >> y;
        laser[i] = atan2(y,x);
    }

    sort(laser.begin(),laser.end());

    int ans = 0;
    for(int i = 0; i < n; ++i){
        int lo = 0, hi = m-1;
        double radianLow = atan2(radio[i].sy,radio[i].sx);
        double radianHi = atan2(radio[i].dy,radio[i].dx);
        if(radianLow > radianHi) swap(radianLow,radianHi);
        vector<double>::iterator itLow = lower_bound(laser.begin(),laser.end(),radianLow);
        if(itLow != laser.end() && *itLow <= radianHi) ans++;
    }
    cout << n-ans;
}