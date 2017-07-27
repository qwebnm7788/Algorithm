//
// Created by jaewon on 2017-06-28.
//
#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <queue>
#include <cmath>
using namespace std;

const int MAXSIZE = 10005;
vector<bool> isPrime(MAXSIZE,true);

void getPrime(){
    isPrime[1] = false;
    for(int i = 2; i < MAXSIZE; ++i) {
        for(int j = i*2; j < MAXSIZE; j += i){
            isPrime[j] = false;
        }
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    freopen("input.txt","r",stdin);
    getPrime();
    int test;
    cin >> test;
    while (test--) {
        string a,b;
        cin >> a >> b;

        vector<bool> visited(MAXSIZE,false);
        queue<string> q;
        visited[stoi(a)] = true;
        q.push(a);
        int level = 0, size = 0;
        string temp;
        bool check = false;
        while(!q.empty()){
            size = q.size();
            for(int i = 0; i < size; ++i){
                string here = q.front();
                q.pop();
                if(here == b){
                    check = true;
                    break;
                }
                temp = here;
                for(int j = 1; j <= 9; ++j) {
                    if(here[0] == j) continue;
                    temp[0] = j + '0';
                    if(isPrime[stoi(temp)] && !visited[stoi(temp)]){
                        visited[stoi(temp)] = true;
                        q.push(temp);
                    }
                }
                temp = here;
                for(int j = 0; j <= 9; ++j){
                    if(here[1] == j) continue;
                    temp[1] = j + '0';
                    if(isPrime[stoi(temp)] && !visited[stoi(temp)]){
                        visited[stoi(temp)] = true;
                        q.push(temp);
                    }
                }
                temp = here;
                for(int j = 0; j <= 9; ++j){
                    if(here[2] == j) continue;
                    temp[2] = j + '0';
                    if(isPrime[stoi(temp)] && !visited[stoi(temp)]){
                        visited[stoi(temp)] = true;
                        q.push(temp);
                    }
                }
                temp = here;
                for(int j = 0; j <= 9; ++j){
                    if(here[3] == j) continue;
                    temp[3] = j + '0';
                    if(isPrime[stoi(temp)] && !visited[stoi(temp)]){
                        visited[stoi(temp)] = true;
                        q.push(temp);
                    }
                }
            }
            if(check) break;
            level++;
        }

        if(check) cout << level << endl;
        else cout << "Impossible\n";
    }
}



