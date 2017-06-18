/*
14503번 로봇청소기

구현문제 -> (3 + direction)%4 + i가 다음번의 방향임을 이용한다.
*/
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

const int dr[4][4] = { {0,1,0,-1},{-1,0,1,0},{0,-1,0,1},{1,0,-1,0} };
const int dc[4][4] = { {-1,0,1,0},{0,-1,0,1}, {1,0,-1,0}, {0,1,0,-1 } };

int main() {
	ios_base::sync_with_stdio(false);
	int n,m;
	cin >> n >> m;

	int row, col, direction;
	cin >> row >> col >> direction;

	vector<vector<char>> matrix(n, vector<char>(m));
	vector<vector<bool>> visited(n, vector<bool>(m));

	for (int i = 0; i < n; ++i)
		for (int j = 0; j < m; ++j)
			cin >> matrix[i][j];

	int ans = 1;
	visited[row][col] = true;
	bool found = false;


	while (true) {
		found = false;
		for (int i = 0; i < 4; ++i) {
			int nextRow = row + dr[direction][i];
			int nextCol = col + dc[direction][i];
			int nextDirection = ((3 + direction) % 4 - i < 0 ? (3+direction)%4 - i + 4 : (3 + direction) % 4 - i);
			if (nextRow < 0 || nextRow >= n || nextCol < 0 || nextCol >= m || visited[nextRow][nextCol] || matrix[nextRow][nextCol] == '1') continue;
			row = nextRow;
			col = nextCol;
			direction = nextDirection;
			ans++;
			visited[row][col] = true;
			found = true;
			break;
		}

		if (!found) {
			if (row+dr[direction][1] < 0 || row+dr[direction][1] >=n || col + dc[direction][1] < 0 || col + dc[direction][1] >= m || matrix[row + dr[direction][1]][col + dc[direction][1]] == '1') break;
			else {
				row += dr[direction][1];
				col += dc[direction][1];
			}
		}
	}
	cout << ans;
}