//
// Created by jaewon on 2017-07-12.
//
#include <cstdio>
#include <vector>
#include <algorithm>
using namespace std;

int main(){
    int n,m;
    scanf("%d %d",&n,&m);
    vector<int> armor(n);
    for(int i = 0; i < n; ++i) scanf("%d",&armor[i]);

    sort(armor.begin(),armor.end());

    int ans = 0;
    for(int i = 0; i < n; ++i){
        if(binary_search(armor.begin() + i + 1, armor.end(), m-armor[i])) ans++;
    }
    printf("%d",ans);
}
