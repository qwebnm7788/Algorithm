//
// Created by jaewon on 2017-06-16.
//
#include <iostream>
#include <algorithm>
#include <vector>
#include <queue>

using namespace std;

const int MAX = 5000005;

vector<int> prime;
vector<bool> isPrime(MAX,true);
vector<bool> checker(MAX,false);

void slave(){
    for(int i = 2; i <= MAX; ++i){
        if(isPrime[i]){
            prime.push_back(i);
            for(int j = i*2; j <= MAX; j += i) isPrime[j] = false;
        }
    }
}

int main(){
    ios_base::sync_with_stdio(false);
    freopen("input.txt","r",stdin);
    int n;
    cin >> n;

    slave();
    long long aRes = 0, bRes = 0;
    priority_queue<int> aPq, bPq;
    int tmp_first,tmp_second;
    for(int i = 0; i < n; ++i){
        int a,b;
        cin >> a >> b;
        if(isPrime[a]){             //A가 말한것이 소수라면
            if(checker[a]){         //이미 말한 소수를 말하면
                aRes -= 1000;
            }else{                  //아니면 리스트에 추가한다.
                aPq.push(a);
                checker[a] = true;
            }
        }else{                      //A가 말한것이 소수가 아니라면
            if(bPq.size() < 3){
                bRes += 1000;
            }else{
                tmp_first = bPq.top();
                bPq.pop();
                tmp_second = bPq.top();
                bPq.pop();
                bRes += bPq.top();
                bPq.push(tmp_first);
                bPq.push(tmp_second);
            }
        }

        if(isPrime[b]){
          if(checker[b]){
              bRes -= 1000;
          }else{
              bPq.push(b);
              checker[b] = true;
          }
        }else{
            if(aPq.size() < 3){
                aRes += 1000;
            }else{
                tmp_first = aPq.top();
                aPq.pop();
                tmp_second = aPq.top();
                aPq.pop();
                aRes += aPq.top();
                aPq.push(tmp_first);
                aPq.push(tmp_second);
            }
        }
    }
    if(aRes > bRes) cout << "소수의 신 갓대웅";
    else if(aRes < bRes) cout << "소수 마스터 갓규성";
    else cout << "우열을 가릴 수 없음";
}

