#include <iostream>
#include <cstring>
#include <algorithm>
using namespace std;

const int MAXN = 21;

int memo[MAXN][MAXN][MAXN];

int foo(int a, int b, int c) {
	if (a <= 0 || b <= 0 || c <= 0) return 1;
	if (a > 20 || b > 20 || c > 20) return foo(20, 20, 20);
	int& ret = memo[a][b][c];
	if (ret != -1) return ret;
	if (a < b && b < c) return ret = foo(a, b, c - 1) + foo(a, b - 1, c - 1) - foo(a, b - 1, c);
	return ret = foo(a - 1, b, c) + foo(a - 1, b - 1, c) + foo(a - 1, b, c - 1) - foo(a - 1, b - 1, c - 1);
}
int main() {
	int a, b, c;
	memset(memo, -1, sizeof(memo));
	while (cin >> a >> b >> c) {
		if (a == -1 && b == -1 && c == -1) break;
		cout << "w(" << a << ", " << b << ", " << c << ") = " << foo(a, b, c) << endl;
	}
}