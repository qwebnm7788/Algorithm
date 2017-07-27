//
// Created by jaewon on 2017-07-16.
//
#include <iostream>
#include <vector>
using namespace std;

int main(){
    ios_base::sync_with_stdio(false);
    int n;
    cin >> n;

    vector<vector<int>> A(n,vector<int>(n)), B(n,vector<int>(n)), C(n,vector<int>(n));
    for(int k = 0; k < 2; ++k){
        for(int i = 0; i < n; ++i){
            for(int j = 0; j < n; ++j){
                if(k)
                    cin >> B[i][j];
                else
                    cin >> A[i][j];
            }
        }
    }

    int ans = 0;
    for(int i = 0; i < n; ++i){
        for(int j = 0; j < n; ++j){
            for(int k = 0; k < n; ++k){
                C[i][j] += A[i][k] * B[k][j];
            }
        }
    }

    for(int i = 0; i < n; ++i){
        for(int j = 0; j < n; ++j){
            ans += (C[i][j] > 0 ? 1 : 0);
        }
    }

    cout << ans;
}
