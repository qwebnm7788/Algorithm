#include <iostream>
#include <string>
#include <vector>
using namespace std;

int solution(string N) {
    int answer = 0;
    int len = N.length();

    vector<int> cnt(10, 0);
    for (int i = 0; i < len; ++i) cnt[N[i] - '0']++;

    int ret = 0;
    int save = cnt[0] - (cnt[0]%2);
    bool check = (cnt[0] < 2 ? true : false);
    for(int i = 0; i < 10; ++i){
        ret += cnt[i];
        ret -= cnt[i]%2;
        if(i != 0 && cnt[i] > 1) check = true;
        cnt[i] = cnt[i]%2;
    }

    for(int i = 0; i < 10; ++i){
        if(cnt[i]){
            ret++;
            break;
        }
    }

    if(!check){
        ret -= (save);
    }

    return ret;
}

int main(){
    string x;
    cin >> x;
    cout << solution(x);
}