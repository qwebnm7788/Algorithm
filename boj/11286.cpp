/*
11286 절대값 힙

우선순위 큐에 집어넣고 그냥 빼면된다.
음수,양수를 구분할 수 있도록 추가적인 정보를 집어넣어주면 된다.
*/
#include <iostream>
#include <queue>
using namespace std;

int main() {
	freopen("input.txt", "r", stdin);
	int n;
	cin >> n;

	priority_queue<pair<long long, bool>> pq;
	long long x, ans;
	for (int i = 0; i < n; ++i) {
		cin >> x;
		if (x != 0) {
			pq.push((x < 0 ? make_pair(x, true) : make_pair(-x, false)));
		}
		else {
			if (pq.empty()) cout << "0\n";
			else {
				ans = (pq.top().second ? pq.top().first : -pq.top().first);
				pq.pop();
				cout << ans << endl;
			}
		}
	}
}