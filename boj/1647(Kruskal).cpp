#include <iostream>
using namespace std;

int main() {
	int n;
	cin >> n;
	
	int arr[101];
	for (int i = 1; i <= n; ++i) {
		cin >> arr[i];
	}
	if (n == 1) {
		if (arr[1] == 0)
			cout << "NO\n";
		else {
			cout << "YES\n";
			cout << "1 1";
		}
		return 0;
	}
	int l = 1;
	int sum = arr[1];
	int k = 0;
	pair<int, int> ans[101];
	for (int i = l + 1; i <= n; ++i) {
		if (sum + arr[i] == 0) {
			if (sum == 0) {
				cout << "NO";
				return 0;
			}
			ans[k].first = l;
			ans[k].second = i - 1;
			l = i;
			sum = arr[i];
			k++;
		}
		if (i == n) {
			ans[k].first = l;
			ans[k].second = i;
			k++;
		}
		sum += arr[i];
	}
	if (k == 0)
		cout << "NO";
	else {
		cout << "YES\n";
		cout << k << endl;
		for (int i = 0; i < k; ++i) {
			cout << ans[i].first << " " << ans[i].second << endl;
		}
	}
	
}