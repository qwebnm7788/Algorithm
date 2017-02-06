#include <iostream>
#include <vector>
using namespace std;

int main(){
	int n;
	cin >> n;

	vector<long long> arr(n+1);
	for(int i = 1; i <= n; ++i)
		cin >> arr[i];

	vector<long long> ans(n+1);
	bool turn = false;
	for(int i = 1; i <= n-i+1; ++i){
		if(turn){
			ans[i] = arr[i];
			ans[n-i+1] = arr[n-i+1];
			turn = !turn;
		}else{
			ans[i] = arr[n-i+1];
			ans[n-i+1] = arr[i];
			turn = !turn;
		}
	}

	for(int i = 1; i <= n; ++i)
		cout << ans[i] << " ";
}