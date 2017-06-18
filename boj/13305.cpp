/*
13305 주유소
왼쪽 -> 오른쪽으로 살펴보며 현재까지의 가장 작은 리터당 가격으로 값을 누적한다. (그리디)
*/
#include <iostream>
#include <limits>
#include <vector>
#include <algorithm>
using namespace std;

const long long INF = numeric_limits<long long>::max();

int main() {
	int n;
	cin >> n;

	vector<long long> city(n);
	vector<long long> road(n - 1);
	for (int i = 0; i < n - 1; ++i) cin >> road[i];
	for (int i = 0; i < n; ++i) cin >> city[i];

	long long ans = 0, minVal = INF;
	for (int i = 0; i < n - 1; ++i) {
		minVal = min(minVal, city[i]);
		ans += minVal*road[i];
	}

	cout << ans;
}