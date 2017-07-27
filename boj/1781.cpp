//
// Created by jaewon on 2017-07-20.
//
#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
using namespace std;

int main(){
    ios_base::sync_with_stdio(false);
    freopen("input.txt","r",stdin);
    int n;
    cin >> n;

    vector<pair<int,int>> arr(n);
    for(int i = 0; i < n; ++i) cin >> arr[i].first >> arr[i].second;

    sort(arr.begin(),arr.end());

    priority_queue<int> pq;
    int answer = 0, current = 0;
    for(int i = 0; i < n; ++i){
        current = arr[i].first;             //현재까지의 데드라인
        pq.push(-arr[i].second);
        while(pq.size() > current){
            pq.pop();
        }
    }

    while(!pq.empty()){
        answer += (-pq.top());
        pq.pop();
    }

    cout << answer;
}