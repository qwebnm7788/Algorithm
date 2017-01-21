/*
5419 북서풍 
으아. 낭레매넝 ㅔㄹ 드디어 풀었다.

세그먼트 트리로 풀면 되는데 정렬을 어떻게 하는지와 좌표를 압축해서 표현하는 방법을
잘 이용하면 쉽게 풀린다. (구간합으로 할 수 있땅)
*/
#include <stdio.h>
#include <vector>
#include <algorithm>
#include <set>
using namespace std;

vector<pair<int, int>> arr;
vector<int> ans;
vector<int> condense;		//y좌표로 압축

//x좌표는 내림차순으로 정렬하고 만약 같다면 y좌표를 기준으로 오름차순으로 정렬해주자
//이렇게 되면 i번 섬을 본다면 이 섬은 앞에 나와있는 섬으로 갈 수 있는데
//왜냐하면 i번 섬의 앞쪽 친구들은 x좌표가 i번 섬보다 크기때문에 더 동쪽에 있는 섬들이므로 x좌표의 조건은 만족한다.
//그리고 나서 y또한 오름차순으로 정렬되어있어서 i번 섬보다는 y좌표가 아래쪽에 있는 친구들 (즉 남쪽)이기 때문에
//i번 섬을 기준으로는 i 밑의 친구들은 모두 i번 섬 기준 동남쪽에 있는 친구여서 주어진 조건을 만족하게 된다.
bool comp(pair<int, int>& a, pair<int, int>& b) {
	if (a.first == b.first)
		return a.second < b.second;
	return a.first > b.first;
}

//맨 처음에 y좌표를 압축시키기 위해서 (비교를 y에 대해서만 할꺼니깐 x는 필요가 없다.)
//y좌표로 오름차순이 될 수있게 비교함수를 정의
bool compY(pair<int, int>& a, pair<int, int>& b) {
	if (a.second == b.second)
		return a.first < b.first;
	return a.second < b.second;
}

//세그먼트 트리를 작성하는데 각 노드는 주어진 범위를(인덱스 자체를) y좌표로 하여 그 높이가 존재하는 수를 반환하게 만든다. (구간 합으로 구현하면 된다.)
int update(int index, int value, int node, int nodeLeft, int nodeRight) {
	if (index < nodeLeft || index > nodeRight)
		return ans[node];
	if (nodeLeft == nodeRight)
		return ans[node] += value;
	int mid = (nodeLeft + nodeRight) / 2;
	return ans[node] = update(index, value, node * 2, nodeLeft, mid) + update(index, value, node * 2 + 1, mid + 1, nodeRight);
}

//쿼리는 주어진 y좌표 이후의 값을 찾으면 된다. (왜냐면 정렬을 y좌표가 작은것이 뒤로 가게 해놓았으므로)
//주어진 [left,right]범위 내의 y좌표에 속하는 친구의 수를 반환해준다.
//근데 우리는 y좌표가 작은친구들이 (원래좌표에서) 뒤로가게 해서 압축된 y의 번호는 큰것을 찾아주면된다.(실 좌표는 y좌표가 작은것)
int query(int left, int right, int node, int nodeLeft, int nodeRight) {
	if (right < nodeLeft || left > nodeRight)
		return 0;
	if (left <= nodeLeft && nodeRight <= right)
		return ans[node];
	int mid = (nodeLeft + nodeRight) / 2;
	return query(left, right, node * 2, nodeLeft, mid) + query(left, right, node * 2 + 1, mid + 1, nodeRight);
}

int main() {
	freopen("input.txt", "r", stdin);
	//freopen("output.txt", "w", stdout);
	int test;
	scanf("%d", &test);
	for (int z = 0; z < test; ++z) {
		int n;
		scanf("%d", &n);
		
		//resize는 사이즈만 바뀌고 초기화는 안된다.
		arr = vector<pair<int,int>>(n);
		ans = vector<int>(4 * n);
		condense = vector<int>(n);

		//입력
		for (int i = 0; i < n; ++i)
			scanf("%d %d", &arr[i].first, &arr[i].second);

		//y좌표로 정렬 (작은게 앞으로 오게끔)
		//y좌표를 새롭게 압축한 값을 condense값에 넣는다, 즉 i번 섬의 압축된 좌표 = condense[i]
		//이렇게 되면 최종적으로 높이는 [0~height]까지로 압축된다.
		sort(arr.begin(), arr.end(), compY);
		int height = 0;
		for (int i = 0; i < n; ++i) {
			//y만을 기준으로 정렬되어서 높이가 같은 친구는 서로 붙어있다. 이때는 같은 높이이므로 증가를 안시킨다.
			if (i != 0 && (arr[i - 1].second != arr[i].second))
				height++;
			condense[i] = height;
		}
		//좌표를 압축된 상태로 바꾸어 준다.
		for (int i = 0; i < n; ++i)
			arr[i].second = condense[i];

		//원하던 대로 다시 정렬하자.
		//즉 우선적으로 x를 오름차순으로 정렬하고 같다면 y는 내림차순이 되도록.
		sort(arr.begin(), arr.end(), comp);
		

		//주의 할 점은 섬의 갯수가 75000개이고 이렇게 되면 섬이 짝지어 지는 최대의 수가 0~75000까지의 누적합이 된다.(0+1+2+3+...+75000)
		//그렇게 되면 int형의 범위를 넘어가게 된다 (unsigned int 형으로도 가능하다.)
		long long ret = 0;
		for (int i = 0; i < n; ++i) {
			//위의 정렬의 설명대로 i번 섬은 i번 앞에 있는 섬들만 접근이 가능한데
			//그렇게 표현하기 위해서는 순서대로 update를 해주면서 쿼리를 날리는 것이다.
			//그러면 i번섬은 자신 이전의 섬들에 대해서만 업데이트 된 상태로 쿼리를 날리게 되어서 원하는 결과를 얻을 수 있다.
			ret += query(0, arr[i].second, 1, 0, height);
			update(arr[i].second, 1, 1, 0, height);
		}
		printf("%lld\n", ret);
	}
}