/*
1654 랜선자르기

x길이로 잘랐을때 얻을 수 있는 랜선의 수는 length[i] / x와 같다.

이분탐색으로 이러한 x중 조건을 만족하는 가장 큰 수를 출력하면 된다.
*/

#include <iostream>
#include <vector>
using namespace std;

int main() {
	int k, n;
	cin >> k >> n;

	long long lo = 1, hi = 1;
	
	vector<long long> length(k);
	for (int i = 0; i < k; ++i) {
		cin >> length[i];
		if (length[i] > hi) hi = length[i];
	}
	
	hi += 5;
	while (lo + 1 < hi) {
		int mid = (lo + hi) / 2;
		long long sum = 0;
		for (int i = 0; i < k; ++i) sum += (length[i] / mid);
		if (sum >= n) lo = mid;
		else hi = mid;
	}
	cout << lo;
}
