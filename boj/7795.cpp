//
// Created by jaewon on 2017-07-12.
//
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main(){
    ios_base::sync_with_stdio(false);
    freopen("input.txt","r",stdin);
    int test;
    cin >> test;
    while(test--){
        int n,m;
        cin >> n >> m;

        vector<int> A(n), B(m);
        for(int i = 0; i < n; ++i) cin >> A[i];
        for(int i = 0; i < m; ++i) cin >> B[i];
        sort(B.begin(),B.end());

        int ans = 0;
        for(int i = 0; i < n; ++i){
            ans += lower_bound(B.begin(),B.end(),A[i]) - B.begin();
        }
        cout << ans << endl;
    }
}
