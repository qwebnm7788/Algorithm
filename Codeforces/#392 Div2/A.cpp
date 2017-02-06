/*
#392 (Div2)

758A - Holiday Of Equality

숫자는 줄어들 수 없으므로 max(a1,a2,a3,...,an)까지 모두 증가시켜주어야 한다.

max(a1,a2,...,an)을 찾고 한번의 루프를 통해서 각 원소와 이 값의 차이를 모두 더해주면 된다.

∑(max-ai) (i=0~n-1) 이 된다.

Time Complexcity = O(n)

*/

#include <iostream>
#include <vector>
using namespace std;

int main(){
	int n;
	cin >> n;
	
	int maxVal = 0;
	vector<int> arr(n);
	for(int i = 0; i < n; ++i){
		cin >> arr[i];
		if(arr[i] > maxVal)
			maxVal = arr[i];
	}
	
	int ans = 0;
	for(int i = 0; i < n; ++i)
		ans += (maxVal-arr[i]);
	
	cout << ans;
}

/*
조금 더 멋진 풀이
*/

#include <algorithm>
int main(){
	int n;
	cin >> n;
	
	int maxVal = 0;
	int sum = 0;
	vector<int> arr(n);
	for(int i = 0; i < n; ++i){
		cin >> arr[i];
		sum += arr[i];
		maxVal = max(maxVal,arr[i]);
	}
	
	cout << n*maxVal - sum;			//전체값을 maxVal이라고 생각하고 총 합을 뺴주면 된다. (가우시안 덧셈과 같다)
}