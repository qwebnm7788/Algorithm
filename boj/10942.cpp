//
// Created by jaewon on 2017-07-12.
//
#include <cstdio>
#include <string>
#include <cstring>
#include <algorithm>
using namespace std;

const int MAXN = 2001;

int cache[MAXN][MAXN];
int number[MAXN];

int foo(int start, int end){
    if(start == end) return 1;
    if(end - start == 1) return (number[start] == number[end] ? 1 : 0);
    int& ret = cache[start][end];
    if(ret != -1) return ret;
    if(number[start] == number[end]) return ret = foo(start+1,end-1);
    else return ret = 0;
}

int main(){
    freopen("input.txt","r",stdin);
    int n;
    scanf("%d",&n);
    for(int i = 0; i < n; ++i) scanf("%d",&number[i]);

    int m;
    scanf("%d",&m);

    memset(cache,-1,sizeof(cache));
    int s,e;
    for(int i = 0; i < m; ++i){
        scanf("%d %d",&s,&e);
        printf("%d\n",foo(s-1,e-1));
    }
}