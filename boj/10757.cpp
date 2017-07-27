//
// Created by jaewon on 2017-06-21.
//

#include <iostream>
#include <string>
#include <algorithm>

using namespace std;

int main(){
    freopen("input.txt","r",stdin);
    string a,b,c;
    cin >> a >> b;
    if(a.length() < b.length()){
        string tmp = b;
        b = a;
        a = tmp;
    }
    int aLen = a.length(), bLen = b.length();
    int len = b.length();
    int carry = 0,x,y,temp;

    for(int i = 0; i < aLen; ++i){
        x = a[aLen-1-i] - '0';
        if(i < bLen){
            y = b[bLen-1-i] - '0';
            temp = x + y + carry;
        }else{
            temp = x + carry;
        }
        carry = temp / 10;
        a[aLen-1-i] = (temp % 10) + '0';
    }
    if(carry) cout << "1";
    for(int i = 0; i < aLen; ++i) cout << a[i];
}
