//
// Created by jaewon on 2017-07-17.
//
#include <iostream>
#include <algorithm>
using namespace std;

int main(){
    int burger = 2500, drink = 2500, in;
    for(int i = 0; i < 3; ++i){
        cin >> in;
        if(in < burger)
            burger = in;
    }
    for(int i = 0; i < 2; ++i){
        cin >> in;
        if(in < drink)
            drink = in;
    }
    cout << burger + drink - 50;
}

