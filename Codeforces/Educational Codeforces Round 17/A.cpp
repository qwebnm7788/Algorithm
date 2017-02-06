#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main(){
	long long n,k;
	cin >> n >> k;

	vector<long long> arr;

	for(long long i = 1; i*i <= n; ++i){
		if(n%i==0){
			if(n/i == i)
				arr.push_back(i);
			else{
				arr.push_back(n/i);
				arr.push_back(i);
			}
		}
	}

	sort(arr.begin(), arr.end());
	if(arr.size() < k)
		cout << "-1";
	else
		cout << arr[k-1];
}