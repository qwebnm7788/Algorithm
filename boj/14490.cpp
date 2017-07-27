//
// Created by jaewon on 2017-07-16.
//
#include <iostream>
using namespace std;

int gcd(int a, int b){
    if(b == 0) return a;
    return gcd(b, a % b);
}

int main(){
    int a,b;
    char buf;
    cin >> a >> buf >> b;
    int c = gcd(a,b);
    cout << a/c << buf << b/c;
}
