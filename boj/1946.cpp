#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main(){
    freopen("input.txt","r",stdin);
    int test;
    cin >> test;
    while(test--){
        int n;
        cin >> n;

        vector<pair<int,int>> person(n);
        for(int i = 0; i < n; ++i) cin >> person[i].first >> person[i].second;

        sort(person.begin(),person.end());

        int answer = 0;
        int leftMin = person[0].second;
        for(int i = 1; i < n; ++i){
            if(leftMin < person[i].second){
                answer++;
            }else leftMin = min(leftMin,person[i].second);
        }
        cout << n - answer << endl;
    }
}