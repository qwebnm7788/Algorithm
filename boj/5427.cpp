#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
using namespace std;

const int INF = 2e9;
const int dr[4] = { -1,0,1,0 };
const int dc[4] = { 0,1,0,-1 };

int main() {
	ios_base::sync_with_stdio(false);
	int test;
	cin >> test;
	while (test--) {
		int w, h;
		cin >> w >> h;

		vector<vector<char>> adj(h, vector<char>(w));
		vector<vector<bool>> personVisit(h, vector<bool>(w, false));
		vector<vector<bool>> fireVisit(h, vector<bool>(w, false));
		queue<pair<int, int>> person, fire;

		for (int i = 0; i < h; ++i) {
			for (int j = 0; j < w; ++j) {
				cin >> adj[i][j];
				if (adj[i][j] == '@') {
					personVisit[i][j] = true;
					person.push({ i,j });
				}
				else if (adj[i][j] == '*') {
					fireVisit[i][j] = true;
					fire.push({ i,j });
				}
			}
		}

		int size, time = 0;
		bool answer = false;
		while (!person.empty()) {
			size = person.size();
			for (int i = 0; i < size; ++i) {
				int currentRow = person.front().first;
				int currentCol = person.front().second;
				person.pop();

				if (adj[currentRow][currentCol] == '*') continue;		//불이 현재 위치에 번져왔다면 실패

				adj[currentRow][currentCol] = '.';					//이제 이 곳을 벗어난다.
				
				//탈출에 성공하였는지 체크
				if (currentRow == h - 1 || currentRow == 0 || currentCol == 0 || currentCol == w-1) {
					answer = true;
					break;
				}

				for (int k = 0; k < 4; ++k) {
					int nextRow = currentRow + dr[k];
					int nextCol = currentCol + dc[k];
					if (nextRow < 0 || nextRow >= h || nextCol < 0 || nextCol >= w) continue;
					if (adj[nextRow][nextCol] != '.' || personVisit[nextRow][nextCol]) continue;		//갈 수 있는 곳이 아니거나 이미 방문한 점은 다시 방문하지 않는다.

					adj[nextRow][nextCol] = '@';
					personVisit[nextRow][nextCol] = true;
					person.push({ nextRow,nextCol });
				}
			}

			if (answer) break;
			//불이 이동
			size = fire.size();
			for (int i = 0; i < size; ++i) {
				int currentRow = fire.front().first;
				int currentCol = fire.front().second;
				fire.pop();

				for (int k = 0; k < 4; ++k) {
					int nextRow = currentRow + dr[k];
					int nextCol = currentCol + dc[k];

					if (nextRow < 0 || nextRow >= h || nextCol < 0 || nextCol >= w) continue;
					if (adj[nextRow][nextCol] == '#' || adj[nextRow][nextCol] == '*' || fireVisit[nextRow][nextCol]) continue;			//벽이나, 이미 방문한 점은 안한다.

					adj[nextRow][nextCol] = '*';
					fireVisit[nextRow][nextCol] = true;
					fire.push({ nextRow,nextCol });
				}
			}

			time++;
		}

		if (answer) cout << time + 1 << endl;
		else cout << "IMPOSSIBLE\n";
	}
}