/*
1780
종이의 개수

종이를 9등분 해가면서 분할정복으로 풀어주면된다.
매 크기 n인 종이를 체크해가면서 진행해주면 된다.
이때 n^2의 시간이 걸리고
분할해서 진행하면 nlogn이 걸리게 된다.;..?
*/
#include <stdio.h>
#include <vector>
#include <algorithm>
using namespace std;

bool check(vector<vector<int>>& arr, vector<int>& ans, int row, int col, int n){
	int holder = arr[row][col];
	if(n==1){
		ans[holder+1]++;
		return true;
	}
	for(int i = row; i < row+n; ++i){
		for(int j = col; j < col+n; ++j){
			if(arr[i][j] != holder)
				return false;
		}
	}
	ans[holder+1]++;
	return true;
}

void solve(vector<vector<int>>& arr, vector<int>& ans, int row, int col, int n){
	if(check(arr,ans,row,col,n))
		return;
	for(int i = 0; i < 3; ++i){
		for(int j = 0; j < 3; ++j)
			solve(arr,ans,row+(n/3)*i,col+(n/3)*j,n/3);
	}
}
	
int main(){
	int n;
	scanf("%d", &n);
	
	vector<vector<int>> arr(n);
	vector<int> ans(3);
	
	for(int i = 0; i < n; ++i)
		arr[i] = vector<int>(n);

	for(int i = 0; i < n; ++i){
		for(int j = 0; j < n; ++j)
			scanf("%d",&arr[i][j]);
	}	
	
	solve(arr,ans,0,0,n);

	for(int i = 0; i < 3; ++i)
		printf("%d\n", ans[i]);
	
}
