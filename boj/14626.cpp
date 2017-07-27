//
// Created by jaewon on 2017-06-22.
//
#include <iostream>
#include <string>
using namespace std;

int main(){
    freopen("input.txt","r",stdin);
    string in;
    cin >> in;

    int index, temp = 0, ans;
    for(int i = 0; i < 13; ++i){
        if(in[i] == '*') index = i;
        else{
            if(i%2 == 0) temp += in[i] -'0';
            else temp += 3 * (in[i] - '0');
        }
    }
    ans = temp % 10;
    if(ans == 0) ans = 0;
    else ans = 10 - (temp % 10);

    if(index % 2 == 0){
        cout << ans;
    }else{
        for(int i = 9; i >= 0; --i){
            if((3*i) % 10 == ans){
                cout << i;
                break;
            }
        }
    }
}
