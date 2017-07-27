//
// Created by jaewon on 2017-06-20.
//
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main() {
    freopen("input.txt", "r", stdin);
    int n, h;
    cin >> n >> h;

    vector<int> aHeight(n / 2), bHeight(n / 2);
    for (int i = 0; i < n / 2; ++i) cin >> aHeight[i] >> bHeight[i];
    sort(aHeight.begin(), aHeight.end());
    sort(bHeight.begin(), bHeight.end());

    int ans = 0, check = 500005;
    //h가 작기때문에 모든 경우를 다 시도해본다.
    for (int i = 1; i <= h; ++i) {
        //석순의 경우 i높이보다 큰 친구들은 모두 부딪히게 된다.
        int cnt = n / 2 - (lower_bound(aHeight.begin(), aHeight.end(), i) - aHeight.begin());
        //종유석의 경우 h-i+1보다 큰 친구들은 모두 부딪힌다. (0 ~ 종유석의 길이를 h에서 뺀 높이 사이면 안부딪히고 그 이상이면 부딪힌다)
        cnt += n / 2 - (lower_bound(bHeight.begin(), bHeight.end(), h - i + 1) - bHeight.begin());
        if (cnt < check) {              //만약 지금까지 최소라고 생각했던 것보다 더 조금 부딪힌다면
            check = cnt;                //갱신해주고
            ans = 1;                    //그러한 구간은 1개 존재한다(현재까지)
        }
        else if (cnt == check) ans++;           //만약 앞서 구한 횟수와 동일하다면 구간의 수를 증가시켜준다.
    }
    cout << check << " " << ans;
}