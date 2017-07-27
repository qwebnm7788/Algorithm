//
// Created by jaewon on 2017-07-16.
//
#include <iostream>
using namespace std;

int main(){
    freopen("input.txt","r",stdin);
    long long a,b,c;
    cin >> a >> b >> c;
    if(a + b >= 2 * c){
        cout << (a + b) - 2 * c;
    }else{
        cout << a + b;
    }
}
