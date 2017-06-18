/*
1252 이진수 덧셈

문자열로 입력받은 두 이진수를 더해주면 된다.

carry를 유지하면서 모든 경우에 덧셈을 진행하면 되는데
우선 i번째 자리의 덧셈에서 a[i] + b[i] + carry의 가능성은
0,1,2,3의 세가지가 있다(3도 존재함에 주의하자)

1. 0이라면 c[i] = 0이고 carry = 0이 된다.
2. 1이라면 c[i] = 1, carry = 0
3. 2이라면 c[i] = 0, carry = 1
4. 3이라면 c[i] = 1, carry = 1 이 된다.

만약 최상위 비트에서 carry가 발생한다면 한자리를 늘려주어야 한다.

또한 문제에서 요구하는 출력은 앞에 leading 0는 제외하고 출력해야 한다. (0인 경우는 제외)
*/
#include <iostream>
#include <string>
#include <algorithm>
using namespace std;

int main() {
	freopen("input.txt", "r", stdin);
	string a, b, c;
	cin >> a >> b;

	if (a.length() != b.length()) {
		if (a.length() > b.length())
			b = string(a.length() - b.length(), '0') + b;
		else
			a = string(b.length() - a.length(), '0') + a;
	}

	c = string(a.length(), '0');

	char carry = '0';
	for (int i = a.length() - 1; i >= 0; --i) {
		int sum = (a[i] - '0') + (b[i] - '0') + (carry - '0');
		if (sum == 1) {
			c[i] = '1';
			carry = '0';
		}
		else if (sum == 2) {
			c[i] = '0';
			carry = '1';
		}
		else if (sum == 3) {
			c[i] = '1';
			carry = '1';
		}
		else {
			c[i] = '0';
			carry = '0';
		}
	}
	if (carry == '1') c = "1" + c;
	int ans = -1;
	for (int i = 0; i < c.length() - 1; i++){
		if (c[i] == '0') ans = i;
		else break;
	}
	if (ans == -1) cout << c;
	else cout << c.substr(ans + 1);
}