//
// Created by jaewon on 2017-06-26.
//
/*
 * 14628 입 챌린저
 *
 * foo(index, health) = 0~index번 까지의 기술을 사용하여 health 를 정확히 0으로 만드는데 필요한 최소의 마나포인트
 * 1) index번 기술을 사용하지 않는다.
 * 2) index번 기술을 1,2,3,....., x번 사용한다.
 *
 * foo(index, health) =
 *                      1) foo(index + 1, health) (사용하지 않는다)
 *                      2) foo(index + 1, health - damage[index] * x) + cost[index] * x + k * x * (x - 1) / 2 (index번 기술을 x번 사용한 경우)
 *                      이 때는 상대방의 체력을 damage[index] * x만큼 깎을 수 있고
 *                      비용은 cost, cost + k, cost + 2k, cost + 3k, ... , cost + (x-1)k 만큼씩 소모되므로
 *                      cost * x + (0 + 1 + 2 + 3 + ... + (x-1)) * k가 되고
 *                      이를 간단하게 변환하면
 *                      cost * x + k*(x * (x-1)) / 2 가 된다.
 *
 */
#include <iostream>
#include <cstring>
using namespace std;

const int MAXN = 101;
const int INF = 2e9;

int cache[MAXN][MAXN], cost[MAXN], damage[MAXN];
int n,m,k;

int foo(int index, int health){
    int& ret = cache[index][health];
    if(ret != -1) return ret;
    if(index == n) return ret = (health == 0 ? 0 : INF);
    ret = foo(index + 1, health);
    for(int i = 1; i * damage[index] <= health; ++i)
        ret = min(ret, foo(index + 1, health - damage[index] * i) + cost[index] * i + k * i * (i - 1) / 2);
    return ret;
}

int main(){
    freopen("input.txt","r",stdin);
    cin >> n >> m >> k;
    for(int i = 0; i < n; ++i) cin >> cost[i] >> damage[i];
    memset(cache,-1,sizeof(cache));
    cout << foo(0,m);
}