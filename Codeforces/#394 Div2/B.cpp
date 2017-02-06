/*
Kefa친구를 모든 칸에서 다 시도해 보면서
Sasha또한 그것에 대응되도록 모든칸에서 시도해 본다.

시간복잡도는 O(nl^2)이 된다.
*/
#include <iostream>
#include <vector>
using namespace std;

int main() {
	int n, l;
	cin >> n >> l;

	vector<int> Kefa(n);
	for (int i = 0; i < n; ++i)
		cin >> Kefa[i];

	vector<int> Sasha(n);
	for (int i = 0; i < n; ++i)
		cin >> Sasha[i];

	bool ans = false;
	for (int i = 0; i < l; ++i) {
		vector<bool> check(l, false);
		for (int j = 0; j < n; ++j)
			check[(i+Kefa[j])%l] = true;
		for (int j = 0; j < l; ++j) {
			for (int k = 0; k < n; ++k) {
				if (!check[(j + Sasha[k]) % l])
					break;
				if (k == n - 1)
					ans = true;
			}
			if (ans)
				break;
		}
		if (ans)
			break;
	}
	if (ans)
		cout << "YES";
	else
		cout << "NO";
}