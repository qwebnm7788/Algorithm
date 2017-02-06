//마지막 자리만을 묻고 있으므로
//이 친구가 계속해서 8과 곱해지고 이러한 수는 8,4,2,6의 주기를 이룬다.
//n==0인 케이스를 따로 처리해 주어야한다.
#include <iostream>
using namespace std;

int main() {
	int n;
	int arr[4] = { 8,4,2,6 };
	cin >> n;
	if (n == 0)
		cout << 1;
	else
		cout << arr[(n-1) % 4];
}