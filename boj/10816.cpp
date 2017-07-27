//
// Created by jaewon on 2017-06-20.
//
#include <cstdio>
#include <algorithm>
#include <vector>
using namespace std;

int main(){
    freopen("input.txt","r",stdin);
    int n;
    scanf("%d",&n);

    vector<int> card(n);
    for(int i = 0; i < n; ++i) scanf("%d",&card[i]);

    sort(card.begin(),card.end());

    int m;
    scanf("%d",&m);

    int in;
    for(int i = 0; i < m; ++i){
        scanf("%d",&in);
        int lo = lower_bound(card.begin(),card.end(),in)-card.begin();
        int hi = upper_bound(card.begin(),card.end(),in)-card.begin();
        printf("%d ", hi - lo);
    }
}
