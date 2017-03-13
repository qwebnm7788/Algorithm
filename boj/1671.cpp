/*
1671 상어의 저녁식사

source - 상어 - 상어 - sink 로 플로우로 풀어도 되고
좀 더 간단하게 상어 - 상어 의 이분매칭으로 수정해도 된다.

여기서는 한 상어가 최대 2마리를 먹을 수 있으므로 N - M 대칭으로 그룹을 지어줄때 N 그룹에 상어가 2개씩 있어주면 된다.

이렇게 최대매칭을 지어주게 되면 상어가 매칭된 갯수만큼 잡아먹히게 되므로 전체 상어의 수에서 최대매칭 수를 빼주면 답을 구할 수 있다.

이때 매칭을 구할때 생길 수 있는 상황으로는 한 상어가 그 친구를 잡아먹었는데 그 친구도 다른친구를 잡아먹었을 경우가 생길 수 있다.
그렇지만 이러한 상황은 크게 문제되지 않는데 이렇게 서로 줄줄이 이어져서 다 잡아먹었다면 
임의대로 순서를 잘 배치해주면 가장 약한 친구부터 하나씩 잡아먹는 순서를 매겨준다면 모두 다 자기가 잡아먹었던 친구를 잡아먹을 수 있음을 알 수 있다.

또한 또다른 예외 케이스는 서로 모든 능력이 동일한 친구가 존재해서 서로가 서로를 잡아먹을 수 있는 경우이다.
이때는 위의 케이스에 해당되지 못한다. 즉 둘 중 한명이 한명만을 잡아먹을 수 있는데 그것은 누가 되던 상관은 없다. (왜냐면 능력이 서로 같기 때문에 이 친구가 다른 친구를 잡아먹는 것에는 영향을 주지 않는다)

따라서 이분그래프를 형성할때 이러한 경우를 제외해주면 되는데 두 상어의 능력치가 전부 다 동일하다면 한번만 추가되도록 한다.

가장 간단한 방법은 순서를 강제해서 먼저 나온 상어가 뒤에 나오는 상어를 잡아먹도록 하고 뒤에 나온 상어가 앞의 상어를 못먹게 해주면 간단하게 처리할 수 있다.
*/
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

class shark {
public:
	shark(int aa, int bb, int cc)
		:a(aa), b(bb), c(cc) {}

	int getA() const {
		return a;
	}

	int getB() const {
		return b;
	}

	int getC() const {
		return c;
	}

private:
	int a, b, c;
};

int n;

vector<vector<int>> adj;
vector<int> aMatch, bMatch;
vector<bool> visited;
vector<shark> arr;


bool dfs(int a) {
	if (visited[a]) return false;
	visited[a] = true;
	for (int b : adj[a]) {
		if (bMatch[b] == -1 || dfs(bMatch[b])) {
			aMatch[a] = b;
			bMatch[b] = a;
			return true;
		}
	}
	return false;
}

int bipartiteMatch() {
	aMatch = vector<int>(2 * n, -1);
	bMatch = vector<int>(n, -1);

	int ret = 0;
	for (int i = 0; i < 2 * n; ++i) {
		if (aMatch[i] == -1) {
			visited = vector<bool>(2 * n, false);
			if (dfs(i))
				ret++;
		}
	}
	return ret;
}
int main() {
	freopen("input.txt", "r", stdin);
	cin >> n;

	int a, b, c;
	for (int i = 0; i < n; ++i) {
		cin >> a >> b >> c;
		arr.push_back(shark(a, b, c));
	}

	adj = vector<vector<int>>(2 * n);
	for (int i = 0; i < n; ++i) {
		for (int j = 0; j < n; ++j) {
			//자기자신은 제외
			if (i == j) continue;
			//완전 똑같은 상어가 존재한다면 순서를 강제해서 한번만 먹이사슬에 이어주자.
			if (arr[i].getA() >= arr[j].getA() && arr[i].getB() >= arr[j].getB() && arr[i].getC() >= arr[j].getC()) {
				if (arr[i].getA() == arr[j].getA() && arr[i].getB() == arr[j].getB() && arr[i].getC() == arr[j].getC() && i > j) continue;

				adj[2 * i].push_back(j);
				adj[2 * i + 1].push_back(j);
			}
		}
	}

	int ans = bipartiteMatch();
	cout << n - ans;
}