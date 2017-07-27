//
// Created by jaewon on 2017-07-19.
//
#include <iostream>
#include <set>
#include <cmath>
using namespace std;

int gcd(int a, int b){
    if(b == 0) return a;
    else return gcd(b,a%b);
}

int main(){
    int d1,d2;
    cin >> d1 >> d2;

    set<pair<int,int>> st;
    for(int i = d1; i <= d2; ++i){
        for(int j = 1; j <= i; ++j){
            int x = gcd(i,j);
            st.insert({i/x,j/x});
        }
    }

    cout << st.size();
}
