/*
구간 트리(Segment Tree)

일차원 배열의 특정구간에 대한 질의에 빠르게 대답하는 곳에 주로 사용된다.

배열의 구간을 표현하는 이진트리로 트리를 만드는 것이 주요 아이디어이다.
이 때 루트노드는 항상 배열 전체의 구간인 [0,n-1]을 표현한다.
루트 노드의 왼쪽 자식과 오른쪽 자식은 각각 해당 구간의 왼쪽 절반과 오른쪽 절반을 표현한다.
그렇게 되면 길이가 1인 구간을 표현하는 노드는 이 트리의 리프노드가 됨을 알 수 있다.

이런식으로 표현한 트리의 각 노드에 대해서 그 노드가 표현하는 구간에 대해서 원하는 값을 저장해 놓으면 된다.
이러한 전처리 과정을 해놓으면 어떤 특정 구간[i,j]에 대해서 원하는 값을 구하고 싶다면 이 구간트리의 노드에 포함된 구간에 포함된 친구들의
합집합을 이용함으로써 답을 빠르게 구해 낼 수 있다.
*/

/*
특정 구간의 최소값을 구하는 문제를 RMQ(range minimum query)라고 하는데 이러한 문제를 구간 트리를 이용하여 풀 수 있다

이 트리는 비교적 꽉 찬 트리에 속하게 되는데 왜냐면 위에서 말했듯이 구간을 계속 절반으로 나누면서 좌우의 자식으로 이어나가기 때문이야
이러한 꽉찬 트리는 배열로 표현하는것이 메모리를 더 절약할수 있어(포인터로 노드를 표현하는 것 보다)

루트 노드를 배열의 1번노드로 하고 노드 i의 왼쪽 자식은 2*i, 오른쪽 자식은 2*i+1로 설정해주자.
이 때 필요한 배열의 길이는 원하는 구간의 크기가 n이라고 할때 이 n이 2의 거듭제곱 꼴이라면 이런 이진트리가 최대한 균형있게
퍼지게 되어서 2*n의 길이로도 표현해 줄 수 있다. 그렇지만 거듭제곱 꼴이 아니라면 중간에 삐져나오는 친구때문에 2*i, 2*i+1로 정의된 이 트리에서
인덱스가 2*n보다 커질 수 있게 되므로 이럴때는 n과 가장 가까운 거듭제곱 꼴(n보다 큰)로 변환 시켜서 그것의 2배로 배열의 크기를 잡아 주어야 한다.

그런게 귀찮다면 4*n으로 하여 (2*n의 2배로 해준것..왜 사이즈가 그 안에 들어가지..?) 표현할 수 도있다.
*/

/*
구간트리의 각 노드에는 현재 자신의 위치를 저장할 필요는 없는데 왜냐면 그 노드가 표현하고 있는 구간을 이용하면 내가 지금 어느 노드에 있는지를
알아낼 수 있기 때문이야
*/

#include <vector>
#include <algorithm>
#include <limits>
using namespace std;

//RMQ문제 해결을 위한 구간트리의 정의
struct RMQ {
	//배열의 길이
	int n;
	//각 구간의 최소치 (rangeMin[i] i번 노드가 표현하는 구간에서 얻을 수 있는 최소값을 저장)
	vector<int> rangeMin;
	//알아내고 싶은 배열을 인자로 받는다.
	RMQ(const vector<int>& array) {
		n = array.size();
		rangeMin.resize(4 * n);
		init(array, 0, n - 1, 1);		//1번을 루트노드로 하여 초기화를 시작한다.
	}

	//node 노드가 array[left,right] 배열을 표현할때 (right포함임을 알자)
	//node를 루트노드로 하는 서브트리를 초기화 하고 이 node가 표현하는 구간의 최소값을 반환한다.
	int init(const vector<int>& array, int left, int right, int node) {
		//leaf노드에 도달 한 경우에는 left=right가 되어서 그 값 자체가 최소값이 된다. base case!
		if (left == right)
			return rangeMin[node] = array[left];
		int mid = (left + right) / 2;
		int leftMin = init(array, left, mid, 2 * node);
		int rightMin = init(array, mid + 1, right, node * 2 + 1);
		return rangeMin[node] = min(leftMin, rightMin);		//양쪽 자식 중에 작은 친구를 반환하면 된다.

		//init함수는 모든 정점을 순회하게 되므로 시간복잡도는 원하는 구간의 길이가 n일때의 노드의 수인 O(2*n) ==> O(n)이 된다.
	}


	/*
	구간트리에서의 질의 연산은 구간트리의 순회를 통해서 구해줄 수 있다.
	query(left,right,node,nodeLeft,nodeRight) = node가 표현하는 범위 [nodeLeft,nodeRight]와 원하는 범위인 [left,right]의 교집합에서 최소값을 반환하는 함수라고 하자.

	이때 루트는 1번이고 이 노드는 [0,n-1]을 표현하므로 [i,j]구간의 최소값은 query(i,j,1,0,n-1)을 호출함으로써 구해줄 수 있다.
	
	이 과정에는 크게 3가지의 경우가 있는데
	교집합이 공집합인 경우는 두 구간은 서로 겹치지 않으므로 반환값이 존재하지 않는다. 이때는 최소값을 구하는데 영향을 주지 못하도록 엄청 큰 수를 반환하도록 하자

	교집합이 [nodeLeft, nodeRight]인 경우는 구하는 구간[left,right]이 노드의 범위에 완전히 포함된 경우이다.
	이 때는 그냥 init에서 구해놓은 node의 최소값을 반환해주면 된다.

	이 외의 모든 경우에서는 두 범위가 서로 겹쳐있는 경우 이므로
	두 자손노드에 대해서 찢어서 값을 구한 후 그 중 더 작은 값을 반환해 주면 된다.
	*/

	const int INF = numeric_limits<int>::max();

	//node가 표현하는 범위 [nodeLeft,nodeRight]가 주어질때
	//이 범위에서 [left,right]범위에서의 교집합에 속하는 친구들 중에 최소값을 반환한다.
	int query(int left, int right, int node, int nodeLeft, int nodeRight) {
		//두 구간이 겹치지 않는경우 (1번 케이스)
		if (right < nodeLeft || left > nodeRight)
			return INF;
		//node의 표현범위가 [left,right]에 완전히 포함되는 경우 그냥 그 node에 미리 계산된 값을 주면 된다.
		if (left <= nodeLeft && right >= nodeRight)
			return rangeMin[node];
		//그렇지 않다면 양 구간으로 나누어서 둘중 최소값을 반환한다.
		int mid = (nodeLeft + nodeRight) / 2;
		return min(query(left, right, node * 2, nodeLeft, mid), query(left, right, node * 2 + 1, mid + 1, nodeRight));
	}

	//query 함수는 모든 경우에 대해서 한 구간이 두개로 쪼개지는 경우는 최대 두번 까지밖에 생기지 않게되어서
	//거의 트리의 높이와 같은 호출이 진행되므로 시간복잡도는 O(logn)이된다.

	//원래 배열의 index위치에 있는 값을 새로운 값으로 갱신하는 경우에 보면
	//이 위치를 구간에 포함하는 친구는 최대 O(logn)개 있을꺼야 (index가 리프 노드에 있다면 그 줄기를 따라서 루트까지 올라가는 모든 노드가 갱신되어야 한다.)

	//array[index] = newValue로 갱신되었을때 node를 루트로 하는
	//구간 트리를 갱신하고 node가 표현하는 구간의 최소값(array[index]=newvalue로 바뀐후의)을 반환한다.
	int update(int index, int newValue, int node, int nodeLeft, int nodeRight) {
		//index가 node가 표현하는 구간에 속하지 않는다면 계산할 필요없이 무시하자
		if (index < nodeLeft || index > nodeRight)
			return;
		//트리의 리프노드까지 내려왔다면 이제 갱신해 줄 수있어
		if (nodeLeft == nodeRight)
			return rangeMin[node] = newValue;		//리프노드의 최소값은 그 값 자체이고 이제 그 값 자체가 바뀌니깐 이 node에서는 rangeMin의 값을 그냥 바꿔버리면 된다.
		int mid = (nodeLeft + nodeRight) / 2;
		//만약에 새로운 값이 최소값에 영향을 주지 않더라도 이 update함수가 최소값을 반환하니깐 원래의 값대로 그대로 있는 값을 줄꺼야
		return rangeMin[node] = min(update(index, newValue, node * 2, nodeLeft, mid), update(index, newValue, node * 2 + 1, mid + 1, nodeRight));		
	}
};

/*
응용문제
1)
만약 구간에서 가장 작은 두개의 값을 찾는 경우를 보자
이렇게 되면 루트의 각 자손들이 각각 2걔씩을 가지고 올테니깐 이제 이 루트는 4개중에 작은 친구 2개를 반환해주면 된다.
그리고 이러한 문제에서는 반환값이 숫자하나로 표현하기 힘드므로 구조체를 따로 정의해서 (내부에 비교함수도 있으면 좋을듯) 반환값으로 해주면 쉽게 구현할 수 있다.

2)
또한 만약 주어진 구간에서 최소값과 최대값을 구하는 문제를 푸는 경우에는
구간에서 최소값을 반환하는 구간트리와 구간에서 최대값을 반환하는 구간트리를 작성하여 구해주어도 되지만

최소값을 구하는 구간트리를 조금 변형하면 쉽게 구할수 있는데
그 방법은 값을 계산하는 array 배열을 하나 가지고 있고 array2 배열을 하나 만드는데 이 값은 array배열에 -(마이너스)를 곱한 값으로 한 후에
array를 이용한 최소값 구간트리와 array2를 이용한 최소값 구간트리를 적용하게 되면
array를 이용하면 원래대로 원하는 최소값을 구할 수 있고 array2를 이용하면 원하는 최대값이 음수형태로 구해지게 된다.!!


3)
이번에는 특정구간에서의 최대출현빈도를 계산하는 경우를 보자
최대 출현빈도란 구간에서 가장 자주 등장하는 수의 등장횟수이다
예를 들면 {1,1,1,2}에서는 3이고 {1,2,3}은 1인것이야

이것또한 왼쪽 범위와 오른쪽 범위의 최대출현빈도를 구해서 둘 중 큰 값을 반환해주고 싶지만
예외가 존재한다.

1) 두 구간에서 최대출현할 숫자가 같은 경우에는 둘중 큰 값이 아니라 둘의 합을 반환해야 한다.
2) 만약 두 구간 각각에서 구한 최대출현빈도보다 두 구간을 합쳐서 봤을때 생긴 최대출현빈도가 큰 경우에는 그 수를 반환해야 한다.
ex) {1,1,1,2,2} {2,2,3,3,3}인 경우 오른쪽과 왼쪽 친구는 3을 반환하지만 이 둘을 합한 {1,1,1,2,2,2,2,3,3,3}은 4를 반환해야 옳은 값이 된다.

따라서 이런 문제를 풀때에는 그냥 단순히 최대 출현빈도를 반환하는 것이 아니라 추가적인 정보도 구조체에 담아서 반환하여
그 곳에서 이러한 예외를 다 판단할 수 있게 해주는 것이 좋다.
결국은 구조체를 잘 활용해야 하는게 포인트 !!

RMQ에서 min함수를 사용한 곳에 merge함수를 사용하면 원하는 값을 구할 수 있다.
*/
//필요한 정보를 모아놓은 구조체
struct RangeResult {
	//이 구간의 크기
	int size;
	//최대빈도수
	int mostFrequent;
	//이 구간의 왼쪽 끝 수와 그 수의 출현횟수
	int leftNumber, leftFreq;
	//오른쪽 끝 수와 출현횟수
	int rightNumber, rightFreq;
};

//왼쪽 구간의 결과 a와 오른쪽 결과 b를 합쳐서 원하는 값을 반환해준다.
RangeResult merge(const RangeResult& a, const RangeResult& b) {
	RangeResult ret;

	//합친 구간의 크기
	ret.size = a.size + b.size;

	//합친 구간의 왼쪽 끝 수는 왼쪽 구간의 왼쪽 끝수 이다
	//그런데 이때 생기는 예외는 왼쪽 구간의 모든 수가 왼쪽 끝수와 같은 경우인데 이때는 leftFreq이 변할 수 있다.
	//{1,1,1,1}, {1,1,2,2} 이때는 합친 구간의 leftFreq가 4가 아니라 4+2 = 6이 된다.!
	ret.leftNumber = a.leftNumber;
	ret.leftFreq = a.leftFreq;
	if (a.size == a.leftFreq && a.leftNumber == b.leftNumber)
		ret.leftFreq += b.leftFreq;
	//오른쪽도 마찬가지
	ret.rightNumber = b.rightNumber;
	ret.rightFreq = b.rightFreq;
	if (b.size == b.rightFreq && a.rightNumber == b.rightNumber)
		ret.rightFreq += a.rightFreq;

	//위 까지는 합쳐진 구간에서 RangeResult에 담아가야할 정보를 수정한 것이고 이제 원하는 답을 계산하자
	//우선 이러한 왼쪽 끝수와 오른쪽 끝 수 중에 더 많이 등장한 친구를 고른다.
	ret.mostFrequent = max(a.mostFrequent, b.mostFrequent);
	
	//근데 위에 말했듯이 합쳐지면 달라지는 친구를 골라내자
	if (a.rightNumber == b.leftNumber)
		ret.mostFrequent = max(ret.mostFrequent, a.rightFreq + b.leftFreq);

	return ret;
}

/*
또 다른 활용예제
LIS(Longest increasing Sequence)를 구하는것
즉 어떤 수열에서 증가하는 부분 수열을 끄낼 때 그 중 가장 긴 수열이다

이것은 O(N^2)으로 다이나믹 프로그래밍으로도 구할 수 있는데

구간트리를 활용한다면 O(logn)에 구할수 있겠죵?

우선 A[i] = x의 값에 대해서 (x,i)인 pair로 만들어 준다. (즉 값과 index정보를 동시에 지닐 수 있게 한다.)
그리고 나서 x 값에 대해서 오름차순 정렬을 한다고 하자
(여기서 모든 x는 서로 다른 수라고 하자)

그러면 작은 x부터 볼수 있고 그 x의 index또한 알 수 있게 되었어

이제 작은 x값부터 순회하면서 A[i] = x인 i에 대해서 구간 [0,i]에 대해 지금까지 존재하는 LIS + 1 이 x로 끝나는 LIS의 길이가 된다.
무슨 말이냐 하면 x는 오름차순으로 정렬되어 있으므로 그 x를 보게 되면 i를 알 수 있고
그러면 [0,i-1]까지의 LIS는 x보다는 작은 연속된 친구 + x 자기 자신이니깐 (x는 서로 다르다고 했으니깐 x와 이전값은 서로 다른값이야)
[0,i]에 대해서는 [0,i-1]의 LIS + 1이 되는거야 x가 크기순으로 정렬되어있으니깐
0~i사이의 모든 index를 체크해보지 않아도 그 친구들은 [0,i]의 LIS에는 영향을 미치지 못함을 알 수 있어


이것을 구현하는 방법은
우선 구간에서 최대값을 구하는 세그먼트 트리를 구현한다, (모든 자리는 0으로 초기화)
그리고 작은 x부터 순회하면서 A[i]=x인 구간[0,i]에서 최대값을 구하고 그 값 + 1을 세그먼트 트리의 인덱스 i인 리프노드의 값으로 update를 시킨다...?

..나중에 계속 ..;; kks 블로그에 올려져 있다.
*/