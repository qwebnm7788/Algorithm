//board[y][x] = (x,y)좌표에 써있는 숫자.
int n, board[100][100];

//jump(y,x) = (x,y)좌표에서 오른쪽 or 아래로 이동하여 도착점(n-1,n-1)에 도달할 수 있는가?
bool jump(int y, int x){
	//range check
	if(y >= n || x >= n)
		return false;

	//base case
	if(y == n-1 && x == n-1)
		return true;

	int jumpSize = board[y][x];
	//오른쪽 혹은 아래쪽으로 점프를 해본다. (둘 중 하나라도 성공한다면 이 위치에서는 도달 가능하다.)
	return jump(y+jumpSize,x) || jump(y,x+jumpSize);
}

/*
이러한 완전탐색 알고리즘을 이용한다면 최악의 경우 탐색하는 경우의 수가 지수적으로 늘어난다. (이번의 경우에는 매번 케이스가 2개씩 늘어나므로 2^n 이 된다.)

이 때 jump에 주어지는 x,y의 종류는 x, y <= 100 이기 때문에 100*100 = 10000개 뿐이 안된다는 사실을 인지하면
2^n 보다는 훨씬 적다는 것을 통해서 비둘기집의 원리로 인해 중복되는 경우의 수가 상당히 많음을 알 수 있다.

또한 jump 함수는 주어진 x,y값에 의해서만 결과값이 좌우되는 참조적 투명함수 이기 때문에
메모이제이션을 이용하여 문제를 최적화 시켜줄 수 있다.
*/

//memoization 적용 코드
//여기서 포인트는 cache 배열은 이 부분문제가 계산된 것인지 아닌지를 확인하기 위해서 true, false 뿐 아니라(계산결과) 계산 여부를 표기할 다른 방법이 필요하기 떄문에
//int 형으로 jump2를 설계하고 -1이라면 계산하지 않은 것으로 한다.

int n, board[100][100];
int cache[100][100];		//cache[y][x] 배열에 (x,y)좌표의 계산된 결과값을 저장해주고 중복된 계산을 피해준다.
int jump2(int y, int x){
	//range check 		(x,y) = (0,0)에서 시작하고 오른쪽, 아래쪽으로만 가기 때문에 0밑으로 떨어지는 체크는 불필요하다.
	if( y >= n || x >= n)
		return 0;
	if( y == n-1 &&  x == n-1)
		return 1;
	//ret은 참조형이다.
	int& ret = cache[y][x];

	if(ret != -1)
		return ret;
	int jumpSize = board[y][x];
	//true = 1, false = 0으로 계산됨을 이용하였다.
	return ret = (jump2(y+jumpSize,x) || jump2(y,x+jumpSize));

}



/*
만약 그래프 문제를 동한다면
각 board[y][x] 의 값을 통해서 그 만큼의 거리에 있는 오른쪽, 아래쪽에 있는 정점을 이어놓고
모든 정점에 대해서 이 작업을 하게 되면 각 정점들은 모두 2~4개의 정점과 이어져있는 그래프가 형성되게 된다. O(4*n) 개의 정점인가.?

이 상태에서 (0,0) 정점에서 BFS, DFS등의 탐색을 진행하여서 (n-1,n-1)정점까지의 reachability를 체크하는 문제로 모델링 하여 간단하게 풀 수 있다.
*/

//이때 직접 노드와 간선을 만들어주지 말고 함의 그래프를 통해서 진행해보자. 
//DFS 이용

int n, board[100][100];
bool reachable[100][100];
//[y][x] 정점에서 DFS를 진행하며 도달 가능한 점에 표시한다.
void dfs(int y, int x){
	if(y >= n || x >= n)
		return false;
	if(y == n-1 && x == n-1)
		return true;
	reachable[y][x] = true;
	int jumpSize = board[y][x];

	if(!reachable[y+jumpSize][x])
		dfs(y+jumpSize,x);
	if(!reachable[y][x+jumpSize])
		dfs(y,x+jumpSize);
}

/*
Accepted code

1.memoization ver

#include <iostream>
using namespace std;

int n;
int board[100][100];
int cache[100][100];

int jump(int y, int x) {
	if (y >= n || x >= n)
		return 0;
	if (y == n - 1 && x == n - 1)
		return 1;
	int& ret = cache[y][x];
	if (ret != -1)
		return ret;

	int jumpSize = board[y][x];
	return ret = (jump(y + jumpSize, x) || jump(y, x + jumpSize));
}
int main() {
	freopen("input.txt", "r", stdin);
	int test;
	cin >> test;
	
	for (int z = 0; z < test; ++z) {
		cin >> n;
		for (int i = 0; i < n; ++i)
			for (int j = 0; j < n; ++j)
				cin >> board[i][j];
		fill(&cache[0][0], &cache[0][0] + sizeof(cache) / sizeof(cache[0][0]), -1);
		if (jump(0, 0))
			cout << "YES\n";
		else
			cout << "NO\n";
	}
}

*/


/*

2. DFS reachability ver

#include <iostream>
using namespace std;

int n;
int board[100][100];
bool reachable[100][100];

void dfs(int y, int x) {
	if (y >= n || x >= n)
		return;
	reachable[y][x] = true;
	int jumpSize = board[y][x];
	if (!reachable[y + jumpSize][x])
		dfs(y + jumpSize, x);
	if (!reachable[y][x + jumpSize])
		dfs(y, x + jumpSize);
}
int main() {
	freopen("input.txt", "r", stdin);
	int test;
	cin >> test;
	
	for (int z = 0; z < test; ++z) {
		cin >> n;
		for (int i = 0; i < n; ++i)
			for (int j = 0; j < n; ++j)
				cin >> board[i][j];
		fill(&reachable[0][0], &reachable[0][0] + sizeof(reachable) / sizeof(reachable[0][0]), false);
		dfs(0, 0);
		if (reachable[n - 1][n - 1])
			cout << "YES\n";
		else
			cout << "NO\n";
	}
}

*/
