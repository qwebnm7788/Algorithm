#include <iostream>
#include <algorithm>
using namespace std;

int main() {
	int n, m, k;
	cin >> n >> m >> k;

	int answer = min(n/2, m);
	int temp = 0;
	if (k >= n - answer * 2) {
		k -= n - answer * 2;
	}
	else {
		k = 0;
	}

	if (k >= m - answer) {
		k -= m - answer;
	}
	else {
		k = 0;
	}

	while (k > 0) {
		k -= 3;
		answer--;
	}
	cout << answer;
}