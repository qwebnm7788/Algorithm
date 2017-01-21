/*
2104 부분배열 고르기

분할정복

처음에 간단히 생각하면 i=0~n-1을 하나 잡고 매 루프마다 j = i+1~n-1을 돌면서 하나씩 다 만들어 보는 방법을 생각해 볼수 있따.
그런데 이 방법은 prefixSum을 이용해도 O(n^2)이어서 시간초과가 나온다. ㅜ;;

매 문제를 절반으로 나누어서 생각해보면
정답은 max(왼쪽 절반의 최대점수, 오른쪽 절반의 최대점수, 가운데를 지나는 구간의 최대점수)가 된다.

그런데 여기서 가운데 구간을 지나는 점수를 처리해줄때 위의 방식대로 하게되면 시간초과가 나온다. ;;
그래서 좀 더 greedy한 방법을 택해보면 mid를 중심으로 양 옆의 값들을 보고 더 큰 쪽으로 이동하는 방식을 택하면 된다.
왜냐면 곱해지는 수에 영향을 최소값이 주게 되는데 둘 중에 더 큰 친구로 가야지 최소값이 변화하더라도 전체 점수가 떨어지는 폭이 최소화 되기 때문이야

이렇게 검사를 다 해주고 나서 최대점수를 반환하면 된다.!
*/
#include <stdio.h>
#include <vector>
#include <algorithm>
using namespace std;

//[a,b]사이의 배열에서 얻을 수 있는 최대점수를 반환한다.
long long solve(vector<int>& arr, vector<long long>& pSum, int a, int b){
	if(a==b)
		return arr[a]*arr[a];			//여기서 원소가 1개 남았다고 arr[a]가 아니라 minVal역시 arr[a]가 되므로 둘의 곱을 반환한다.!
	
	int mid = (a+b)/2;
	long long ret = max(solve(arr,pSum,a,mid),solve(arr,pSum,mid+1,b));
	
	int left,right,minVal;
	left = right = mid;
	minVal = arr[mid];
	ret = max(ret, 1LL*arr[mid]*minVal);			//여기서도 빼먹으면 안되는게 (요거 없으니깐 WA를 받았다) mid 자기자신만을 원소로 할때를 고려해주어야 된다. 밑에서는 늘리기만 하니깐 1개 원소일때를 고려하지 못한다. (역시 마찬가지로 arr[mid]의 제곱으로 비교해야된다.)
	long long comp;
	while(left > a || right < b){
		if(left > a && right < b){		//양쪽으로 늘릴수 있다면 더 큰수가 있는 쪽으로 늘린다.
			if(arr[left-1]<arr[right+1]){
				right++;
				minVal = min(minVal,arr[right]);
			}
			else{
				left--;
				minVal = min(minVal, arr[left]);
			}
		}else if(left > a){			//오른쪽은 끝까지 갔고 왼쪽이 남았다면 왼쪽으로 간다.
			left--;
			minVal = min(minVal,arr[left]);
		}else{
			right++;
			minVal = min(minVal,arr[right]);
		}

		if(left != 0)			//left = 0이면 prefixSum을 쓸때 약간의 예외가 생긴다.
			comp = (pSum[right]-pSum[left-1])*minVal;	
		else
			comp = pSum[right]*minVal;

		ret = max(ret,comp);
	}
	return ret;
}

int main(){
	int n;
	scanf("%d", &n);
	
	vector<int> arr(n);
	vector<long long> pSum(n);
	for(int i = 0; i < n; ++i){
		scanf("%d", &arr[i]);
		if(i!=0)
			pSum[i] = pSum[i-1]+arr[i];
		else
			pSum[i] = arr[i];
	}
	printf("%lld", solve(arr,pSum,0,n-1));
	
}