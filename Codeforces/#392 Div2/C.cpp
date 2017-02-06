/*
758C - Unfair Poll

질문을 하는 순서를 잘 살펴보자 (마지막줄은 한번만 물어보고 돌아온다는것에 주의!)
1번줄 -> 2번줄 -> ... -> n-1번줄 -> n번줄 -> n-1번 줄 -> ... -> 2번줄

이렇게 하면 한 주기가 끝난다고 생각해보자.
그 이후로는 다시 처음부터 주기를 반복하면 모듈러 연산을 이용할 수 있다.

이 주기의 길이를 T라고 하면 T = nm(처음 1~n줄까지) + (n-2)m (첫줄,n번줄 제외) 돌아올때의 카운팅이 되어서
T = nm + (n-2)m 번이 된다.
여기서 n >=2 여야 되므로 n=1 일경우는 예외적으로 처리를 해주어야 된다.
n = 1이면 T = m 이 된다. (첫번째 줄만 다 돌면되니깐)

이렇게 되면 full period 의 수는 (즉 완전히 주기를 다 도는 횟수는)
k/T가 된다 그러고 나서 k mod T가 남게 되는게 이친구들은 그냥 O(nm)으로 돌면서
체크를 해주면 다 구할 수 있다.

따라서 이 체크의 시간복잡도는 우선 k mod T == 0 이 된다면 O(1)에 구할 수도 있고
그렇지 않다면 최악의 경우는 O(nm)에 구할 수 있게 된다.

또한 재미있는 점은 최대의 질문을 받는 친구의 후보는 정해져있다는 것이다.
첫번째로 맨 첫줄의 첫번째 친구인데 왜냐면 시작이 그 친구부터 이기 때문에 가능성이 있다. (아예 한 주기도 돌지 못하는 경우를 위해서 이다.)
두번째로는 두번째 줄의 첫번째 친구이다 왜냐면 두번째 줄부터는 full period 에서 2번씩 방문이 되기도 하고
각 줄의 왼쪽친구부터 질문을 던질꺼기 때문에 이 친구가 inner 친구중에서 대상이 된다.
세번째로는 깜빡할 수 있는데 n-1번 줄의 첫번째 친구가 된다. 왜냐면 이 친구까지만 2번을 방문받을 수 도 있기 때문이야(inner들 중에서)

따라서 maximum number of asked question 은 위의 값들을 f(x,y)라고 한다면
max(f(1,1), f(2,1), f(n-1,1))이 된다.

또한 minimum number of asked question 은 맨 첫줄과 맨 마지막줄이 후보가 된다.
왜냐면 이 친구들은 남들보다는 최소 작거나 같은 횟수를 받을꺼야 왜냐면 한 주기에 이친구들은 무조건 한번 이하씩만 방문되기 때문이야
*/


#include <iostream>
#include <limits>
using namespace std;

const long long INF = numeric_limits<long long>::max();
long long arr[101][101];

int main(){
	long long n,m,k,x,y;
	cin >> n >> m >> k >> x >> y;

	if(n==1){
		for(int i = 0; i < m; ++i)
			arr[0][i] += k/m;
		k = k % m;
	}else{
		for(int i = 0; i < n; ++i){
			for(int j = 0; j < m; ++j){
				if(i==0 || i == n-1)
					arr[i][j] += k / (n*m+(n-2)*m);
				else
					arr[i][j] += 2*(k / (n*m+(n-2)*m));
			}
		}
		k = k % (n*m+(n-2)*m);
	}	

	for(int i = 0; i < n; ++i){
		for(int j = 0; j < m; ++j){
			if(k>0){
				arr[i][j]++;
				k--;
			}
		}
	}

	for(int i = n-2; i >= 1; --i){
		for(int j = 0; j < m; ++j){
			if(k>0){
				arr[i][j]++;
				k--;
			}
		}
	}

	//혹은 arr[i][j]의 모든 값을 vector에 넣고 sort해도 된다.! 0번이 최소값 n*m-1번이 최대값이겠죵?

	long long maxVal = 0;
	long long minVal = INF;

	for(int i = 0; i < n; ++i){
		for(int j = 0; j < m; ++j){
			if(arr[i][j] > maxVal)
				maxVal = arr[i][j];
			if(arr[i][j] < minVal)
				minVal = arr[i][j];
		}
	}

	cout << maxVal << " " << minVal << " " << arr[x-1][y-1];
}