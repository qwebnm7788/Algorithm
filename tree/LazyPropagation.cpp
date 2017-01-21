/*
Lazy Propagation

세그먼트 트리에 적용되는 내용이다.

기존의 세그먼트 트리에는 update와 원하는 구간의 특정성질을 갖는 값을 구하는 query연산이 있었다.

그런데 특정한 구간[a,b]에 대해서 동시에 값 x를 더한다고 생각해보자 (더한다는 연산은 그때그때의 트리의 구현에 따라 다를 수 있다.)
만약 원래 하던데로 구현해준다면 a~b의 모든 index에 대해서 update를 시켜줌으로써 구현해낼 수 있다.
원하는 구간의 길이를 k(=b-a+1)이라고 하면 매 쿼리에서는 O(logN) (N은 전체구간의 수)에 처리되므로
O(klogN)에 구현해 줄수 있고 k는 최대 n까지 커지므로 시간복잡도는 O(nlogn)이 된다.

그런데 이를 O(logN)에 구현하는 방법이 있는데 이는 lazy propagation을 이용하는 방법이다.!

연산은 원래대로 세그먼트 트리에서 구현하듯이 해주면 되는데 여기서 추가로 구현해주어야 하는 것은
세그먼트 트리의 각 노드마다 lazy라는 배열을 따로 만들어 주는것이다.

lazy배열은 이 노드가 표현하는 영역에 대해서 얼마만큼 더할 계획이 있음을 알려주는 배열이 된다. 
->그렇지만 실제로 아직 더하지는 않은상태

만약 lazy값이 있는 범위 내의 값이 필요한 쿼리가 들어온다면 그 lazy값을 더해진 상태로 값을 반환해 주어야 한다.
이때 특정 노드의 lazy값이 존재하는 노드까지도 내려온다면 이제 이 친구를 계산해주고 자신의 자식들에게 lazy를 넘겨주는데
이 넘겨주는 것을 lazy propagation 이라고 한다.

이런식으로 계속 미루다 보면 리프노드까지 내려오게 되는데 이때는 더이상 미룰 친구가 없으니깐
어쩔수 없이 자신의 값에 lazy값을 흡수시켜주면 된다.

*/

/*
원하는 범위가 모두 들어가는 노드에 도달했을때 만약 lazy가 있다면 lazy를 propagation해주고 그 값을 더한 상태로 반환을 해주면 되는데
더할때는 자신이 포함하는 모든 범위들이 lazy값을 더했어야 하는거니깐 (자신이 포함하는 구간의 길이 * lazy값)을 더해주어야 한다.

리프노드로 들어왔다면 그냥 자신의 값에 더해주는게 좋지

그런데 주의해야 할 점이 있다 propagation을 리프노드로 넘겨주었다면 위에서 말했듯이 구현을 리프노드로 가면 그냥 자신의 값에 더하는 형태로 하였다면 (lazy를 두는게 아니고)
위의 친구들은 값을 갱신해주어야 한다. (왜냐면 자신이 표현하는 구간내의 값들이 변했기 때문에 -> 즉 그 리프노드를 포함하는 구간의 값은 모두 갱신되어야 해 -> 기존의 세그먼트 트리처럼)
따라서 자식들로 propagation을 시켜준 다음에도 자신의 값을 갱신해주는 과정이 추가적으로 필요하다 ! (리프에 도달하는 케이스가 있기 때문)
*/

//구간합을 표현하는 세그먼트 트리의 lazy propagation 형태의 구현 
#include <algorithm>
#include <vector>
using namespace std;

vector<long long> arr;
vector<long long> lazy;
vector<long long> ans;

long long init(int nodeLeft, int nodeRight, int node) {
	if (nodeLeft == nodeRight)
		return ans[node] = arr[nodeLeft];
	int mid = (nodeLeft+nodeRight) / 2;
	return ans[node] = init(nodeLeft, mid, node * 2) + init(mid + 1, nodeRight, node * 2 + 1);
}

//[nodeLeft,nodeRight] 구간을 표현하는 node의 lazy값을 자식에게 propagate한다.
void propagate(int node, int nodeLeft, int nodeRight) {
	//lazy값이 존재한다면
	if (lazy[node] != 0) {

		//리프노드가 아니면 자식한테 미루자
		if (nodeLeft != nodeRight) {
			lazy[node * 2] += lazy[node];
			lazy[node * 2 + 1] += lazy[node];
		}

		//자신의 값은 범위에 해당하는 만큼 더해주면 된다.
		ans[node] += lazy[node] * (nodeRight - nodeLeft + 1);
		lazy[node] = 0;
	}
}

//[left,right]의 범위에 value만큼의 값을 update시킨다.
void update(int left, int right, int value, int node, int nodeLeft, int nodeRight) {
	//우선 propagate 시킨다. (없는친구라면 그냥 종료되겠지)
	propagate(node,nodeLeft,nodeRight);
	//범위에 포함되지 않으면 종료
	if (right < nodeLeft || left > nodeRight)
		return;
	//이 노드의 표현범위가 구간에 완전히 포함되면 lazy를 이 노드에 부여한 후에
	//propagte해서 나는 계산하고 반환하면 되고
	//lazy는 내 자식들에게 가도록 한다.
	//그리고서 종료
	if (left <= nodeLeft && nodeRight <= right) {
		lazy[node] += value;
		propagate(node, nodeLeft, nodeRight);
		return;
	}

	//범위가 아직 더 크다면 반으로 쪼개본다.
	int mid = (nodeLeft + nodeRight) / 2;
	update(left, right, value, node * 2, nodeLeft, mid);
	update(left, right, value, node * 2 + 1, mid + 1, nodeRight);

	//update한 후에 나의 값또한 변화시켜주어야 한다.
	//왜냐면 그 친구들이 leaf에 도달했을 수 있기 때문이다.?
	//그냥 대입 = 임에 유의 ! 
	ans[node] = ans[node * 2] + ans[node * 2 + 1];
}

//[left,right]의 구간합을 반환한다.
long long query(int left, int right, int node, int nodeLeft, int nodeRight) {
	//주어진 구간이 lazy가 존재하는 친구를 포함할 수 있으므로
	//원하는 구간에 내려가면서 propagation을 먼저 시켜준 후에 값을 구한다.
	propagate(node, nodeLeft, nodeRight);

	if (right < nodeLeft || left > nodeRight)
		return 0;
	if (left <= nodeLeft && nodeRight <= right)
		return ans[node];
	int mid = (nodeLeft + nodeRight) / 2;
	return query(left, right, node * 2, nodeLeft, mid) + query(left, right, node * 2 + 1, mid + 1, nodeRight);
}


//이렇게 구현을 하게 되면 매 구간에 대한 쿼리를 O(klogN)이 아닌 O(logN)으로 처리 할 수 있다.