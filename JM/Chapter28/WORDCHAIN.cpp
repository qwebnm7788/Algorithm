/*
헤밀토니안경로 = 그래프의 모든 정점을 한번씩만 방문하는 경로를 말한다. (이때는 간선은 여러번 거쳐도 된다.)
*/
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
using namespace std;

//adj[i][j] = i-j사이의 간선의 수
vector<vector<int>> adj;
//graph[i][j] = i로 시작해서 j로 끝나는 단어의 목록
vector<string> graph[26][26];

//indeg[i] = i로 끝나는 단어의 수
//outdeg[i] = i로 시작하는 단어의 수
vector<int> indeg, outdeg;
void makeGraph(const vector<string>& words) {
	//전역변수 초기화
	for (int i = 0; i < 26; ++i)
		for (int j = 0; j < 26; ++j)
			graph[i][j].clear();
	adj = vector<vector<int>>(26, vector<int>(26, 0));
	indeg = outdeg = vector<int>(26, 0);

	//모든 단어를 그래프에 추가해준다.
	for (int i = 0; i < words.size(); ++i) {
		int a = words[i][0] - 'a';		//첫글자.
		int b = words[i][words[i].size() - 1] - 'a';		//마지막글자.
		graph[a][b].push_back(words[i]);
		adj[a][b]++;
		outdeg[a]++;
		indeg[b]++;
	}
}

//here에서 시작하는 오일러 회로의 역순을 반환한다.
void getEulerCircuit(int here, vector<int>& circuit) {
	for (int there = 0; there < adj.size(); ++there) {
		while (adj[here][there] > 0) {
			adj[here][there]--;
			getEulerCircuit(there, circuit);
		}
	}
	circuit.push_back(here);
}

//오일러 회로나 경로를 반환한다.
//오일러 경로가 존재하려면 indeg[x]+1 == outdeg[x] 인 점과 outdeg[y]+1 == indeg[y] 인 정점 x,y가 존재해서
//y->x 간선을 이어서 얻어주면 된당. 근데 실제로는 알아서 잘 얻어진다.
vector<int> getEulerTrailOrCircuit() {
	vector<int> circuit;
	//indeg[x]+1 == outdeg[x] 가 성립하는 정점이 존재한다면 오일러 경로가 존재한다.
	for (int i = 0; i < 26; ++i) {
		if (outdeg[i] == indeg[i] + 1) {
			getEulerCircuit(i, circuit);
			return circuit;
		}
	}

	//경로의 가능성이 없다면 회로다 !
	for (int i = 0; i < 26; ++i) {
		if (outdeg[i]) {
			getEulerCircuit(i, circuit);
			return circuit;
		}
	}
	
	//전부 실패하면 빈 배열
	return circuit;
}

//오일러 경로/회로가 존재하는지의 여부를 반환한다.
bool checkEuler() {
	int plus1 = 0, minus1 = 0;		//시작점의 수, 끝점의 수
	for (int i = 0; i < 26; ++i) {
		int delta = outdeg[i] - indeg[i];
		//정점의 차수의 차이는 -1,1,0이어야 한다.
		if (delta < -1 || delta > 1)
			return false;
		if (delta == -1)
			plus1++;
		if (delta == 1)
			minus1++;
	}

	//오일러 경로가 존재하려면 1, -1이 한번씩만 존재했어야 하고
	//오일러 회로가 존재한다면 전부다 0이었어야 한다.
	return (plus1 == 1 && minus1 == 1) || (plus1 == 0 && minus1 == 0);
}

string solve(const vector<string>& words) {
	makeGraph(words);
	//존재 조건 자체가 안되면 실패!
	if (!checkEuler())
		return "IMPOSSIBLE";

	//오일러 회로/경로를 찾아낸다.
	vector<int> circuit = getEulerTrailOrCircuit();

	//이때 모든 간선을 모두 돌아보지 못했다면 안된다.
	//한번의 시도에서 모든 간선을 돌아보지 못했다면 연결그래프가 아니라는 말이 되는데 이렇게 되면
	//모든 단어를 사용하지 못한것이 된다.
	//circuit의 길이는 words의 갯수보다 하나 크다. (왜냐면 끝점에서 시작점으로 돌아와야 하니깐)
	if (circuit.size() != words.size() + 1)
		return "IMPOSSIBLE";

	//뒤집힌것을 되돌린다.
	reverse(circuit.begin(), circuit.end());
	string ret;
	for (int i = 1; i < circuit.size(); ++i) {
		int a = circuit[i - 1], b = circuit[i];
		//처음만 제외하고
		if (ret.size())
			ret += " ";
		ret += graph[a][b].back();
		graph[a][b].pop_back();
	}
	return ret;
}

int main() {
	freopen("input.txt", "r", stdin);

	int test;
	cin >> test;

	for (int z = 0; z < test; ++z) {
		int n;
		cin >> n;

		vector<string> words(n);
		for (int i = 0; i < n; ++i)
			cin >> words[i];
		cout << solve(words) << endl;
	}
}