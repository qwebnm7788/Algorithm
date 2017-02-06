/*
이 문제를 풀떄 우선
완전탐색을 생각해볼수 있다.
path(y,x,sum) = 현재 (y,x)위치에 있고 현재까지의 합이 sum일때 맨밑으로 내려갔을때 얻을 수 있는 최대합을 반환한다.
-> path(y,x,sum) = max(path(y+1,x,sum+cost[y+1][x]),path(y+1,x+1,sum+cost[y+1][x+1])) 이 된다.

그러나 이런식으로 구하게 되면 한 줄에 n개의 원소가 있다면 2^(n-1)개의 문제가 생기게된다. (각 원소당 2개씩 늘어난다)

여기서 중복되는 문제에 메모이제이션을 적용해보자.
*/

//MAX_NUMBER = 한 칸에 들어갈 수 있는 숫자의 최대치
int n, cost[100][100];		//cost[y][x] = (y,x)점에 쓰여진 숫자.
//cache[y][x][sum] = (y,x,sum)일때의 값을 저장해둔다. 이때 sum에 들어갈 수 있는 최대의 값은 n <= 100 이므로 맨 꼭대기 친구가 100개의 원소를 거쳐서(나 포함)
//얻은 합일 수 있으니 100*(각 칸에 들어갈 수 있는 최대의 값) 이 된다.
int cache[100][100][MAX_NUMBER*100 + 1]; 		

//(y,x)위치까지(포함) sum일때 맨 아래줄까지 내려가서 얻을 수 있는 합의 최대값을 반환한다.
int path(int y, int x, int sum){
	//base case : 맨 아래줄 도달
	if(y == n-1)
		return sum + cost[y][x];
	//memoization
	int& ret = cache[y][x][sum];
	if(ret != -1) return ret;
	sum += cost[y][x];
	return ret = max(path(y+1,x,sum),path(y+1,x+1,sum));
}
												
/*
위의 구현상의 문제는 우선 cache 배열이 MAX_NUMBER가 크면 클수록 너무 커진다는 것이다.

또 다른 문제는 다음과 같다.
만약 주어진 삼각형의 모든 원소가 2^i 의 값을 갖는다고 하면 우리가 계산하는 각 원소마다 2개의 원소들은 항상 sum을 다른값을 가진다(즉 경로마다 모든 sum값이 다르다.)
*/																		

/*
이 친구를 최적화하려면 어떻게 해야할까
우선 위의 알고리즘에 y,x의 역할을 보면 이친구들은 다음에 아직 풀지못한 부분문제가 어떤것인지 알려주는 친구들이다 (y+1,x), (y+1,x+1)
sum은 무슨역할일까? 이 친구는 지금까지 풀어온 부분문제의 정보이다. (지금까지의 합)
그런데 이게 아직 풀지못한 부분문제의 답을 구하는데 영향을 줄까?
즉 (y+1,x),(y+1,x+1)로 각각가서 맨밑까지의 최대합을 구하는데 영향을 주는걸까? 그렇지 않다.
왜냐면 이 sum은 변하지 않는 값이니깐 이 밑에서의 최대 경로는 sum에 영향을 받지 ㅁ않는다. sum 이 얼마던 간에 (y+1,x),(y+1,x+1) 중 누가 더 큰 경로인지의 결과에는
영향을 주지 못한다. 왜냐면 둘다 같은 값을 받으니깐

따라서 이러한 함수의 정의를 살짝 바꿔보자.

path2(y,x) = (y,x)에서 시작해서 맨 아랫줄까지 가는 부분경로의 최대합 을 반환하게 하자.
즉 이제 ㅇ이 친구들은 아직 해결하지못한 부분문제의 답만을 반환한다.
*/

int n,cost[100][100];
int cache[100][100];

int path2(int y, int x){
	if(y==n-1) return cost[y][x];
	int& ret = cache[y][x];
	if(ret != -1) return ret;
	return ret = max(path2(y+1,x),path(y+1,x+1)) + cost[y][x];
}

/*
Accepted code

#include <iostream>
#include <algorithm>
using namespace std;

int cost[101][101];
int cache[101][101];
int n;
//(y,x)위치에서 시작해서 맨 아랫줄까지 가는 부분경로의 최대합을 반환
int path(int y, int x) {
	if (y == n - 1) return cost[y][x];		//base case
	int& ret = cache[y][x];
	if (ret != -1) return ret;
	return ret = max(path(y + 1, x), path(y + 1, x + 1)) + cost[y][x];
}

int main() {
	ios_base::sync_with_stdio(false);
	int test;
	cin >> test;

	for (int z = 0; z < test; ++z) {
		cin >> n;

		for (int i = 0; i < n; ++i) {
			for (int j = 0; j <= i; ++j) {
				cin >> cost[i][j];
				cache[i][j] = -1;
			}
		}
		cout << path(0, 0) << endl;
	}
}
*/
