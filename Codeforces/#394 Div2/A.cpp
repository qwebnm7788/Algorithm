/*
어느 구간을 잡더라도 짝수칸과 홀수칸의 갯수 차이는 0 또는 1밖에 나지 않는다.

주의할 점은 a=0,b=0이 들어오면 NO가 된다는 예외 !! (어느 구간을 잡더라도 최소한 하나는 1이상이 나와야 한다. 한칸만 잡아도 1 0 또는 0 1 이니깐)

시간복잡도는 O(1)
*/
#include <iostream>
#include <cmath>
using namespace std;

int main() {
	int a, b;
	cin >> a >> b;
	if (a == 0 && b == 0)
		cout << "NO";
	else if (abs(a - b) > 1)
		cout << "NO";
	else
		cout << "YES";
}