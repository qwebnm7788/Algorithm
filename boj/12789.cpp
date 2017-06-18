/*
12789번 도키도키 간식드리미

스택을 이용하여 밑에 줄을 관리하며 순서를 확인해주면 된다.
스택,큐의 연산 사용시 이미 비어있는지의 여부를 잘 살펴야 한다.
*/
#include <iostream>
#include <stack>
#include <queue>
using namespace std;

int main() {
	freopen("input.txt", "r", stdin);
	int n;
	cin >> n;
	queue<int> right;
	stack<int> down;
	int x;
	for (int i = 0; i < n; ++i) {
		cin >> x;
		right.push(x);
	}
	int current = 1;
	while (true) {
		if (!right.empty() && right.front() == current) {
			right.pop();
			current++;
		}
		else if(!down.empty() && down.top() == current){
			down.pop();
			current++;
		}
		else {
			if (right.empty()) break;
			down.push(right.front());
			right.pop();
		}
	}
	if (current == n + 1) cout << "Nice";
	else cout << "Sad";
}