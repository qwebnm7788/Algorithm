/*
10227 JuQueen

이 문제에서 고민이 되는 부분은 구간에서 어느 한 친구라도 더하는 값과 합쳐서 0이 되거나 N이 된다면 그 이상으로는 더할 수 없다는것이다.
이것을 해결하는 방법은 구간최대값/최소값 세그먼트 트리를 이용하는 것이다.

만약 더하는 값이 음수라면 최소값 트리를 이용해서 그 구간에서 최소값 x을 얻었다고 하면 x와 더하는 값을 합쳐서 음수가 된다면 최대 -x뿐이 더할수없으므로 -x을 업데이트 하고
그렇지 않다면 그냥 원하는 값을 주면 된다.

양수라면 구간 최대값 x를 찾은 후에 합쳐서 n보다 크다면 n-x만큼만 증가가 가능하므로 그 값만큼만 증가시키고
n보다 작다면 그냥 그대로 그 값을 업데이트 시켜주면 된다.
*/
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
using namespace std;

const int INF = 987654321;

vector<int> maxans;
vector<int> minans;
vector<int> lazy;
int n;

void propagate(int nodeLeft, int nodeRight, int node) {
	if (lazy[node] != 0) {
		if (nodeLeft != nodeRight) {
			lazy[node * 2] += lazy[node];
			lazy[node * 2 + 1] += lazy[node];
			maxans[node] = max(maxans[node * 2]+lazy[node*2], maxans[node * 2 + 1]+lazy[node*2+1]);
			minans[node] = min(minans[node * 2] + lazy[node * 2], minans[node * 2 + 1] + lazy[node * 2 + 1]);
		}
		else {
			maxans[node] += lazy[node];
			minans[node] += lazy[node];
		}
		lazy[node] = 0;
	}
}

void update(int left, int right, int value, int node, int nodeLeft, int nodeRight) {
	propagate(nodeLeft, nodeRight, node);

	if (right < nodeLeft || left >nodeRight)
		return;
	if (left <= nodeLeft && nodeRight <= right) {
		lazy[node] += value;
		propagate(nodeLeft, nodeRight, node);
		return;
	}

	int mid = (nodeLeft + nodeRight) / 2;
	update(left, right, value, node * 2, nodeLeft, mid);
	update(left, right, value, node * 2 + 1, mid + 1, nodeRight);
	maxans[node] = max(maxans[node * 2], maxans[node * 2 + 1]);
	minans[node] = min(minans[node * 2], minans[node * 2 + 1]);
}

int minQuery(int left, int right, int node, int nodeLeft, int nodeRight) {
	propagate(nodeLeft, nodeRight, node);
	if (right <nodeLeft || left > nodeRight)
		return INF;
	if (left <= nodeLeft && nodeRight <= right)
		return minans[node];
	int mid = (nodeLeft + nodeRight) / 2;
	return min(minQuery(left, right, node * 2, nodeLeft, mid), minQuery(left, right, node * 2 + 1, mid + 1, nodeRight));
}

int maxQuery(int left, int right, int node, int nodeLeft, int nodeRight) {
	propagate(nodeLeft, nodeRight, node);
	if (right < nodeLeft || left > nodeRight)
		return -1;
	if (left <= nodeLeft && nodeRight <= right)
		return maxans[node];
	int mid = (nodeLeft + nodeRight) / 2;
	return max(maxQuery(left, right, node * 2, nodeLeft, mid), maxQuery(left, right, node * 2 + 1, mid + 1, nodeRight));
}

int main() {
	ios_base::sync_with_stdio(false);
	freopen("input.txt", "r", stdin);
	int c,o;
	cin >> c >> n >> o;

	maxans.resize(4 * c);
	minans.resize(4 * c);
	lazy.resize(4 * c);

	string x;
	int a, b, s, temp;
	for (int i = 0; i < o; ++i) {
		cin >> x;
		if (x == "state") {
			cin >> a;
			cout << maxQuery(a, a, 1, 0, c - 1) << endl;
		}
		else if (x == "change") {
			cin >> a >> b;
			if (b < 0) {
				temp = minQuery(a, a, 1, 0, c - 1);
				if (temp + b < 0) {
					update(a, a, -temp, 1, 0, c - 1);
					cout << -temp << endl;
				}
				else {
					update(a, a, b, 1, 0, c - 1);
					cout << b << endl;
				}
			}else{
				temp = maxQuery(a, a, 1, 0, c - 1);
				if (temp + b > n) {
					update(a, a, n - temp, 1, 0, c - 1);
					cout << n - temp << endl;
				}
				else {
					update(a, a, b, 1, 0, c - 1);
					cout << b << endl;
				}
			}
		}
		else {
			cin >> a >> b >> s;
			if (s < 0) {
				temp = minQuery(a, b, 1, 0, c - 1);
				if (temp + s < 0) {
					update(a, b, -temp, 1, 0, c - 1);
					cout << -temp << endl;
				}
				else {
					update(a, b, s, 1, 0, c - 1);
					cout << s << endl;
				}
			}
			else {
				temp = maxQuery(a, b, 1, 0, c - 1);
				if (temp + s > n) {
					temp = maxQuery(a, b, 1, 0, c - 1);
					update(a, b, n - temp, 1, 0, c - 1);
					cout << n - temp << endl;
				}
				else {
					update(a, b, s, 1, 0, c - 1);
					cout << s << endl;
				}
			}
		}
	}
}
