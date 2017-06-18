//
// Created by jaewon on 2017-06-16.
//

#include <iostream>
#include <string>
using namespace std;

int main(){
    freopen("input.txt","r",stdin);
    string a,b,c;
    cin >> a >> b;

    int aLen = a.length(), bLen = b.length();
    unsigned long long aVal = 0, bVal = 0;

    for(int i = aLen-1; i >= 0; --i)
        aVal += (a[i]-'0')*(1 << (aLen-1-i));
    for(int i = bLen-1; i >= 0; --i)
        bVal += (b[i]-'0')*(1 << (bLen-1-i));

    aVal *= bVal;
    while(aVal){
        c.push_back(aVal%2+'0');
        aVal /= 2;
    }

    int cLen = c.length();
    for(int i = cLen-1; i >= 0; --i) cout << c[i];
}