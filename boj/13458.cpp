#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main() {
	ios_base::sync_with_stdio(false);
	int n;
	cin >> n;

	vector<int> A(n);
	for (int i = 0; i < n; ++i) cin >> A[i];

	int b, c;
	cin >> b >> c;

	long long answer = n;
	for (int i = 0; i < n; ++i) A[i] -= b;

	for (int i = 0; i < n; ++i) {
		if (A[i] > 0) {
			answer += A[i] / c + (A[i] % c ? 1 : 0);
		}
	}

	cout << answer;
}