#include <iostream>
#include <cstring>
#include <iomanip>
#include <algorithm>
using namespace std;

const int MAXN = 201;
const int MOD = 100000;

long long memo[MAXN][MAXN];
char target[MAXN];
bool check = false;

long long foo(int left, int right) {
	if (left > right) return 1;
	if ((right - left + 1) % 2) return 0;

	long long& ret = memo[left][right];
	if (ret != -1) return ret;
	ret = 0;
	long long temp = 0;
	if (target[left] == '(') {
		for (int k = left + 1; k <= right; k += 2) {
			if (target[k] == ')' || target[k] == '?') {
				temp = foo(left + 1, k - 1) * foo(k + 1, right);
				if (temp >= MOD) {
					check = true;
					temp %= MOD;
				}
				ret += temp;
			}
		}
	}else if (target[left] == '{') {
		for (int k = left + 1; k <= right; k += 2) {
			if (target[k] == '}' || target[k] == '?') {
				temp = foo(left + 1, k - 1) * foo(k + 1, right);
				if (temp >= MOD) {
					check = true;
					temp %= MOD;
				}
				ret += temp;
			}
		}
	}else if (target[left] == '[') {
		for (int k = left + 1; k <= right; k += 2) {
			if (target[k] == ']' || target[k] == '?') {
				temp = foo(left + 1, k - 1) * foo(k + 1, right);
				if (temp >= MOD) {
					check = true;
					temp %= MOD;
				}
				ret += temp;
			}
		}
	}else if (target[left] == '?') {
		for (int k = left + 1; k <= right; k += 2) {
			if (target[k] == '?') {
				temp = 3 * foo(left + 1, k - 1)*foo(k + 1, right);
				if (temp >= MOD) {
					check = true;
					temp %= MOD;
				}
				ret += temp;
			}
			else if (target[k] == ')' || target[k] == ']' || target[k] == '}') {
				temp = foo(left + 1, k - 1)*foo(k + 1, right);
				if (temp >= MOD) {
					check = true;
					temp %= MOD;
				}
				ret += temp;
			}
		}
	}
	ret %= MOD;
	return ret;
}

int main() {
	int len;
	cin >> len;

	char in;
	for (int i = 0; i < len; ++i) {
		cin >> target[i];
	}

	memset(memo, -1, sizeof(memo));
	int answer = foo(0, len - 1);
	if (check) {
		cout << setw(5) << setfill('0') << answer;
	}
	else {
		cout << answer;
	}
}