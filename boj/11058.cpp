//
// Created by jaewon on 2017-06-26.
//

/*
 * 11058 크리보드
 *
 * foo(n) = n번 버튼을 눌러 얻을 수 있는 최대의 A의 갯수
 *
 * Ctrl + A , Ctrl + C는 함께 붙어있어야 의미있는 작업이고
 * Ctrl + A, Ctrl + C 이후에 Ctrl + V를 연속해서 하는 것으로 갯수를 늘릴 수 있다.
 *
 * foo(n) =
 *          1) foo(n-1) + 1
 *          2) foo(n-2-i) * (i + 1) (i = 1~n-2)
 * 2의 경우를 자세히 살펴보면
 * Ctrl + A, Ctrl + C의 행동을 위해서는 최소 2번이 필요하므로 N-2번에서 시작하며
 * N-2-i번째부터 N번째 버튼까지 Ctrl + V를 누른다는 의미이다.
 * 따라서 Ctrl + A, Ctrl + C를 완성시킨 버튼에서의 출력 수인 foo(n-2-i)가 (i+1)번 복붙된것이므로 저 식이 성립하게 된다.
 *
 * 예를들어 i = 1인 경우
 * foo(n) = max(foo(n-1) + 1, foo(n-2-1) * (2))가 되는데
 * foo(n-2-1) * 2 를 보면
 * foo(n-2)까지 Ctrl + A, Ctrl + C가 완성되고 foo(n-3)번째에서부터 Ctrl + V를 반복해서 눌렀다는 이야기가 된다.
 *
 *
 *
 */
#include <iostream>
#include <cstring>
using namespace std;

const int MAXN = 101;

long long cache[MAXN];

long long foo(int n){
    long long& ret = cache[n];
    if(n == 0) return ret = 0;
    if(ret != -1) return ret;
    ret = foo(n-1) + 1;
    if(n >= 2){
        for(int i = 1; i <= n-2; ++i)
            ret = max(ret, foo(n-2-i) * (i + 1));
    }
    return ret;
}

int main(){
    int n;
    cin >> n;
    memset(cache,-1,sizeof(cache));
    cout << foo(n);
}
