//
// Created by jaewon on 2017-06-29.
//
#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
using namespace std;

const int INF = 2e9;
const int dr[4] = { -1,0,1,0 };
const int dc[4] = { 0,1,0,-1 };

int n;
vector<vector<int>> adj;
vector<vector<bool>> visited;

void paint(int row, int col, int color) {
    visited[row][col] = true;
    adj[row][col] = color;
    for (int i = 0; i < 4; ++i) {
        int nextRow = row + dr[i];
        int nextCol = col + dc[i];
        if (nextRow < 0 || nextRow >= n || nextCol < 0 || nextCol >= n) continue;
        if (!visited[nextRow][nextCol] && adj[nextRow][nextCol] == 1) {
            visited[nextRow][nextCol] = true;
            paint(nextRow, nextCol, color);
        }
    }
}

int bfs(int color) {
    vector<vector<bool>> checked(n, vector<bool>(n, false));
    queue<pair<int, int>> q;
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            if (adj[i][j] == color) {
                checked[i][j] = true;
                q.push({ i,j });
            }
        }
    }
    int size, level = 0;
    bool check = false;
    while (!q.empty()) {
        size = q.size();
        for (int i = 0; i < size; ++i) {
            int row = q.front().first;
            int col = q.front().second;
            q.pop();
            if (adj[row][col] != 0 && adj[row][col] != color) {
                check = true;
                break;
            }
            for (int j = 0; j < 4; ++j) {
                int nextRow = row + dr[j];
                int nextCol = col + dc[j];
                if (nextRow < 0 || nextRow >= n || nextCol < 0 || nextCol >= n) continue;
                if (!checked[nextRow][nextCol] && adj[nextRow][nextCol] != color) {
                    checked[nextRow][nextCol] = true;
                    q.push({ nextRow,nextCol });
                }

            }
        }
        if (check) break;
        level++;
    }
    return level;
}
int main() {
    ios_base::sync_with_stdio(false);
    freopen("input.txt", "r", stdin);
    cin >> n;

    adj = vector<vector<int>>(n, vector<int>(n));
    visited = vector<vector<bool>>(n, vector<bool>(n, false));

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            cin >> adj[i][j];
        }
    }
    int color = 1;
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            if (!visited[i][j] && adj[i][j] == 1) {
                paint(i, j, color++);
            }
        }
    }

    int ans = INF;
    for (int i = 1; i < color; ++i) {
        ans = min(ans, bfs(i));
    }
    cout << ans - 1;
}