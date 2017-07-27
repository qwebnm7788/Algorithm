//
// Created by jaewon on 2017-07-20.
//
#include <iostream>
#include <vector>
using namespace std;

int main(){
    freopen("input.txt","r",stdin);
    int n,k;
    cin >> n >> k;

    vector<int> coin(n);
    for(int i = 0; i < n; ++i) cin >> coin[i];

    int answer = 0;
    for(int i = n-1; i >= 0; --i){
        answer += (k/coin[i]);
        k = (k % coin[i]);
    }

    cout << answer;
}

