//
// Created by jaewon on 2017-07-16.
//
#include <iostream>
using namespace std;

int main(){
    ios_base::sync_with_stdio(false);
    int n;
    cin >> n;

    int maxVal = 0, total = 0, in;
    for(int i = 0; i < n; ++i){
        cin >> in;
        if(in > maxVal){
            maxVal = in;
        }
        total += in;
    }

    cout << total - maxVal;
}

