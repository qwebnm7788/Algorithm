#include <iostream>
#include <string.h>
#include <algorithm>
using namespace std;

const int INF = 987654321;

//A[] 양자화 해야되는 대상 배열
//pSum[i] = A[0]~A[i]까지의 합
//pSqSum[i] = A[0]^2 ~ A[i]^2의 합
int n, s;
int A[101], pSum[101], pSqSum[101];

//A를 정렬하고 부분합을 계산한다.
void precalc(){
	sort(A, A+n);
	pSum[0] = A[0];
	pSqSum[0] = A[0]*A[0];
	for(int i = 1; i < n; ++i){
		pSum[i] = pSum[i-1] + A[i];
		pSqSum[i] = pSqSum[i-1] + A[i]*A[i];
	}
}

//A[lo]~A[hi] 구간을 하나의 숫자로 표현할때 얻을 수 있는 최소 오차 합을 반환한다.
int minError(int lo, int hi){
	//부분합 이용 A[lo]~A[hi]의 합을 얻는다.
	int sum = pSum[hi] - (lo == 0 ? 0 : pSum[lo-1]);		//0번째 부터면 그냥 pSum[hi]와 같다.
	int sqSum = pSqSum[hi] - (lo == 0 ? 0 : pSqSum[lo-1]);
	//평균을 반올림 한 값으로 모든 수를 양자화한다.
	int m = int(0.5 + (double)sum / (hi-lo+1));
	//sum(A[i]-m)^2 을 펼쳐서 얻으면
	int ret = sqSum - 2*m*sum + m*m*(hi-lo+1);
	return ret;
}

int cache[101][11];			//cache[i][j] = i번부터의 친구들을 j개의 숫자들로 양자화할때 얻을 수 있는 최소의 오차값
int quantize(int from, int parts){
	//base case = 모든 숫자를 양자화했을때
	if(from == n) return 0;
	//base case = 아직 할께 있는데 이용가능한 숫자가 없을때
	if(parts == 0) return INF;
	int& ret = cache[from][parts];
	if(ret != -1) return ret;
	ret = INF;

	//조각의 길이를 변화해가면서 최적의 값을 찾는다.
	for(int partSize = 1; from + partSize <= n; ++partSize)
		ret = min(ret, minError(from, from+partSize-1) + quantize(from + partSize, parts-1));

	return ret;
}

int main(){
	ios_base::sync_with_stdio(false);

	int test;
	cin >> test;
	for(int z = 0; z < test; ++z){
		cin >> n >> s;

		for(int i = 0; i < n; ++i)
			cin >> A[i];

		memset(cache, -1, sizeof(cache));
		precalc();
		cout << quantize(0,s) << endl;
	}
}
