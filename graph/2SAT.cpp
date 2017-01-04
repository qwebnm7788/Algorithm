//2-SAT 함의 그래프 생성 예시
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

//그래프의 인접리스트 표현
vector<vector<int>> adj;

//회의시간이 서로 겹치지 않으면 true를 리턴한다.
bool disjoint(const pair<int, int>& a, const pair<int, int>& b) {
	return a.second <= b.first || b.second <= a.first;
}

//meetings[]를 각 팀이 원하는 회의 시간의 목록
//i번 팀의 원하는 시간은 meetings[2*i] 또는 meetings[2*i+1]중 하나이고 둘 중 하나를 꼭 해야 한다.
//함의 그래프 생성 함수
void makeGraph(const vector<pair<int, int>>& meetings) {
	int vars = meetings.size();

	//그래프는 각 변수마다 두개의 정점을 갖는다. (x||y) 은 x -> !y 와 y -> !x 로 표현가능하니깐
	adj.clear();
	adj.resize(vars * 2);
	for (int i = 0; i < vars; i += 2) {
		//우선 여기서는 (i||j)절을 추가한다. 둘 중 하나를 꼭해야 하니깐 !
		int j = i + 1;
		adj[i * 2 + 1].push_back(j);		//!i -> j
		adj[j * 2 + 1].push_back(i);		//!j -> i
	}

	//i번 회의와 j번 회의가 겹치는 회의라면 그 둘은 발생해서는 안되는 친구이므로 (!i || !j) 절을 추가해주면 된다. -- 즉 동시에 참이 되지 않는 점을 추가.!
	for (int i = 0; i < vars; ++i) {
		for (int j = 0; j < i; ++j) {
			if (!disjoint(meetings[i], meetings[j])) {
				//i번 이 열리지 않거나 j번이 열리지 않는 함의 !
				//(!i || !j) 는 i -> !j 와 j -> !i로 표현가능하다.
				adj[2 * i].push_back(2 * j + 1);
				adj[2 * j].push_back(2 * i + 1);
			}
		}
	}
}


/*
이제 보면 어떤 절 (X||Y)가 거짓이라면 !X -> Y 이고 !Y -> X인 친구들을 갖게 되는데
이걸 잘 보면 (X||Y)가 거짓이니깐 X 와 Y모두 거짓이고 !X->Y 는 참 -> 거짓
!Y->X도 참 -> 거짓인 친구임을 알 수 있어
그러니깐 참 -> 거짓으로 가는 친구가 없게끔 최대한 해주면 모든 절을 참으로 만들어서 우리가 원하는 조건식을
참으로 만들어줄 수 있을꺼야

1. x 정점과 !x 정점은 하나는 참, 하나는 거짓으로 분류되도록 한다.
2. 그리고 참 -> 거짓으로 가는 경로는 없다.

이 두 조건을 만족하면서 함의 그래프를 형성 할 수 있다면 해를 구할 수 있다.

이걸 만족하지 않는 경우를 보면 예를 들면 한 사이클에 x정점과 !x정점이 모두 속해있는 경우야
사이클은 계속 빙글빙글 도는데 x -> ... -> !x -> ... -> x 가 되는데 x와 !x는 둘 중 하나는
거짓이 될꺼야 그러면 참 -> 거짓인 경로가 생기게 되니깐 위의 조건을 만족하지 못하게 되지 !

이런 그래프의 형성은 SCC로 표현할 수 있어

특징은 이게 x와 !x은 서로 대칭적인 속성을 가져서
SCC로 압축해주면 그래프가 대칭인 그래프가 생긴다는거

이제 이 압축한 그래프를 이용해서 2-SAT을 풀어보면 이 압축 그래프는 DAG임을 알 수 있고
여기서 indeg가 0 인 친구를 일단 다 찾아
그리고 이 중에 한 친구를 최대한 거짓으로 분류한다음에
그에 대칭되는 정점은 참으로 만들어 주고 이 정점을 지워주면 된다.

이 과정을 계속 반복하면 된다.

이게 왜 되냐면 p->q에서 p를 거짓으로 만들어 주면 q는 거짓이던 참이던 이 명제는 항상 참이야
그래서 손해를 볼 일이 없어

만약에 저기서 indeg = 0인 친구를 골랐는데 이미 참으로 분류가 되어있다면 이 친구는 그냥 건너 뛰면 되겠징?

*/

vector<int> solve2SAT() {
	int n = adj.size() / 2;		//변수의 수! 그래프의 크기는 두배니깐 절반

	//함의 그래프를 SCC의 요소별로 묶는다.
	vector<int> label = tarjanSCC();		//tarjanSCC는 SCC 컴포넌트로 분류한 결과

	//이 SAT 문제가 해결 가능한지 확인
	//만약에 x와 !x가 하나의 SCC에 속한다면 불가능 하겠죵 참 -> 거짓이 생기니깐
	for (int i = 0; i < 2 * n; i += 2) {
		if (label[i] == label[i + 1])
			return vector<int>();	//안돼면 그냥 빈 벡터
	}

	//가능하다면
	vector<int> value(2 * n, -1);

	//타잔 알고리즘은 SCC를 위상정렬의 역순으로 번호를 매기는 특징을 이용하면
	//따로 압축하고 위상정렬할 필요 없이 바로 값을 구할 수 있다.
	vector<pair<int, int>> order;
	for (int i = 0; i < 2 * n; ++i) {
		order.push_back(make_pair(-label[i], i));		//역순으로 집어넣을라고 SCC의 번호를 음수를 붙여서 정렬했따.
	}
	sort(order.begin(), order.end());		//그래서 이걸 하면 위상정렬한 순서로 order에 들어가게 된다. order.second에 정점번호!

	//각 정점에 값을 배정
	for (int i = 0; i < 2 * n; ++i) {
		int vertex = order[i].second;
		int variable = vertex / 2;	
		int isTrue = vertex % 2 == 0;
		if (value[variable] != -1)		//이미 결정된 친구면 건너뛰공
			continue;

		//먼저 만나는 정점을 거짓으로 만들어 주면 된다.
		//!x가 x보다 먼저 나왔다면 x는 참
		//x가 !x보다 먼저 나왔다면 x는 거짓
		value[variable] = !isTrue;		//variable의 값은 isTrue의 반전과 같은데
		//variable(x)가 참인지 거짓인지는 vertex의 값이 참이라면 2*i니깐 0으로 istrue가 참이고
		//거짓 정점을 먼저 만났다면 2*i+1로 isTrue가 거짓이 되니깐 거짓이 된다.
		//위에서 이미 값이 정해진 친구는 건너뛰니깐 둘중 하나의 값만 저장됨을 알 수 있다.
	}

	return value;

}