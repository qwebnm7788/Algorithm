//
// Created by jaewon on 2017-07-16.
//
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main(){
    freopen("input.txt","r",stdin);
    ios_base::sync_with_stdio(false);
    int n;
    double t;
    cin >> n >> t;

    vector<int> position(n), speed(n);
    for(int i = 0; i < n; ++i) cin >> position[i];
    for(int i = 0; i < n; ++i) cin >> speed[i];

    double maxLeft = -1000000005.0, minRight = 1000000005.0;
    bool ans = false;
    for(int i = 0; i < n; ++i){
        maxLeft = max(maxLeft,position[i] - speed[i]*t);
        minRight = min(minRight,position[i] + speed[i]*t);
    }

    if(minRight >= maxLeft){
        ans = true;
    }

    if(ans) cout << "1";
    else cout << "0";
}
/*이분탐색 풀이
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main(){
    ios_base::sync_with_stdio(false);
    freopen("input.txt","r",stdin);
    int n;
    double t;
    cin >> n >> t;

    vector<double> position(n), speed(n);
    for(int i = 0; i < n; ++i) cin >> position[i];
    for(int i = 0; i < n; ++i) cin >> speed[i];

    bool ans = false;
    double lo = 0LL, hi = 1000000005.0;
    for(int i = 0; i < 50; ++i){
        double mid = (lo + hi) / 2.0;
        double leftMax = 0, rightMax = 0;
        for(int i = 0; i < n; ++i){
            if(position[i] < mid){
                leftMax = max(leftMax,(mid-position[i])/speed[i]);
            }else{
                rightMax = max(rightMax,(position[i]-mid)/speed[i]);
            }
        }

        if(rightMax <= t && leftMax <= t){
            ans = true;
            break;
        }

        if(rightMax > leftMax){
            lo = mid;
        }else{
            hi = mid;
        }
    }

    if(ans) cout << "1";
    else cout << "0";
}

*/