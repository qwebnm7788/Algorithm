#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main() {
	ios_base::sync_with_stdio(false);
	int t;
	cin >> t;

	int n;
	cin >> n;
	vector<int> A(n);
	for (int i = 0; i < n; ++i)	cin >> A[i];

	int m;
	cin >> m;
	vector<int> B(m);
	for (int i = 0; i < m; ++i) cin >> B[i];

	int temp;
	vector<int> pA;
	for (int i = 0; i < n; ++i) {
		pA.push_back(A[i]);
		temp = A[i];
		for (int j = i + 1; j < n; ++j) {
			temp += A[j];
			pA.push_back(temp);
		}
	}

	vector<int> pB;
	for (int i = 0; i < m; ++i) {
		pB.push_back(B[i]);
		temp = B[i];
		for (int j = i + 1; j < m; ++j) {
			temp += B[j];
			pB.push_back(temp);
		}
	}

	sort(pA.begin(), pA.end());
	sort(pB.begin(), pB.end());

	int aSize = pA.size(), bSize = pB.size();
	long long answer = 0;

	for (int i = 0; i < aSize; ++i) {
		answer += upper_bound(pB.begin(), pB.end(), t - pA[i]) - lower_bound(pB.begin(), pB.end(), t - pA[i]);
	}
	cout << answer;
}