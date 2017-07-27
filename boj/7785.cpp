//
// Created by jaewon on 2017-06-25.
//
#include <iostream>
#include <vector>
#include <string>
#include <map>
using namespace std;

int main(){
    ios_base::sync_with_stdio(false);
    freopen("input.txt","r",stdin);
    int n;
    cin >> n;

    map<string,int> mp;
    string name, state;
    for(int i = 0; i < n; ++i){
        cin >> name >> state;
        mp[name]++;
    }
    vector<string> ans;
    for(auto& person : mp){
        if(person.second%2) ans.push_back(person.first);
    }
    for(int i = ans.size()-1; i >= 0; --i) cout << ans[i] << endl;
}