//
// Created by jaewon on 2017-06-22.
//
#include <iostream>
using namespace std;

int main(){
    freopen("input.txt","r",stdin);
    int n;
    cin >> n;

    if(n%2){
        for(int i = 0; i < n; ++i) cout << "*";
        cout << endl;
        for(int i = 0; i < n/2 + 1; ++i){
            if(i == 0){
                for(int j = 0; j < n/2; ++j) cout << " ";
                cout << "*\n";
            }else{
                for(int j = 0; j < n/2 - i; ++j) cout << " ";
                cout << "*";
                for(int j = n/2 - i; j < n/2 -1 + i; ++j) cout << " ";
                cout << "*\n";
            }
        }
    }else{
        cout << "I LOVE CBNU";
    }
}
