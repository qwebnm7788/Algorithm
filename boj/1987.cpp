/*
1987 알파벳

4방향을 보면서 visited를 관리해주며 가능한 경로의 수를 모두 계산해주면 된다.
한번 방문후 종료하면서 visited를 다시 초기화시켜주는 과정이 필요하다.

*/
#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;

const int MAXN = 21;
const int ALPHA = 26;
const int dx[4] = { -1,0,1,0 };
const int dy[4] = { 0,1,0,-1 };

char arr[MAXN][MAXN];
int r, c;

//[row][col]점에서 지금까지 visited의 알파벳을 방문하였을때 최대로 이동할수 있는 거리를 반환한다.
int foo(vector<bool>& visited, int row, int col) {
	//at least this one 
	int ret = 1;
	visited[arr[row][col] - 'A'] = true;

	//check 4 direction
	for (int i = 0; i < 4; ++i) {
		int nextRow = row + dx[i];
		int nextCol = col + dy[i];
		if (nextRow >= 0 && nextRow < r && nextCol >= 0 && nextCol < c) {
			if(!visited[arr[nextRow][nextCol]-'A'])
				ret = max(ret, foo(visited, nextRow, nextCol) + 1);
		}
	}
	visited[arr[row][col]-'A'] = false;
	return ret;
}

int main() {
	freopen("input.txt", "r", stdin);

	cin >> r >> c;
	for (int i = 0; i < r; ++i) {
		for (int j = 0; j < c; ++j)
			cin >> arr[i][j];
	}
	
	int ans = 0;
	vector<bool> visited(ALPHA, false);
	cout << foo(visited, 0, 0);
}