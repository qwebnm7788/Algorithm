//
// Created by jaewon on 2017-07-19.
//
#include <iostream>
#include <vector>
using namespace std;

const int MOD = 1000000007;

int main(){
    int n;
    cin >> n;

    vector<long long> position(n);
    for(int i = 0; i < n; ++i) cin >> position[i];

    long long answer = 1;
    vector<long long> cost(n);
    for(int i = 1; i < n; ++i){
        cost[i] = (cost[i-1] + i * (position[i] - position[i-1])) % MOD;
        answer = (answer * cost[i]) % MOD;
    }
    cout << answer;
}
