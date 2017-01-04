#include <iostream>
#include <vector>
using namespace std;

//�׷����� ��������Ʈ ǥ��
vector<vector<int> > adj;

//�湮 ���� ǥ��
vector<bool> visited;

void dfs(int here) {
	cout << "DFS visits " << here << endl;
	visited[here] = true;

	//��� ���� ������ ��ȸ�Ѵ�.
	for (int i = 0; i < adj[here].size(); ++i) {
		int there = adj[here][i];

		//���� �湮�������� ���������� �ִٸ� �湮�Ѵ�.
		if (!visited[there])
			dfs(there);
	}
	
	//�� �̻� �湮�� ������ �����Ƿ� ���ȣ���� ����Ǹ鼭 ���� �湮 �������� ���ư���.
}

//��� ������ �湮�Ѵ�.
void dfsAll() {
	//visited�� ��� false�� �ʱ�ȭ
	visited = vector<bool>(adj.size(), false);
	
	//��� ������ ��ȸ�ϸ鼭, ���� �湮�� ���� ���ٸ� ���̿켱Ž���� �ǽ��Ѵ�.
	//���⼭ ��� ������ 0~size-1�� ����Ǿ��ٰ� �����Ѵ�.
	for (int i = 0; i < adj.size(); ++i) {
		if (!visited[i])
			dfs(i);
	}
}



/////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////

#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

class Graph {
public:
	int N;		//������ ����
	vector<vector<int>> adj;		//��������Ʈ
	vector<bool> visited;		//�湮����

	//������.
	Graph()
		:N(0) {}
	Graph(int n)
		:N(n) {
		adj.resize(N);
		visited.resize(N);
	}

	//���� �߰� �Լ� (������ �׷���)
	void addEdge(int u, int v) {
		adj[u].push_back(v);
		adj[v].push_back(u);
	}

	//��� �������� �� ������ ��������Ʈ�� ��ȣ������ ����
	void sortList() {
		for (int i = 0; i < N; ++i) {
			sort(adj[i].begin(), adj[i].end());
		}
	}

	//���� �켱 Ž��
	void dfs() {
		fill(visited.begin(), visited.end(), false);
		dfs(0);
	}
private:
	void dfs(int curr) {
		visited[curr] = true;
		cout << "node " << curr << " visited" << endl;
		for (int next : adj[curr]) {
			if (!visited[next])
				dfs(next);
		}
	}

	//dfsAll�� �����Ͽ� ������Ʈ�� ���� ��ȯ
	int dfsAll() {
		int components = 0;
		fill(visited.begin(), visited.end(), false);
		for (int i = 0; i < N; ++i) {
			if (!visited[i]) {
				cout << "-- new DFS begins --" << endl;
				dfs(i);
				components++;
			}
		}
		return components;
	}

	//�� ������Ʈ�� ������ ���ϱ� ���ؼ� dfs �Լ��� �����غ���
	int dfs2(int curr) {
		//���� dfs2�� curr���� dfs�� ���ؼ� �湮�� ������ ���� ��ȯ�Ѵ�.
		int nodes = 1;		//�ڱ� �ڽź��� ���Ƿ� 1
		visited[curr] = true;
		cout << "node " << curr << " visited" << endl;
		for (int next : adj[curr]) {
			if (!visited[next])
				nodes += dfs2(next);
		}
		return nodes;
	}
};


//dfs�� �̿��Ͽ� ����Ŭ ������ ã�Ƴ��� ���
/*
����� �� ������ �湮�� ���۵Ǿ������� üũ�ϴ� �迭�� (visited)
�� ������ �湮�� ������ ���������� üũ�ϴ� �迭�� (finished) �̿��Ѵ�.

1. visited[next] = false, finished[next] = false
--> ���� �湮���� ���� ����
2. visited[next] = true, finished[next] = false
--> here ������ next������ �ϳ��� ����Ŭ�� ������ �� �� �ִ�.
--> �ֳĸ� next�� �湮�Ǿ��µ� ���� ������ ���� ���¿��� here�� �����������Ƿ� next���� DFS�� ������ here�� �ִ��Ű�
--> here���� �ٽ� ���������� ���캸�Ҵµ� next�� �ٽ� �����ϱ� �� ģ������ �ѹ��� dfs�� reachable �� ģ�����̿��� �׷��Ƿ� �� ģ������ �� ����Ŭ�� �ִ�.!
3. visited[next] = false, finished[next] =true
--> �̷� ���� ���� �ֳĸ� ������ ���ߴµ� ���� ���ٴ� �Ŵϱ�
4. visited[next] = true, finished[next] = true
--> next�� �̹� ��� Ž���� �������̹Ƿ� (DFS�� �� ������) here�̶� next�� ���� ����Ŭ�� ���� �� ����.
*/

#include <cstdio>
#include <vector>
#include <algorithm>
using namespace std;

//S[i] �� i������ ����Ű�� ģ�� (���⼭�� �� ������ �ִ� �Ѱ��� ������ ����Ǿ��ٰ� ����.)
int N, S[100000], cnt;		//cnt�� ����Ŭ�� ���ϴ� ������ ����� ����.
bool visited[100000], finished[100000];

void dfs(int curr) {
	visited[curr] = true;		//�湮 ���� ǥ��
	int next = S[curr];
	if (visited[next]) {
		if (!finished[next]) {
			//visited[next] =true, finished[next] =false�� ��� !
			//curr ~ next������ ��� ģ������ �� ����Ŭ�� �̷��. 
			//�� �� �������� �����ؼ� curr���� �Դµ� �̰� �̹� ������ �߰� ���� �ȳ� (�� �̹� dfs����Ŭ�� ���� ģ��)ģ���� �����ٸ�
			//���� ��� ��ۻ�� ������ �׷��� Ŀ�����ְ� ������ �ǿ�~
			for (int temp = next; temp != curr; temp = S[temp])
				cnt++;
		}
	}
	else {
		dfs(next);
	}
	finished[curr] = true;
}

int main() {
	int T;
	scanf("%d", &T);
	for (int t = 0; t < T; ++t) {
		scanf("%d", &N);
		for (int i = 0; i < N; ++i) {
			scanf("%d", S + i);
			S[i]--;
		}

		fill(visited, visited + N, false);
		fill(finished, finished + N, false);
		cnt = 0;
		for (int i = 0; i < N; ++i) {
			if (!visited[i])
				dfs(i);
		}
		printf("%d\n", N - cnt);

	}


}


//////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////


//DFS spanning tree�� ������ �̿��Ͽ� ����� ����Ŭ�� ���θ� �����ϴ� ���


#include <iostream>
#include <vector>
using namespace std;

//��������Ʈ ǥ��
vector<vector<int> > adj;

//discovered[i] = i�� ������ �湮 ���� -> -1�� �ʱ�ȭ
//finished[i] = dfs(i)�� ����Ǿ����� 1 �ƴϸ� 0 -> 0���� �ʱ�ȭ
vector<int> discovered, finished;

//���ݱ��� �湮�� ������ ��
int counter;

void dfs2(int here) {
	discovered[here] = counter++;

	//��� ���������� ��ȸ
	for (int i = 0; i < adj[here].size(); ++i) {
		int there = adj[here][i];
		cout << "(" << here << ", " << there << ") is a ";
		//���� there�� �湮�� ���� ���ٸ� �湮�Ѵ�.
		if (discovered[there] == -1) {
			cout << "tree edge" << endl;
			dfs2(there);
		}
		//there�� �̹� �湮�� �����ε� + here���ٴ� �ʰ� �湮�� �����̶�� 
		else if (discovered[here] < discovered[there]) {
			cout << "forward edge" << endl;
		}
		//there�� �̹� �湮�� �����̰� here���� ���� �湮�� �����϶�
		else if (finished[there] == 0) {
			//���� there�� �湮�� ���۵Ǿ����� ���� ���� �ʾҴٸ�
			//there�� dfs��ȸ�߿� here�� �����ѰŴϱ� there�� here�� ������ �ȴ�.
			//�� �� ������ �����Ⱓ���� �ȴ�.
			//u������ ó�� ����Ŭ�� ���۵ȴٰ� ���� u -> ... -> u�� �ɲ���
			//u���� dfs�� �����ߴٸ� ...�� �ִ� ģ������ u�� dfs �߰��� �湮�ϰ� ���ٵ� �� ģ������ dfs��
			//��������� Ÿ�� �Ǹ� �ᱹ���� u�� ������ �ɲ��� �׶� ���� u�� ��ó�� ���ۿ��� �̹� �������Ƿ�
			//discovered =true �̰� finished = false�� ������ �������� �з��� �ɲ���
			//�׷��ϱ� �̷��� ��������� ���ٰ� ������ �������� ��� �� ����Ŭ�� ���� ģ����
			cout << "back edge" << endl;
		}
		else {
			//there�� �湮�� ���۵Ǿ��� �̹� �������¶�� (here���� ���� �߰ߵǾ���)
			//�� ������ ���������� �ȴ�. (����, �ڼյ� �ƴѻ��°� �ǹǷ�)
			cout << "cross edge" << endl;
		}
	}

	finished[here] = 1;
}

//������ �׷������� ����Ŭ ã��
//dfs���� �ڽ��� �ٷ� �� �θ� �����ϰ� �̹� �湮�� ������ �����Ѵٸ� ����Ŭ�� ���´�.

/*
dfsAll(G){
	//�ʱ�ȭ
	for each vertex v of G{
		color[v] = "white";		//visited
		parent[v] = null;		//�ڽ��� �θ� �������� ����
	}

	//���� �湮���� ���� ������ �ִٸ� dfs
	//DFS�Լ��� ����Ŭ�� �ִٸ� true�� �����Ѵ�.
	for each vertex v of G{
		if( color[v] == "white")
			if(DFS(v)){
				print("Cycle detected"); exit;
			}
	}
	print("No cycle detected");
}

boolean DFS(v){
	color[v] = "Gray";		//�湮�ߴٰ� ǥ��
	//���� ���� ��ȸ
	for( each vertex w adjacent to v){
		//�湮 ���� ���� ���̸� �湮
		if(color[w] == 'white'){
			parent[w] = v;
			DFS(w);
		}
		else if(color[w] == "gray" and parent[w] != v){
			//�̹� �湮�� ���̰� �� ���� ���� �θ� �ƴ϶��(�θ��� �׳� �̾��� ģ����� ������ �����Ƿ� ����Ŭ�� �ƴϾ�)
			return true;	//��
		}
	}
	color[v] = "black";		//�̹� Ȯ���� ģ����� ǥ��
	return false;		//����Ŭ�� ���ٰ� ��ȯ
}
*/

//���� �˰����� ����׷��������� �������� �ʴµ� �ֳĸ� �ٷ��� �θ� �ƴ� �̹� �湮�� ������ �����Ѵٰ� �ؼ�
//�׻� ����Ŭ�̶�� ������ ���� �����̾�
// (1,2), (1,3), (2,4), (3,4) �׷������� 1���������� dfs�� �ϸ� 2��, 4���� �湮�ϰ� �ٽ� �ö�ͼ�
//3���� Ÿ�� 4���� üũ�ϰ� �Ǵµ� 4���� �̹� �湮�� �����̰� 3���� �ٷ��� �θ� �ƴ����� �̰� ����Ŭ�� �ƴϾ�
//���⼺�� �ֱ� ������¡

//���� (1,2), (2,1) �׷��������� ���� 2������ �ڽ� �ٷ����� ������ �����ϰ�� �̹� �湮�� ���� �� �� �ִ°� ���
//���� �˰������δ� false�� �����ϰ����� �̰� ����Ŭ�� �ִ� �׷������� ��Ȯ��

//directed �׷��������� back edge�� �ִٸ� ����Ŭ�� �������� ��Ȯ��
//�ֳĸ� ������ ���� �������ٰ� ���� �����ִ� dfs�� ���� ������ ������ �� �ִٴ°��� back edge�ε�
//�׷��� �Ǹ� �װ� Ÿ�� �ö󰡸� �ٽ� �� �����ü� �����ϱ� �̰� ����Ŭ�� �Ǵ°ž�

/*
dfsAllVertices(G){
	color all vertices white;		//�ʱ�ȭ
	for (each v in V){
		if(v is white){
			if(DFS(v)){
				print("Cycle detected");
			}
		}
	}
	print("No Cycle detected")
}

boolean DFS(v){
	color[v] = 'gray';
	for(each w adjacent to v){
		if(color[w] == 'gray')		//back edge
			return true;
		if(color[w] == 'white')
			DFS(w)
	}
	color[v] = black;
	return false;
}
*/