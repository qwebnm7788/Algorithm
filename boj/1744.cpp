#include <iostream>
#include <deque>
#include <algorithm>

using namespace std;

int main(){
    ios_base::sync_with_stdio(false);
    freopen("input.txt","r",stdin);
    int n;
    cin >> n;

    deque<int> negative, positive;
    int zero = 0, in;

    for(int i = 0; i < n; ++i){
        cin >> in;
        if(in > 0) positive.push_back(in);
        else if(in == 0) zero++;
        else negative.push_back(in);
    }

    sort(negative.begin(),negative.end());
    sort(positive.begin(),positive.end());


    //만약 음수가 짝수개라면 0이랑 곱하지 않아야 좋다. (-10 * -20 = 200이 되므로)
    if(zero > 0 && (negative.size() > 0 && negative.size() % 2 != 0)){
        negative.pop_back();
    }

    long long answer = 0, size;
    //음수계산
    size = negative.size();
    int i;
    for(i = 0; i < size - 1; i += 2){
        answer += (negative[i] * negative[i+1]);
    }
    if((size % 2) != 0) answer += negative[size-1];

    //양수계산
    size = positive.size();
    for(i = size - 1; i >= 1; i -= 2){
        if(positive[i] == 1 || positive[i-1] == 1) answer += positive[i] + positive[i-1];
        else answer += positive[i] * positive[i-1];
    }
    if((size % 2) != 0) answer += positive[0];

    cout << answer;
}