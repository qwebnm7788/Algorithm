//
// Created by jaewon on 2017-07-20.
//
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main(){
    ios_base::sync_with_stdio(false);
    freopen("input.txt","r",stdin);
    int n,l;
    cin >> n >> l;

    vector<pair<int,int>> pos(n);
    for(int i = 0; i < n; ++i) cin >> pos[i].first >> pos[i].second;

    sort(pos.begin(),pos.end());

    int answer = 0, current = 0, temp;              //현재 current까지(!) 덮여있는 상태
    for(int i = 0; i < n; ++i){
        temp = 0;
        if(current < pos[i].first){
            temp = (pos[i].second-pos[i].first) / l + ((pos[i].second-pos[i].first) % l ? 1 : 0);
            current = pos[i].first + temp * l;
        }else if(current >= pos[i].first && current < pos[i].second){
            temp = (pos[i].second-current) / l + ((pos[i].second-current) % l ? 1 : 0);
            current = current + temp * l;
        }
        answer += temp;
    }
    cout << answer;
}
