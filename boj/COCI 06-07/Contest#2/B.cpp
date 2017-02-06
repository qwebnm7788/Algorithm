#include <iostream>
#include <algorithm>
using namespace std;

int main(){
	int arr[3];
	for(int i = 0; i < 3; ++i)
		cin >> arr[i];
	if(arr[2] < arr[0])
		swap(arr[2],arr[0]);
	if(arr[2] < arr[1])
		swap(arr[2],arr[1]);
	if(arr[1] < arr[0])
		swap(arr[0],arr[1]);
	char str[3];
	cin >> str;
	for(int i = 0; i < 3; ++i)
		printf("%d ", arr[str[i]-'A']);
}
