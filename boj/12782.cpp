/*
12782번 비트 우정지수
(E)

우선 두 수에 대해서 각각 1의 갯수를 세준다. (0의 갯수는 두 수의 길이가 동일하므로 len-1의개수로 알 수 있다.)
또한 두 수에 대해 서로 다른값을 가지는 자리의 수(x) 를 세준다.

두 수에 대해 1의 개수가 다르다면 1번 연산을 통해서
갯수를 우선 맞춰주는데 이때 0->1이나 1->0으로 교환하는 자리는
그 교환으로 인해서 두 수의 그 자리는 이제 동일한 비트수가 되도록 하자. 그렇다면 x-(1번연산의 수)만큼의 자리는 배치만 잘못되었을 뿐이 된다.

따라서 0인 친구와 1인 친구를 서로 2번 연산을 통해 자리를 교환한다면 2자리가 동시에 제위치를 찾아들어가므로
(x-(1번연산의수)) / 2번의 2번 연산으로 모두 제위치를 찾을 수 있게된다.
*/
#include <iostream>
#include <string>
using namespace std;

int main() {
	freopen("input.txt", "r", stdin);
	int test;
	cin >> test;
	while (test--) {
		string n, m;
		cin >> n >> m;
		int len = n.length();

		int a = 0, b = 0, ans = 0;
		for (int i = 0; i < len; ++i) {
			if (n[i] == '1') a++;
			if (m[i] == '1') b++;
		}
		ans = (a >= b ? a - b : b - a);
		int diff = 0;
		for (int i = 0; i < len; ++i) {
			if (n[i] != m[i]) diff++;
		}
		diff -= ans;
		ans += diff / 2;
		cout << ans << endl;
	}
}