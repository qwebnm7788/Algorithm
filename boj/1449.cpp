//
// Created by jaewon on 2017-06-19.
//

#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main(){
    freopen("input.txt","r",stdin);
    int n,l;
    cin >> n >> l;
    vector<int> pos(n);
    for(int i = 0; i < n; ++i) cin >> pos[i];
    sort(pos.begin(),pos.end());
    double current = 0.5;
    int ans = 0;
    for(int i = 0; i < n; ++i){
        if(pos[i] - 0.5 > current){
            current = pos[i] - 0.5 + l;
            ans++;
        }else if(pos[i] + 0.5 > current){
            current += l;
            ans++;
        }
    }
    cout << ans;
}
