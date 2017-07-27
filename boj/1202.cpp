//
// Created by jaewon on 2017-07-22.
//
#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
using namespace std;

int main() {
    int n, k;
    cin >> n >> k;

    vector<pair<int, int>> jewel(n);
    for (int i = 0; i < n; ++i) cin >> jewel[i].first >> jewel[i].second;

    vector<int> bag(k);
    for (int i = 0; i < k; ++i) cin >> bag[i];

    sort(bag.begin(), bag.end());
    sort(jewel.begin(), jewel.end());

    priority_queue<int> pq;
    long long answer = 0;
    int current = 0;
    int i;
    for (i = 0; i < n;) {
        if (jewel[i].first <= bag[current]) {
            pq.push(jewel[i].second);
            i++;
        }
        else {
            if (!pq.empty()) {
                answer += pq.top();
                pq.pop();
            }
            current++;
            if (current >= k) break;
        }
    }
    for (; current < k; ++current) {
        if (!pq.empty()) {
            answer += pq.top();
            pq.pop();
        }
        else {
            break;
        }
    }
    cout << answer;
}
