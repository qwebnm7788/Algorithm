/*
10815번 숫자카드

가지고 있는 카드의 리스트에 M개의 카드 각각이 존재하는지 여부를 찾으면 된다.
stl의 binary_search 함수를 이용해도 바로 풀 수 있고

이처럼 직접 구현하여 찾아줄 수도 있다.
*/
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main() {
	freopen("input.txt", "r", stdin);
	int n, m;
	cin >> n;
	vector<int> card(n);
	for (int i = 0; i < n; ++i) cin >> card[i];

	cin >> m;
	vector<int> target(m);
	for (int i = 0; i < m; ++i) cin >> target[i];

	sort(card.begin(), card.end());

	for (int i = 0; i < m; ++i) {
		int lo = -1, hi = n;
		bool found = false;
		while (lo + 1 < hi) {
			int  mid = (lo + hi) / 2;
			if (target[i] > card[mid]) lo = mid;
			else if (target[i] < card[mid]) hi = mid;
			else {
				found = true;
				break;
			}
		}
		if (found) cout << "1 ";
		else cout << "0 ";
	}
	
}