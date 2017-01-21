/*
1725
히스토그램
부분배열찾기 문제랑 똑같당

이 문제가 판단해야 되는 부분이 좀 더 간단하다

스택을 이용하면 O(N)에 풀수 있다고 한다.
*/

#include <stdio.h>
#include <vector>
#include <algorithm>
using namespace std;

//[a,b]사이의 직사각형으로 만들 수 있는 최대의 넓이
long long solve(vector<long long>& arr, int a, int b){
	if(a==b)
		return arr[a];
	
	int mid = (a+b)/2;
	long long ret = max(solve(arr,a,mid),solve(arr,mid+1,b));
	
	int left,right;
	long long height = arr[mid];
	left = right = mid;
	ret = max(ret, height);
	
	while(left > a || right < b){
		if(left > a && right < b){
			if(arr[left-1] > arr[right+1]){
				height = min(height,arr[left-1]);
				left--;
			}
			else{
				height = min(height,arr[right+1]);
				right++;
			}
		}else if(left > a){
			height = min(height,arr[left-1]);
			left--;
		}else{
			height = min(height,arr[right+1]);
			right++;
		}
		
		ret = max(ret, (right-left+1)*height);
	}
	
	return ret;
}
int main(){
	int n;
	scanf("%d", &n);
	
	vector<long long> arr(n);
	for(int i = 0; i < n; ++i){
		scanf("%lld", &arr[i]);
	}
	
	printf("%lld", solve(arr,0,n-1));
}