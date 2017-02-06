#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
using namespace std;

//parent[i] = i의 부모노드 (루트라면 parent[i] = i)
//rank[i] = i가 속한 트리의 높이(rank) (루트인경우)
//enemy[i] = i가 속한 집합과 적대적인 집합의 루트 번호 (i가 루트일때),(없으면 -1)
//size[i] = i가 속한 집합의 크기
struct BipartiteUnionFind {
	vector<int> parent, rank, enemy, size;
	BipartiteUnionFind(int n)
		:parent(n), rank(n, 0), enemy(n, -1), size(n, 1) {
		for (int i = 0; i < n; ++i)
			parent[i] = i;
	}

	int find(int x) {
		if (parent[x] == x)
			return x;
		return parent[x] = find(parent[x]);
	}

	//merge한 후에 트리의 루트를 반환한다.
	int merge(int a, int b) {
		//만약 둘중 하나라도 공집합이라면 아닌 친구를 반환하거나 (-1보다 큰 친구는 무조건이지) -1을 반환한다.
		if (a == -1 || b == -1)
			return max(a, b);

		a = find(a);
		b = find(b);

		if (a == b)
			return a;
		
		//rank가 더 작은 친구를 항상 a로 유지해주자.
		if (rank[a] > rank[b])
			swap(a, b);

		//rank가 더 작은 친구가 큰 친구 밑으로 들어간다.
		parent[a] = b;
		size[b] += size[a];
		if (rank[a] == rank[b])
			rank[b]++;

		return b;
	}

	//u와 v가 서로 상호비방 상태라면 서로 다른집합에 속한다.
	//추가적으로 알아낼 수 있는 정보는 둘은 적이니깐 상대방의 적은 나의 동지가 된다.
	bool dis(int u, int v) {
		u = find(u);
		v = find(v);

		//같은 집합에 있으면 거짓
		if (u == v)
			return false;

		//상대방의 적은 나의 동지이므로 합해주자.
		int a = merge(u, enemy[v]);
		int b = merge(v, enemy[u]);

		//그리고 나서도 서로는 적이다.
		enemy[a] = b;
		enemy[b] = a;

		return true;
	}

	//서로 인정하는 친구들은 서로 같은 집합에 속한다.
	//적대관계라면 모순이고 (여기서 enemy[i]가 처음에 -1로 초기화되어 있어서 맨 처음 아무것도 아닐때는 이 조건을 skip할 수 있다.)
	//enemy[i]를 통해서 체크해주어야 한다. 루트가 서로 다르다는 조건으로 만들어주면 둘이 아무런 연산도 안했을때조차 false가 나게 된다.
	//여기서도 서로 인정하는 집합이면 서로의 적은 나의 적이된다는 사실을 추가적으로 알 수 있다.
	bool ack(int u, int v) {
		u = find(u);
		v = find(v);
		/*
		if (u != v)
			return false;
		요건 안된다.
		*/

		if (enemy[u] == v)
			return false;

		int a = merge(u, v);
		int b = merge(enemy[u], enemy[v]);

		enemy[a] = b;
		//여기서 b는 -1인지를 체크해주어야 하는데 왜냐면 합친 두 집합이 모두 아직 적대시하는 친구들이 없는 경우가 있을 수 있다.
		//즉 맨 처음에 두 친구를 merge해서 a에 넣고 그 적들을 merge했는데 이 두 친구 모두 아직 enemy가 없어서 enemy[u], enemy[v] 가 -1일 수 있다.
		//여기서 merge에서 -1인 경우를 처리해 주었기 때문에 이렇게 간단하게 처리해 줄 수 있다.
		if (b != -1)
			enemy[b] = a;

		return true;
	}
};

//구해놓은 모든 트리에 대해서 가장 크기가 큰 집합의 크기를 반환해주면 된다.
//이때 각각의 트리가 서로 떨어져 있을수 있으니깐 vi 유저집합을 따로 계산하고 emacs유저 집합을 모두 합쳐서
//둘 중 큰 값을 반환 해 주면 된다.
int maxParty(const BipartiteUnionFind& buf) {
	int ret = 0;
	for (int node = 0; node < buf.parent.size(); ++node) {
		//루트만 보자.
		if (buf.parent[node] == node) {
			int enemy = buf.enemy[node];		//이 트리의 적 트리의 루트를 잡는다.

			//이때 한 노드는 한번은 "나"로 한번은 "적"으로 쌍으로 존재하기 때문에
			//두번씩을 방문하게 되는데 이러면 중복계산이 되므로 이를 제한을 해주자.
			//노드의 번호로 두 번 중에 enemy노드의 정점 번호가 더 큰 경우만 계산하게 해줌으로써 (두정점번호는 항상 다르니깐)
			//중복을 피했다. !!
			if (enemy > node)
				continue;

			int mySize = buf.size[node];		//내 집합의 크기
			int enemySize = (enemy == -1 ? 0 : buf.size[enemy]);		//아직도 적이 없을수도 있다. 이때는 크기가 0이다. (적을 한번도 안만들고 트리를 형성할수도 있으므로)
			ret += max(mySize, enemySize);
		}
	}
	return ret;
}
int main() {
	freopen("input.txt", "r", stdin);

	int test;
	cin >> test;

	for (int z = 0; z < test; ++z) {
		int n, m;
		cin >> n >> m;

		BipartiteUnionFind uf(n);
		string message;
		int u, v;
		bool check = false;
		int index = -1;
		for (int i = 0; i < m; ++i) {
			cin >> message >> u >> v;

			if (check)
				continue;

			if (message == "ACK") {
				if (!uf.ack(u, v)) {
					check = true;
					index = i + 1;
				}
			}
			else {
				if (!uf.dis(u, v)) {
					check = true;
					index = i + 1;
				}
			}
		}
		if (!check)
			cout << "MAX PARTY SIZE IS " << maxParty(uf) << endl;
		else
			cout << "CONTRADICTION AT " << index << endl;
	}
}