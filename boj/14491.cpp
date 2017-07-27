//
// Created by jaewon on 2017-07-16.
//
#include <iostream>
#include <vector>
using namespace std;

int main(){
    vector<char> ans;
    int t;
    cin >> t;

    if(t==0){
        cout << "0";
    }else{
        while(t){
            ans.push_back((t%9) + '0');
            t /= 9;
        }
        for(int i = ans.size()-1; i >= 0; --i) cout << ans[i];
    }
}
