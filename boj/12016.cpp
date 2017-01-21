/*
12016 라운드 로빈 스케줄러

이 문제는 그냥 단순하게 1초씩 감소시키게 만들어준다면 한 작업에 최대 드는 시간이 10^9이고 1초씩 모든 작업을 다 확인해봐야 하므로
O(n*10^9)으로 n의 최대값이 10^5이므로 O(10^14)이 된다.

빠르게 풀기 위해서는 한 작업이 다른 작업보다 걸리는 시간이 더 크다면 더 작은 작업이 완료되는 시간을 포함한다는 사실을 이용하면 되는데
우선 각 작업에 필요한 시간으로 오름차순이 되도록 정렬한다. 그렇게 되면 i번 앞에있는 친구는 무조건 나보다 적은 시간으로 완료가 가능하다.
따라서 다음의 식이 성립하게 되는데
i번째의 작업을 완성짓기 위해서는 (1~i번중 끝나지 않은작업의 수)*(i번 작업의 걸리는 시간) + (i+1~n번 중 끝나지않은 수 )*(i번작업에 걸리는 시간-1) + 이미 완료된 작업의 시간중 최대값(즉 누적합)

7 3 4초가 걸리는 작업이 있다고 하자 정렬하면 3 4 7초가 되는데 우선 3초가 걸리는 작업을 보게 되면 3초가 걸리는 작업은 2번이고 이 친구는
3바퀴를 돌아야지 0초가 되어 완성이 된다. -> 그렇게 되면 이 친구 앞에 있는 친구들은 모두 3바퀴를 경험하게 된다.
-> 그러나 이 친구 뒤에 있는 친구들은 3바퀴 바로직전에 끝나게 되므로 3-1바퀴를 경험하게 되는것이당.
-> 우리가 구하는 것은 몇초가 "흘렀는지"를 확인하는 것이기 때문에
그 기준으로부터 얼마나 흘렀는지에다가 지금까지 흐른시간을 더해주면 된다.
(왜냐면 바로 전 친구는 완료가 되어서 끝나지 않은 작업의 수에서 제외가 된다. -> 그렇게 되면 이제 그 친구는 종료된 후에 몇번이 더 이루어지는 지를 계산하는 것이니깐
현재까지 흐른시간을 더해주어야 올바른 시간을 구할 수 있따.
*/
#include <stdio.h>
#include <vector>
#include <algorithm>
using namespace std;

vector<pair<long long, int>> arr;
vector<long long> ans;
vector<long long> ret;

long long update(int index, long long value, int node, int nodeLeft, int nodeRight) {
	if (index < nodeLeft || index > nodeRight)
		return ans[node];
	if (nodeLeft == nodeRight)
		return ans[node] += value;
	int mid = (nodeLeft + nodeRight) / 2;
	return ans[node] = update(index, value, node * 2, nodeLeft, mid) + update(index, value, node * 2 + 1, mid + 1, nodeRight);
}

long long query(int left, int right, int node, int nodeLeft, int nodeRight) {
	if (right < nodeLeft || nodeRight < left)
		return 0;
	if (left <= nodeLeft && nodeRight <= right)
		return ans[node];
	int mid = (nodeLeft + nodeRight) / 2;
	return query(left, right, node * 2, nodeLeft, mid) + query(left, right, node * 2 + 1, mid + 1, nodeRight);
}

int main() {
	freopen("input.txt", "r", stdin);

	int n;
	scanf("%d", &n);

	arr.resize(n);
	ret.resize(n);
	ans.resize(4 * n);

	//pair로 index와 값 자체를 저장
	long long x;
	for (int i = 0; i < n; ++i) {
		scanf("%lld", &x);
		arr[i].first = x;
		arr[i].second = i;
		update(i, 1, 1, 0, n - 1);
	}

	sort(arr.begin(), arr.end());

	long long current = 0;
	for (int i = 0; i < n; ++i) {
		int index = arr[i].second;
		long long value = arr[i].first;
		
		ret[index] = query(0, index, 1, 0, n - 1) *(value)+query(index + 1, n - 1, 1, 0, n - 1)*(value - 1) + current;
		update(index, -1, 1, 0, n - 1);

		current += value;		//지금까지 걸린 시간은 0~i번까지 작업에 필요한 시간의 누적합과 같다.
	}

	for (int i = 0; i < n; ++i)
		printf("%lld\n", ret[i]);
}