//6549 히스토그램에서 가장 큰 직사각형
//나보다 크기가 작거나 같은 친구의 갯수 * 나의 높이를 다 체크해주면 된다.
//단순히 이 친구들을 매번 왼쪽, 오른쪽을 다 훑어주게 되면 O(n)번 씩 O(n)번 훑게 되어서
//O(N^2)이 된다.  n = 10^5까지라서 O(N^2) = 10^10이 되어서 시간제한인 1초안에 들어올 수 없다.
/*
#include <stdio.h>
#include <vector>
#include <algorithm>
using namespace std;

int main() {
	freopen("input.txt", "r", stdin);

	while (true) {
		int n;
		scanf("%d", &n);

		if (!n)
			break;

		vector<long long> height(n);
		for (int i = 0; i < n; ++i)
			scanf("%d", &height[i]);

		long long ret = 0;
		int cnt;
		for (int i = 0; i < n; ++i) {
			cnt = 1;
			
			//요기는 필요가 없었다.
			//for (int j = i - 1; j >= 0; --j) {
				//if (height[j] >= height[i])
					//cnt++:
			//	else
					//break;
			//}
			
			for (int j = i + 1; j < n; ++j) {
				if (height[j] >= height[i])
					cnt++;
				else
					break;
			}
			ret = max(ret, cnt*height[i]);
		}

		printf("%lld\n", ret);
	}
	
}
*/

/*
저렇게 풀면 안되네;
분할정복으로 풀어주어야 한다. -> 좌변과 우변을 left,right로 하는 직사각형중에 제일 큰 친구는 무엇일까용..? --> 그 변을 양변으로 하려면 모든 히스토그램을 뚫어야 되니깐
-> 그 범위 내에서 가장 작은 높이를 갖는 친구의 높이 * (right-left)가 된다.
이제 그 가장 작은 높이를 가지는 친구를 기준으로 반반으로 자르고 그 과정을 반복하면 된다.
이때 주어진 구간에서 가장 작은 높이는 세그먼트 트리로 O(logN)에 구할 수 있고 매번 반복하면 O(N)이므로 총 O(NlogN)에 구할 수 있따.
*/
#include <stdio.h>
#include <vector>
#include <algorithm>
#include <limits>
using namespace std;

const long long INF = numeric_limits<long long>::max();

vector<long long> arr;
vector<long long> ans;

//각 노드를 자신의 구간에서 가장 작은 높이의 위치를 반환하도록 하자.
long long init(int left, int right, int node) {
	if (left == right)
		return ans[node] = left;
	int mid = (left + right) / 2;
	int leftMin = init(left, mid, node * 2);
	int rightMin = init(mid + 1, right, node * 2 + 1);
	if (arr[leftMin] <= arr[rightMin])
		return ans[node] = leftMin;
	else
		return ans[node] = rightMin;
}

//[left,right]에서 가장 작은 높이의 인덱스를 반환해준다.
long long query(int left, int right, int node, int nodeLeft, int nodeRight) {
	if (right < nodeLeft || left > nodeRight)
		return -1;
	if (left <= nodeLeft && nodeRight <= right)
		return ans[node];
	int mid = (nodeLeft + nodeRight) / 2;
	int leftMin = query(left, right, node * 2, nodeLeft, mid);
	int rightMin = query(left, right, node * 2 + 1, mid + 1, nodeRight);
	
	//어차피 둘 중 하나는 원하는 구간안에 들어가니깐.! (겹칠 수도 있고 -> 세그먼트 트리의 최대 겹치는 구간을 보자.-> 설명글에)
	if (leftMin == -1)
		return rightMin;
	else if (rightMin == -1)
		return leftMin;
	else {
		if (arr[leftMin] <= arr[rightMin])
			return leftMin;
		else
			return rightMin;
	}
}

//[start,end]구간에서의 가장 큰 넓이를 갖는 히스토그램의 넓이를 반환해주장
long long func(int start, int end, int node, int nodeLeft, int nodeRight) {
	int found = query(start, end, 1, nodeLeft, nodeRight);

	long long ret = (end - start + 1)*arr[found];
	if (start <= found - 1) {
		long long left = func(start, found - 1, 1, nodeLeft, nodeRight);
		ret = max(ret, left);
	}
	if (end >= found + 1) {
		long long right = func(found + 1, end, 1, nodeLeft, nodeRight);
		ret = max(ret, right);
	}
	return ret;
}
int main() {
	freopen("input.txt", "r", stdin);
	while (true) {
		int n;
		scanf("%d", &n);

		if (n == 0)
			break;

		ans = vector<long long>(4 * n);
		arr = vector<long long>(n);
		for (int i = 0; i < n; ++i)
			scanf("%lld", &arr[i]);

		init(0, n - 1, 1);
		printf("%lld\n", func(0, n - 1, 1, 0, n - 1));
	}
}
