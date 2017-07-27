//
// Created by jaewon on 2017-07-16.
//
#include <iostream>
#include <vector>
using namespace std;

int main(){
    ios_base::sync_with_stdio(false);
    freopen("input.txt","r",stdin);
    int n;
    cin >> n;

    vector<pair<int,int>> bot(n);
    for(int i = 0; i < n; ++i) cin >> bot[i].first >> bot[i].second;

    int time = 0;
    int currentIndex = -1;
    while(currentIndex != n-1){
        if(time % (bot[currentIndex+1].first + bot[currentIndex+1].second) <= bot[currentIndex+1].second){
            time += bot[currentIndex+1].second - (time % (bot[currentIndex+1].first + bot[currentIndex+1].second));
        }
        time += 1;
        currentIndex++;
    }
    cout << time;
}
