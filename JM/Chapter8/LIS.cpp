/*
Longest Increasing Subsequence (LIS) 
최장 증가 부분수열

주어진 배열에서 만들 수 있는 증가하는 형태의 부분수열들 중에 가장 긴 증가부분수열의 길이를 구하는 알고리즘

arr[n] 배열이 주어졌다고 생각해보자.
다이나믹 프로그래밍을 적용할 수 있다면 optimal substructure를 만족해야한다.
즉 한 문제를 subproblem 으로 쪼깨주었을떄 각각의 subproblem 에서 최적의 해를 구하면
그것을 합치면 원래의 문제의 최적해를 구할 수 있는지를 보자.

L[i] = i번 인덱스에서 끝나는 LIS의 길이라고 하자. (즉 구한 LIS가 arr[i]를 마지막으로 하는 수열이다)

그렇다면 L[i] 는 다음과 같이 재귀적으로 구성할 수 있다.
L[i] = 1 + max(L[j]) where 0 < j < i and arr[j] < arr[i]
L[i] = 1 if no such j exists.

즉 L[i]는 i번 앞쪽에 있는 친구들과 arr[i]를 비교해서 i까지 LIS를 끌어올 수 있다면
L[j] + 1이 되는것이다. (이 때 L[j]는 최대한 긴것이 좋다.)
만약 그런 친구가 없다면 각 원소로 끝나는 친구는 자기 자신 1개뿐이므로 길이는 1


이렇게 정의 했을때 주어진 arr에서 가장 긴 LIS를 찾기 위해서는
max(L[i]) where 0 < i < n 을 찾아주면 된다. (LIS 의 끝을 차지하는 친구가 누구인지 잘 모른다.)

이렇게 L[i]를 풀때 L[j]를 사용하므로 optimal substructure 속성을 만족한다.
*/



#include <iostream>
using namespace std;

int arr[501], cache[501];
int n;

//arr[start]에서 시작하는 LIS의 길이를 반환한다.
int lis(int start){
	int& ret = cache[start];
	if(ret != -1) return ret;

	//start 자체도 길이가 1이니깐 ret = 1부터 시작
	ret = 1;
	for(int i = start+1; i < n; ++i){
		//나보다 큰 친구가 있으면 그 친구의 lis와 나를 합친게 구하는 값이다.
		if(arr[i] > arr[start])
			ret = max(ret, lis(i)+1);
	}
	return ret;
}

int main(){
	ios_base::sync_with_stdio(false);

	int test;
	cin >> test;

	for(int z = 0; z < test; ++z){
		cin >> n;

		for(int i = 0; i < n; ++i){
			cin >> arr[i];
			cache[i] = -1;
		}

		int ans = 0;
		for(int i = 0; i < n; ++i)
			ans = max(ans, lis(i));

		cout << ans << endl;
	}
}


//이분탐색을 이용한 NlogN 버전.
#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;

int main() {
	freopen("input.txt", "r", stdin);
	ios_base::sync_with_stdio(false);
	int test;
	cin >> test;

	for (int z = 0; z < test; ++z) {
		int n;
		cin >> n;

		vector<int> c;
		int x;
		for (int i = 0; i < n; ++i) {
			cin >> x;
			//지금 보는 값이 c[ans]의 값보다 크다면 그냥 넣어줘도 된다.
			if (c.empty() || c.back() < x)
				c.push_back(x);
			else {
				//그렇지 않다면 이 친구가 들어갈 수 있는 가장 빠른 부분에 들어간다.
				//그러면 그 친구를 arr[i]로 바꾸자. 이러면 좀 더 최대한 길게 만들 수 있는 조건이 된다. (앞 친구가 더 작아짐으로써 앞으로 추가 될 친구가 조금 더 작아도 된다.)
				vector<int>::iterator it = lower_bound(c.begin(), c.end(), x);
				*it = x;
			}
		}
		cout << c.size() << endl;
	}
}