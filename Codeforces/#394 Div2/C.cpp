/*
arr[i][j=0~2] = i번 문자열의 각 대응되는 문자로 가는 최소 횟수를 저장한다. (0=digit, 1=english, 2=sepcial case)

그 후 모든 친구들을 시도해보면서 그 때 드는 비용의 최소값을 출력해주면 된다.
-> dp를 적용할수 있을꺼야...?
모든 시도 가능한 조합은 3^n이고 
*/
#include <iostream>
#include <vector>
#include <string>
#include <limits>
#include <algorithm>
using namespace std;

const int INF = 987654321;

int n, m;
vector<vector<int>> arr;
vector<bool> check;
vector<bool> checkArr;
//arr[x][y] 를 고름으로써 valid password를 만들기 위한 최소한의 움직임을 반환한다.
int foo(int x, int y) {
	for (int i = 0; i < 3; ++i) {
		if (!check[i])
			break;
		if (i == 2)
			return arr[x][y];
	}
	int ret = arr[x][y];
	int temp = INF;
	for (int i = 0; i < n; ++i) {
		if (i == x)
			continue;
		for (int j = 0; j < 3; ++j) {
			if (!checkArr[i] && !check[j]) {
				check[j] = true;
				checkArr[i] = true;
				temp = min(temp, foo(i, j));
				check[j] = false;
				checkArr[i] = false;
			}
		}
	}
	return ret + temp;
}
int main() {
	freopen("input.txt", "r", stdin);
	cin >> n >> m;

	arr.resize(n);
	check.resize(3);
	checkArr.resize(n);

	for (int i = 0; i < n; ++i)
		arr[i] = vector<int>(3,INF);
	//0 = digit 1 = lower 2 = special
	string temp;
	for (int i = 0; i < n; ++i) {
		cin >> temp;
		for (int j = 0; j < m; ++j) {
			if (temp[j] >= '0' && temp[j] <= '9')
				arr[i][0] = min(arr[i][0], j);
			else if (temp[j] >= 'a' && temp[j] <= 'z')
				arr[i][1] = min(arr[i][1], j);
			else
				arr[i][2] = min(arr[i][2], j);
		}
		for (int j = m - 1; j >= 0; --j) {
			if (temp[j] >= '0' && temp[j] <= '9')
				arr[i][0] = min(arr[i][0], (m - 1) - j + 1);
			else if (temp[j] >= 'a' && temp[j] <= 'z')
				arr[i][1] = min(arr[i][1], (m - 1) - j + 1);
			else
				arr[i][2] = min(arr[i][2], (m - 1) - j + 1);
		}
	}

	//모든 친구들에 대해서 0~2를 시도해보면서 제일 조금 움직이는 친구를찾는거야!
	//foo(int i, int j) = arr[i][j]번 친구를 고름으로써 valid password를 만들 수 있는 최소의 움직임의 수를 반환한다.
	int ans = INF;
	for (int i = 0; i < n; ++i) {
		for (int j = 0; j < 3; ++j) {
			checkArr[i] = true;
			check[j] = true;
			ans = min(ans, foo(i, j));
			check[j] = false;
			checkArr[i] = false;
		}
	}
	cout << ans;
}