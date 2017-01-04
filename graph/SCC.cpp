#include <iostream>
#include <vector>
#include <stack>
#include <algorithm>
using namespace std;

const int MAX = 10000;

//SN -> SCC의 갯수 sn[i] -> i 정점이 속한 SCC의 번호

int V, E, cnt, dfsn[MAX], SN, sn[MAX];
vector<int> adj[MAX];
//SCC로 추출되었는지의 여부를 저장.
bool finished[MAX];
stack<int> S;
vector<vector<int>> SCC;

//자신이 도달 가능한 곳 중 가장 빠른 방문순서를 반환한다.
int dfs(int curr) {
	//방문 순서 저장
	dfsn[curr] = ++cnt;
	//스택에 저장
	S.push(curr);

	//result는 반환값
	int result = dfsn[curr];
	//인접 정점 순회
	for (int next : adj[curr]) {
		//아직 방문하지 않은 이웃
		if (dfsn[next] == 0) {
			//next로 내려가서 next를 루트로 하는 서브트리의 dfs 결과 값과 result를 비교해서 최소값을 얻는다.
			result = min(result, dfs(next));
		}
		else if (!finished[next]) {
			//방문은 했는데 아직 SCC로 추출되지 않은 정점
			result = min(result, dfsn[next]);
		}
	}

	//curr이 나의 밑에 친구들이 도달 가능한 최고 높은 정점인 경우에는 SCC를 추출한다.
	//내 밑에 서브트리가 (그 중에는 이미 SCC로 뽑혀나간 친구도 있을 수 있어) 하나의 SCC를 이룬다.
	if (result == dfsn[curr]) {
		vector<int> currSCC;

		while (1) {
			int t = S.top();
			S.pop();
			currSCC.push_back(t);
			finished[t] = true;
			sn[t] = SN;
			if (t == curr)
				break;
		}
		SCC.push_back(currSCC);
		SN++;
	}

	return result;
}


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////



#include <iostream>
#include <vector>
#include <stack>
#include <algorithm>
using namespace std;

//그래프의 인접리스트 표현
vector<vector<int>> adj;

//각 정점의 컴포넌트 번호 (0부터 시작)
//같은 SCC에 속하는 정점은 이 컴포넌트 번호가 동일 하다.
vector<int> sccId;

//각 정점의 발견 순서
vector<int> discovered;

//정점의 번호를 담는 스택
stack<int> st;

int sccCounter, vertexCounter;

//here를 루트로 하는 서브트리에서 역방향 간선/ 교차간선을 통해서 갈 수 있는 정점 중 최소 발견순서를 반환한다.
//이미 SCC로 묶여진 친구로 가는 교차간선은 무시하는데 왜냐면 그 친구를 통해서는 내가 거기로는 갈 수 있지만 거기서는 내 쪽으로 올 수 없기 떄문(방향 그래프니깐)
int scc(int here) {
	int ret = discovered[here] = ++vertexCounter;

	//스택에 here을 넣는다. here의 후손들은 모두 스택에서 here위로 올라가게 되는데
	//나중에 SCC를 뽑을 때 here까지 뽑는 형식으로 here과 같은 SCC에 있는 것을 만들어줄 수 있다.

	for (int i = 0; i < adj[here].size(); ++i) {
		int there = adj[here][i];

		//(here,there)이 tree edge
		if (discovered[there] == -1) {
			ret = min(ret, scc(there));
		}
		else if (sccId[there] == -1) {
			//there이 무시해야 하는 cross edge가 아니라 아직 scc로 커팅이 안된 친구라면 체크 해봐야 해
			//역방향 간선이라면 there이 here의 조상이라는 소리고 there의 발견순서랑 ret을 비교해서 최소값을 보면된다.
			//순방향 간선이라면 there이 here의 자손이라는 소리인데 scc로 이미 뽑혔다면 서로 다른 SCC에 속한다는 의미가 되니깐 꼭 체크할 필요가 없다.
			//그런데 scc로 뽑히지 않았다면 순방향 간선은 here에서 there로 다른경로로 한번 갔다왔다는 것인데 그 때 재귀가 풀리면서 정보를 다 얻어왔을꺼야
			//그러면 내가 순방향친구를 꼭 따라가지 않아도 내가 얻을 수 있는 정보는 다 얻어왔을 꺼야
			//교차간선중에 이미 SCC로 뽑힌 친구들은 거기서 이쪽 트리로 넘어오지 못하기 때문에 커팅을 한것이니깐 그 친구들을 체크할 필요는 없당.
			ret = min(ret, discovered[there]);
		}
	}

	//here에서 부모로 올라가는 간선을 끊을지 여부를 체크한다.
	if (ret == discovered[here]) {
		//here를 루트로하는 서브트리에서 올라갈 수 있는 최대 높이가 결국은 here까지밖에 되지 못한다면
		//here에서 here의 부모로 올라가는 간선을 커팅해서 here밑의 친구들은 하나의 SCC 에 속함을 알 수 있다.
		
		//그러면 here을 루트로 하는 서브트리에서 스택에 남아있는 친구들을 모두 하나의 컴포넌트로 묶는다 (이 내부에 또 다른 SCC가 있을 수 있고 그건 이미 스택에서 빠졌을꺼야)
		while (true) {
			int t = st.top();
			st.pop();
			sccId[t] = sccCounter;
			if (t == here)
				break;
		}

		++sccCounter;
	}
	return ret;

}


//타잔 알고리즘
vector<int> tarjanSCC() {
	//배열 모두 초기화
	sccId = discovered = vector<int>(adj.size(), -1);

	//카운터초기화
	sccCounter = vertexCounter = 0;

	//모든 정점에 대해서 scc 호출 -> 왜냐면 연결 그래프가 아닐 수 있기 때문이지
	for (int i = 0; i < adj.size(); ++i) {
		if (discovered[i] == -1)
			scc(i);
	}
	return sccId;
}


