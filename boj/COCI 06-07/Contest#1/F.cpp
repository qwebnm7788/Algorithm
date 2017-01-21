/*
COCI 2006/2007 
3057 Debug

그냥 문제에서 요구하는대로 짜주면 풀린다.;;
시간제한이 넉넉해서 그런듯

그런데 공식 솔루션에는 좀더 최적화하는 방법이 있는데 뭔지 잘 모르겠다 dp랑 전처리를 좀 하면 되는듯;

시간을 조금 단축시키는 방법은 가능한 가장 큰 직사각형부터 킬러를 찾는것이다.
min(r,c)가 가장 크겠죠?

그리고 나서 180도니깐 왼쪽 위와 오른쪽 아래를 비교해 주면서 체크해주면 된다.

정사각형의 크기가 1보다 크니깐 최소 2까지만임을 주의하자.
찾고서 바로 종료시키면 좀 더 빠르게 끝나겠지?

그러면 배열의 최대 크기는 r^2까지이다. (r=300) 
check 함수의 시간복잡도는 만약 정가운데 친구 하나만 다른 경우가 최악의 경우가 되고
이때는 [row~row+size][col~col+size]를 모두 검사하니깐 O(size^2)이 된다.

즉 모든 배열의 원소에 대해서 check를 해주니깐 최악의 경우 O(r^4)이 될텐데 생각한만큼 꽉 채워서 4제곱이 될꺼같지는 않다. (킬러의 사이즈가 크면 check도 오래걸리지만 작으면 작아진다.)
r = 최대 300이므로 r^4은 81*10e8이 되어서 약 1초를 조금 넘는 시간이 걸리지 않을까.?
*/
#include <stdio.h>
#include <vector>
#include <algorithm>
using namespace std;

bool check(vector<vector<char>>& arr, int row, int col, int size) {
	int rR = row + size - 1;
	int rC = col + size - 1;
	for (int i = 0; i < size / 2; ++i) {
		for (int j = 0; j < size; ++j) {
			if (arr[row + i][col + j] != arr[rR - i][rC - j])
				return false;
		}
	}
	return true;
}
int main() {
	freopen("input.txt", "r", stdin);
	int r, c;
	scanf("%d %d", &r, &c);
	getchar();

	vector<vector<char>> arr(r);
	for (int i = 0; i < r; ++i)
		arr[i] = vector<char>(c);

	for (int i = 0; i < r; ++i) {
		for (int j = 0; j < c; ++j) {
			scanf("%c", &arr[i][j]);
		}
		getchar();
	}

	int n = min(r, c);
	int ans = -1;
	bool ret = false;
	for (int i = n; i >= 2; --i) {
		for (int j = 0; j <= r-i; ++j) {
			for (int k = 0; k <= c-i; ++k) {
				if (check(arr, j, k, i)){
					ans = i;
					ret = true;
					break;
				}
			}
			if (ret)
				break;
		}
		if (ret)
			break;
	}
	printf("%d", ans);
}