#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

const int dr[8] = { -1,-1,-1,0,1,1,1,0 };
const int dc[8] = { -1,0,1,1,1,0,-1,-1 };

int main() {
	ios_base::sync_with_stdio(false);
	int n;
	cin >> n;

	vector<vector<char>> adj(n, vector<char>(n));
	for (int i = 0; i < n; ++i) {
		for (int j = 0; j < n; ++j) {
			cin >> adj[i][j];
		}
	}

	int cnt, answer = 0;
	bool finish;
	while (true) {
		finish = true;
		for (int i = 0; i < n; ++i) {
			if (adj[0][i] != '0' || adj[n - 1][i] != '0' || adj[i][n - 1] != '0' || adj[i][0] != '0') finish = false;
		}
		if(finish) break;
		cnt = 0;
		for (int i = 0; i < 4; ++i) {
			for (int j = 0; j < n; ++j) {
				int row, col;
				if (i == 0) {
					row = 0;
					col = j;
				}
				else if (i == 1) {
					row = j;
					col = n - 1;
					if (row == 0) continue;
				}
				else if (i == 2) {
					row = n - 1;
					col = n - 1 - j;
					if (col == n - 1) continue;
				}
				else {
					row = j;
					col = 0;
					if (row == 0 || row == n - 1) continue;
				}
				cnt = 0;
				if (adj[row][col] - '0' == 0) {
					for (int z = 0; z < 8; ++z) {
						int nR = row + dr[z];
						int nC = col + dc[z];
						if (nR < 0 || nR >= n || nC < 0 || nC >= n) continue;
						if (adj[nR][nC] == '#') adj[nR][nC] = '.';
					}
				}
				else {
					int foundRow, foundCol;
					for (int z = 0; z < 8; ++z) {
						int nR = row + dr[z];
						int nC = col + dc[z];
						if (nR < 0 || nR >= n || nC < 0 || nC >= n) continue;
						if (adj[nR][nC] == '#') {
							foundRow = nR;
							foundCol = nC;
							cnt++;
						}
					}
					if (cnt == 1 && adj[row][col] - '0' == 1) {
						answer++;
						adj[foundRow][foundCol] = '.';
						for (int z = 0; z < 8; ++z) {
							int nR = foundRow + dr[z];
							int nC = foundCol + dc[z];
							if (nR < 0 || nR >= n || nC < 0 || nC >= n) continue;
							if (adj[nR][nC] != '#') adj[nR][nC]--;
						}
					}
				}
			}
		}
	}

	if (n > 4) answer += (n - 4)*(n - 4);
	cout << answer;
}