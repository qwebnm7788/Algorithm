//
// Created by jaewon on 2017-06-15.
//

#include <iostream>
#include <string>
using namespace std;

int main(){
    int a,b;
    string c;
    cin >> a >> b >> c;

    if((c[c.length()-1]-'0') % 2) cout << (a^b);
    else cout << a;
}