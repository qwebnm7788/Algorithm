/*
3392 화성지도

세그먼트 트리 + 스위핑

세로 변을 기준으로 생각해보자. 즉 각 직사각형이 직사각형이 시작하는 세로변과 끝나는 세로변 2개로 구성되어 있다고 생각해보면 된다.
이러한 세로변들을 모두 저장해두고 x축 좌표를 기준으로 오름차순 정렬을 시켜주자.

그러면 제일 왼쪽에 있는 세로변부터 만나게 될것이다. 이때 이 세로변이 시작하는 세로변이라면 각 노드가 표현하는 범위의 y좌표를 갖는 점의 수라고 생각하고 업데이트 시켜주자. (구간에 1씩 증가되도록)
만약 끝나는 세로변이라면 이 친구가 표현하는 구간에 대해서 -1을 업데이트 시켜주자.

이 과정을 거치기전에는 나의 왼쪽에 있는 친구들의 계산을 한번 진행해볼수 있는데 나 이전에 만난 세로변의 x좌표와 나의 x좌표의 차이와 현재 (나를 업데이트 하기전에) 존재하는 모든 y좌표상에 있는 친구들의 "갯수"를
곱해주면 이전 세로변과 나의 사이에 존재하는 모든 친구들을 계산해줄 수 있다. -> 이때는 업데이트 시켜준 값으로 다른 배열을 만들어서 비교해주어야 한다.
그냥 구간합을 리턴한다면 중복되는 친구들도 모두 세어주기 때문이다. 따라서 업데이트 할때 적절하게 변형해주어야 한다.

*/
#include <cstdio>
#include <vector>
#include <algorithm>
using namespace std;

const int MAX_Y = 30005;

struct elem {
	bool isStart;
	int x, y1, y2;
	elem(int a = 0, int b = 0, int c = 0, bool d = false)
		:x(a), y1(b), y2(c), isStart(d) {}
};

bool comp(elem& a, elem& b) {
	if (a.x != b.x)
		return a.x < b.x;
	else
		return a.isStart > b.isStart;
}

vector<elem> arr;
vector<int> cnt;
vector<int> ans;

//y좌표가 [left,right]인 친구의 갯수를 value만큼 증가시켜준다.
void update(int left, int right, int value, int node, int nodeLeft, int nodeRight) {
	if (right <nodeLeft || left >nodeRight)
		return;
	if (left <= nodeLeft && nodeRight <= right)
		ans[node] += value;
	else {
		int mid = (nodeLeft + nodeRight) / 2;
		update(left, right, value, node * 2, nodeLeft, mid);
		update(left, right, value, node * 2 + 1, mid + 1, nodeRight);
	}
	if (ans[node] >= 1)
		cnt[node] = nodeRight - nodeLeft + 1;
	else {
		if (nodeLeft == nodeRight)
			cnt[node] = 0;
		else
			cnt[node] = cnt[node * 2] + cnt[node * 2 + 1];
	}
}

int query(int left, int right, int node, int nodeLeft, int nodeRight) {
	if (right < nodeLeft || left > nodeRight)
		return 0;
	if (left <= nodeLeft && nodeRight <= right)
		return cnt[node];
	int mid = (nodeLeft + nodeRight) / 2;
	return query(left, right, node * 2, nodeLeft, mid) + query(left, right, node * 2 + 1, mid + 1, nodeRight);
}


int main() {
	freopen("input.txt", "r", stdin);
	int n;
	scanf("%d", &n);

	arr.resize(2 * n);
	ans.resize(4 * MAX_Y);
	cnt.resize(4 * MAX_Y);

	int x1, y1, x2, y2;
	for (int i = 0; i < n; ++i) {
		//입력시에 y2의 값을 -1을 해주어야 하는데 그냥 구하게 된다면 나는 지금 (1,1)을 한 칸으로 생각해서 사각형이 (1,1)-(1,2)-(2,2)-(2,1)인 크기 1의 정사각형이라고 생각하고
		//세그먼트 트리의 구간을 표현한것이기 때문에 WA가 나온다. !!! 따라서 한칸을 낮추어주어서 구현한 방향대로 입력을 받도록 하자.
		scanf("%d %d %d %d", &x1, &y1, &x2, &y2);
		arr[2 * i] = elem(x1, y1, y2-1, true);
		arr[2 * i + 1] = elem(x2, y1, y2-1, false);
	}

	sort(arr.begin(), arr.end(), comp);
	int area = 0;
	for (int i = 0; i < arr.size(); ++i) {
		if (i != 0) {
			printf("%d\n", query(0, MAX_Y, 1, 0, MAX_Y));
			area += ((arr[i].x - arr[i - 1].x)*(query(0, MAX_Y, 1, 0, MAX_Y)));
		}
		if (arr[i].isStart)
			update(arr[i].y1, arr[i].y2, 1, 1, 0, MAX_Y);
		else
			update(arr[i].y1, arr[i].y2, -1, 1, 0, MAX_Y);
	}
	printf("%d", area);
}
