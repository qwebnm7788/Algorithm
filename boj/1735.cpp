//
// Created by jaewon on 2017-06-15.
//

#include <iostream>
#include <vector>
using namespace std;

int gcd(int a, int b){
    if((a%b) == 0) return b;
    else return gcd(b,a%b);
}

int main(){
    int a,b,c,d;
    cin >> a >> b >> c >> d;
    a = a*d + b*c;
    b = b*d;
    int g = gcd(a,b);
    cout << (a/g) << " " << (b/g);
}
