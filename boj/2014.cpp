/*
2014번 소수의 곱

주어진 소수를 적절히 선택하여 곱한 수들의 크기순으로 나열하였을 때 (주어진 소수 자체도 포함)
N번째의 수를 출력하면 된다.

우선순위 큐를 이용하여 크기가 작은 순서대로 뽑아내면 된다.
즉 주어진 수를 모두 큐에 넣고 하나씩 제일 작은것을 뽑고 그것에 모든 소수를 한번씩 곱해본 값을 넣어준다.

이때 무작정 큐에 다 넣게되면 메모리 초과가 난다.
최대한 넣어야 할것만을 큐에 넣어야 하는데

현재까지 형성된 리스트들 중 (즉 큐안에 있는 수) 최대의 값을 유지하면서
큐에 넣으려고 할 때 넣으려는 수가 최대의 값 밑이고 큐에 있는 것까지 합하면 답을 구할 수 있는 상태라면
큐에 넣지않고 루프를 빠져나온다. (prime의 값이 정렬된 상태이므로 hold와 그 뒤의 prime을 곱해봤자 더 커질 뿐이므로 볼 필요가없다.)

이미 큐에 존재하는지의 여부는 set을 이용하여 관리한다.
*/
#include <iostream>
#include <vector>
#include <queue>
#include <set>
#include <algorithm>
using namespace std;

int main() {
	freopen("input.txt", "r", stdin);
	int k, n;
	cin >> k >> n;

	vector<long long> prime(k);
	priority_queue<long long> pq;
	set<long long> s;
	long long cnt = 0, hold, maxVal = 0;

	for (int i = 0; i < k; ++i) {
		cin >> prime[i];
		maxVal = max(maxVal, prime[i]);
		pq.push(-prime[i]);
		s.insert(prime[i]);
	}

	while (true) {
		hold = -pq.top();
		pq.pop();
		cnt++;
		if (cnt == n) break;
		for (int i = 0; i < k; ++i) {
			if (pq.size() >(n - cnt) && prime[i] * hold > maxVal) break;
			if (s.count(prime[i] * hold) == 0){
				maxVal = max(maxVal, prime[i] * hold);
				s.insert(prime[i] * hold);
				pq.push(-(prime[i] * hold));
			}
		}
	}
	cout << hold;
}