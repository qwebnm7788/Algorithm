/*
3780 Corporative Network

union-find로 문제를 풀어줄 수 있는데
여기서는 매번 새로운 트리로 합쳐질때마다 길이를 갱신해주어야 한다는 점이 다르다.

a->b->c->d 로 이어져있다면 (d가 루트)
length[i] = i~루트 까지의 길이로 두면
루트에서부터 내려오면서 재귀적으로 값을 갱신해 줄 수 있다.
length[b] = length[c] + abs(c-b)%1000 이 되니깐.

이때 find를 이용해서 재귀적으로 갱신해 줄 수 있는데
find에서 find(parent[x])를 곧바로 반환하는것이 아니라 호출만을 해주게 되면
꼭대기 까지 올라가서 루트일때 반환되면서 unwinding이 되는데
이 때를 이용해서 값을 누적시켜주면 된다.

여기서 주의할 점은 find가 값을 누적시키기 때문에
merge할때 두 루트를 find로 찾아서 검사하는 순간 값이 두번 이상 중복되기 시작한다.
따라서 값의 계산은 두 친구를 merge할때만 한번만 계산해주어야 한다.

*/
#include <cstdio>
#include <cmath>
#include <algorithm>
#include <vector>
using namespace std;

class Uf {
public:
	vector<int> parent, length;		//length[i] = i번 정점이 자기의 루트까지 가는데 필요한 거리
	Uf(int n)
		:parent(n), length(n, 0) {
		for (int i = 0; i < n; ++i)
			parent[i] = i;
	}
	int find(int x) {
		if (parent[x] == x)
			return x;
		int temp = find(parent[x]);
		length[x] += length[parent[x]];
		parent[x] = temp;
		return parent[x];
	}

	void merge(int a, int b) {
		if (parent[a] == parent[b])
			return;
		parent[a] = b;
		length[a] = (abs(a - b) % 1000);
	}
};
int main() {
	freopen("input.txt", "r", stdin);
	freopen("output.txt", "w", stdout);
	int test;
	scanf("%d", &test);

	for (int z = 0; z < test; ++z) {
		int n;
		scanf("%d", &n);
		getchar();
		Uf ar(n);

		char x;
		int a, b;
		while (1) {
			scanf("%1c", &x);
			getchar();
			if (x == 'O')
				break;
			else if (x == 'E') {
				scanf("%d", &a);
				getchar();
				ar.find(a - 1);
				printf("%d\n", ar.length[a - 1]);
			}
			else {
				scanf("%d %d", &a, &b);
				getchar();
				ar.merge(a - 1, b - 1);
			}
		}
	}
}