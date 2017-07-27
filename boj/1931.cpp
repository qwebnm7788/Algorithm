#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

bool cmp(pair<int,int> a, pair<int,int> b){
    if(a.second != b.second) return a.second < b.second;
    else return a.first < b.first;
}

int main(){
    ios_base::sync_with_stdio(false);
    int n;
    cin >> n;

    vector<pair<int,int>> time(n);
    for(int i = 0; i < n; ++i) cin >> time[i].first >> time[i].second;

    sort(time.begin(),time.end(),cmp);

    int answer = 0;
    int current = 0;
    for(int i = 0; i < n; ++i){
        if(time[i].first < current) continue;
        current = time[i].second;
        answer++;
    }
    cout << answer;
}