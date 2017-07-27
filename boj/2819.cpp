/*
단순하게 시뮬레이션 하여 모든 instruction을 돌아보며
매번 거리를 계산해주게 되면 O(NM)이 되어 시간초과를 받게 된다.

모든 조사점의 위치를 x좌표, y좌표를 따로 관리하는 배열을 만들어 주고
정렬해주자.

매 단계의 명령어에 따라서 (0,0)에서 시작한 위치를 갱신시켜주면서 
다음과 같이 빠르게 변화량을 구해줄 수 있다.

1) 북쪽 방향으로 이동한다면
cY를 포함한 (같은 y좌표를 같는) 위쪽에 있는 조사점까지의 거리는 모두 -1이 될 것이다.
밑에 있는 정점들에게는 모두 +1이 된 효과와 같다

cY 밑에 있는 정점의 집합을 F라고 한다면 이 친구들의 갯수는 lower_bound 를 이용하여 cY를 검색하여 O(logM)에 구해줄 수 있다
2) 남쪽 방향으로 이동한다면
비슷하게 cY를 포함한 아래쪽 방향의 조사점들은 모두 거리가 -1씩이 될 것이고
위에 있는 친구들에게는 +1씩이 될것이다.

아래의 친구들을 upper_bound로 갯수를 구해줄 수 있다.( 이번에는 cY와 같은 정점을 포함해야 하므로 upper_bound를 사용하였다)
이렇게 되면 기존의 정답 answer 는 answer = answer - F + (n-F)  즉 F만큼 -1이 되고 위 쪽 정점들 (n-F) 만큼 + 1이 된다.

나머지 동쪽, 서쪽에 대해서도 비슷한 방법으로 구해줌으로써
O(NlogM)에 정답을 구해줄 수 있다.

cin , cout을 사용하게 되면 시간초과를 받으므로 scanf,printf 함수를 이용하자.
*/
#include <cstdio>
#include <vector>
#include <string>
#include <cmath>
#include <algorithm>
using namespace std;

const int MAXM = 300005;

int main() {
	int n, m;
	scanf("%d %d", &n, &m);

	long long answer = 0;

	vector<int> xcor(n), ycor(n);
	for (int i = 0; i < n; ++i) {
		scanf("%d %d", &xcor[i], &ycor[i]);
		answer += abs(xcor[i]) + abs(ycor[i]);
	}

	sort(xcor.begin(), xcor.end());
	sort(ycor.begin(), ycor.end());

	char inst[MAXM];
	scanf("%s", inst);

	int cX, cY;
	cX = cY = 0;

	for (int i = 0; i < m; ++i) {
		if (inst[i] == 'S') {		//north
			cY++;
			answer += 2 * (lower_bound(ycor.begin(), ycor.end(), cY) - ycor.begin()) - n;
		}
		else if (inst[i] == 'J') {	//south
			cY--;
			answer += n - 2 * (upper_bound(ycor.begin(), ycor.end(), cY) - ycor.begin());
		}
		else if (inst[i] == 'I'){	//east
			cX++;
			answer += 2 * (lower_bound(xcor.begin(), xcor.end(), cX) - xcor.begin()) - n;
		}
		else{						//west
			cX--;
			answer += n - 2 * (upper_bound(xcor.begin(), xcor.end(), cX) - xcor.begin());
		}
		
		printf("%lld\n", answer);
	}
}