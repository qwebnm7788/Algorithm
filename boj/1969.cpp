//
// Created by jaewon on 2017-06-22.
//
#include <iostream>
#include <string>
#include <vector>
#include <map>
using namespace std;

const int INF = 2e9;

int main(){
    freopen("input.txt","r",stdin);
    int n,m;
    cin >> n >> m;

    vector<string> array(n);
    for(int i = 0; i < n; ++i) cin >> array[i];

    int ans = 0;
    for(int i = 0; i < m; ++i){
        map<char,int> mp;
        for(int j = 0; j < n; ++j) mp[array[j][i]]++;
        int temp = mp['A'];
        char choice = 'A';
        if(mp['C'] > temp){
            temp = mp['C'];
            choice = 'C';
        }
        if(mp['G'] > temp){
            temp = mp['G'];
            choice = 'G';
        }
        if(mp['T'] > temp){
            temp = mp['T'];
            choice = 'T';
        }
        cout << choice;
        ans += n - temp;
    }
    cout << endl << ans;
}
