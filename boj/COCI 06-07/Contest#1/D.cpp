/*
BFS로 탐색을 진행하면 된다.

물을 먼저 진행시켜야지 고슴도치가 다음 물이 진행할 곳에 가지 못하는 효과를 줄 수 있다.

시간복잡도는 BFS의 시간복잡도가 지배하는데 O(|V|+|E|)에서 약 O(|N|^2)이된다. 
*/


#include <iostream>
#include <queue>
#include <algorithm>
using namespace std;

char arr[51][51];
bool visited[51][51];
int r, c;
void water_flow() {
	queue<pair<int, int>> q;
	for (int i = 0; i < r; ++i) {
		for (int j = 0; j < c; ++j) {
			if (arr[i][j] == '*')
				q.push(make_pair(i, j));
		}
	}

	while (!q.empty()) {
		int row = q.front().first;
		int col = q.front().second;
		q.pop();

		if (row > 0 && arr[row - 1][col] == '.')
			arr[row - 1][col] = '*';
		if (row < r - 1 && arr[row + 1][col] == '.')
			arr[row + 1][col] = '*';
		if (col > 0 && arr[row][col - 1] == '.')
			arr[row][col - 1] = '*';
		if (col < c - 1 && arr[row][col + 1] == '.')
			arr[row][col + 1] = '*';
	}
}
int main() {
	freopen("input.txt", "r", stdin);
	ios_base::sync_with_stdio(false);
	cin >> r >> c;
	
	int sr, sc;
	int er, ec;

	for (int i = 0; i < r; ++i) {
		for (int j = 0; j < c; ++j) {
			cin >> arr[i][j];
			if (arr[i][j] == 'S') {
				sr = i;
				sc = j;
			}
			else if (arr[i][j] == 'D') {
				er = i;
				ec = j;
			}
		}
	}

	queue<pair<int, int>> q;
	visited[sr][sc] = true;
	q.push(make_pair(sr, sc));
	int size = 0;
	int dist = 0;
	while (!q.empty()) {
		size = q.size();

		water_flow();

		for (int z = 0; z < size; ++z) {
			int cr = q.front().first;
			int cc = q.front().second;
			q.pop();


			if (cr > 0 && (arr[cr - 1][cc] != 'X' && arr[cr - 1][cc] != '*')) {
				if (!visited[cr - 1][cc]) {
					visited[cr - 1][cc] = true;
					q.push(make_pair(cr - 1, cc));
				}
			}
			if (cr < r - 1 && (arr[cr + 1][cc] != 'X' && arr[cr + 1][cc] != '*')) {
				if (!visited[cr + 1][cc]) {
					visited[cr + 1][cc] = true;
					q.push(make_pair(cr + 1, cc));
				}
			}
			if (cc > 0 && (arr[cr][cc - 1] != 'X' && arr[cr][cc - 1] != '*')) {
				if (!visited[cr][cc - 1]) {
					visited[cr][cc - 1] = true;
					q.push(make_pair(cr, cc - 1));
				}
			}
			if (cc < c - 1 && (arr[cr][cc + 1] != 'X' && arr[cr][cc + 1] != '*')) {
				if (!visited[cr][cc + 1]) {
					visited[cr][cc + 1] = true;
					q.push(make_pair(cr, cc + 1));
				}
			}

		}
		dist++;
		if (visited[er][ec])
			break;
	}

	if (visited[er][ec])
		printf("%d", dist);
	else
		printf("KAKTUS");
}
