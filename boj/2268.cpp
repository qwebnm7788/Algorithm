//
// Created by jaewon on 2017-06-20.
//
#include <cstdio>
#include <vector>
#include <algorithm>
using namespace std;

vector<long long> segment;

long long init(const vector<int>& array, int nodeLeft, int nodeRight, int node){
    if(nodeLeft == nodeRight) return segment[node] = array[nodeLeft];
    int mid = (nodeLeft + nodeRight) / 2;
    return segment[node] = init(array,nodeLeft,mid,node*2) + init(array,mid+1,nodeRight, node*2 + 1);
}

long long query(int left, int right, int node, int nodeLeft, int nodeRight){
    if(right < nodeLeft || left > nodeRight) return 0;
    if(left <= nodeLeft && nodeRight <= right) return segment[node];
    int mid = (nodeLeft + nodeRight) / 2;
    return query(left,right,node*2,nodeLeft,mid) + query(left,right,node*2+1,mid+1,nodeRight);
}

long long update(int index, int newVal, int node, int nodeLeft, int nodeRight){
    if(index < nodeLeft || index > nodeRight) return segment[node];
    if(nodeLeft == nodeRight) return segment[node] = newVal;
    int mid = (nodeLeft + nodeRight) / 2;
    return segment[node] = update(index,newVal,node*2,nodeLeft,mid) + update(index, newVal, node*2+1,mid+1,nodeRight);
}


int main(){
    freopen("input.txt","r",stdin);
    int n,m;
    scanf("%d %d",&n,&m);
    segment.resize(4*n);
    vector<int> A(n,0);

    init(A,0,n-1,1);

    int a,b,c;
    for(int i = 0; i < m; ++i){
        scanf("%d %d %d",&a,&b,&c);
        b--;
        if(a == 0){
            c--;
            if(b > c) swap(b,c);
            printf("%lld\n",query(b,c,1,0,n-1));
        }else{
            update(b,c,1,0,n-1);
        }
    }
}
