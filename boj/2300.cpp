#include <iostream>
#include <cstdio>
#include <vector>
#include <cmath>
#include <cstring>
#include <algorithm>
using namespace std;

const int INF = 1e9;
const int MAXN = 1e4 + 1;

int memo[MAXN];

int main() {
	ios_base::sync_with_stdio(false);
	int n;
	cin >> n;

	vector<pair<int, int>> building(n);
	for (int i = 0; i < n; ++i) {
		cin >> building[i].first >> building[i].second;
		if (building[i].second < 0) building[i].second *= -1;
	}

	sort(building.begin(), building.end());

	int maxHeight;
	memo[0] = building[0].second * 2;
	for (int i = 1; i < n; ++i) {
		memo[i] = INF;
		maxHeight = building[i].second;
		for (int j = i; j >= 0; --j) {
			if (maxHeight < building[j].second) {
				maxHeight = building[j].second;
			}
			memo[i] = min(memo[i], memo[j - 1] + max(building[i].first - building[j].first, maxHeight * 2));
		}
	}
	cout << memo[n - 1];
}