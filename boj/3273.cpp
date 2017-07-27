//
// Created by jaewon on 2017-07-12.
//
#include <cstdio>
#include <vector>
#include <algorithm>
using namespace std;

int main(){
    freopen("input.txt","r",stdin);
    int n;
    scanf("%d",&n);

    vector<int> number(n);
    for(int i = 0; i < n; ++i) scanf("%d",&number[i]);

    sort(number.begin(),number.end());

    int x;
    scanf("%d",&x);

    int ans = 0;
    for(int i = 0; i < n; ++i){
        if(binary_search(number.begin() + i + 1,number.end(),x-number[i])) ans++;
    }
    printf("%d",ans);
}