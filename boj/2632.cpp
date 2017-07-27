#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main() {
	ios_base::sync_with_stdio(false);
	int target;
	cin >> target;

	int m, n;
	cin >> m >> n;

	vector<int> A(m), B(n);

	for (int i = 0; i < m; ++i) cin >> A[i];
	for (int i = 0; i < n; ++i) cin >> B[i];

	vector<int> pA,pB;
	int temp;

	for (int i = 0; i < m; ++i) {
		temp = A[i];
		pA.push_back(A[i]);
		for (int j = i + 1; j < m; ++j) {
			temp += A[j];
			pA.push_back(temp);
		}
	}

	for (int i = m - 1; i > 0; --i) {
		temp = A[i];
		for (int j = i + 1; j < m; ++j)
			temp += A[j];
		for (int j = 0; j < i - 1; j++) {
			temp += A[j];
			pA.push_back(temp);
		}
	}

	for (int i = 0; i < n; ++i) {
		temp = B[i];
		pB.push_back(B[i]);
		for (int j = i + 1; j < n; ++j) {
			temp += B[j];
			pB.push_back(temp);
		}
	}

	for (int i = n - 1; i > 0; --i) {
		temp = B[i];
		for (int j = i + 1; j < n; ++j)
			temp += B[j];
		for (int j = 0; j < i - 1; j++) {
			temp += B[j];
			pB.push_back(temp);
		}
	}

	sort(pA.begin(), pA.end());
	sort(pB.begin(), pB.end());

	int aSize = pA.size(), bSize = pB.size();
	long long answer = 0;

	for (int i = 0; i < aSize; ++i) {
		if (pA[i] == target) answer++;
	}
	for (int i = 0; i < bSize; ++i) {
		if (pB[i] == target) answer++;
	}

	for (int i = 0; i < aSize; ++i) {
		if(target > pA[i])
			answer += upper_bound(pB.begin(), pB.end(), target - pA[i]) - lower_bound(pB.begin(), pB.end(), target - pA[i]);
	}

	cout << answer;
}