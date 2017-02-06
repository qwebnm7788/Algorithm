/*
모든 쌍을 다 살펴보게 되면 O(N^2)이어서 N이 최대 10^5이기 때문에
시간제한안에 돌아올수 없다.

대신 생각해보면 ai와 어떤 수를 xor했을때 x가 나온다는 말은
ai를 이진수로 생각해보면 x와 ai의 y번째 이진수를 보자.
x의 y번자리 수가 1이고 ai의 y번 자리 수가 0이라면 ai와 xor해서 x가 나오려면
그 친구의 y번 자리수는 무조건 1이어야 한다.
ai의 y번자리가 1이었다면 무조건 0이어야 겠죠?

이런식으로 살펴본다면 규칙을 알아낼수있는데
ai가 xor해서 x가 나오는 수는 ai와 x를 xor하면 알아낼 수 있다는 것이다.

이 문제에서 주의해야 할 점은
ai가 같은 수가 여러번 나올수 있다는 점과

만약 ai xor x를 한 값이 다시 ai와 같이 나온다면 (즉 나와 2진수가 정 반대되는 친구여서)
갯수를 세어줄때 for문에서 쭉 훑을때 -1을 해서 나를 센값을 빼주는 과정이 필요하다.

이렇게 세어주면 쌍의 갯수를 구해야 하므로 나누기 2를 해주면 된다.

이러면 한번만 쭉 훑어주면 되므로 O(N)이 된다.!

또한 이 친구들의 크기가 얼마까지 커지는지도 잘 고려해서 check배열의 크기를 만들어 주어야 한다.
x xor y 의 크기는 max(x,y)*2까지 커진다고 한다.
여기서 x,y는 최대 10^5이므로 200000까지는 키워주어야 하겠죠
*/

#include <iostream>
using namespace std;

long long check[150000];
long long arr[100005];
int main() {
	freopen("input.txt", "r", stdin);

	long long n, x;
	cin >> n >> x;

	for (int i = 0; i < n; ++i) {
		cin >> arr[i];
		check[arr[i]]++;
	}

	long long ans = 0;
	for (int i = 0; i < n; ++i) {
		if (check[arr[i] ^ x]) {
			if (arr[i] == (arr[i] ^ x))
				ans += (check[arr[i] ^ x] - 1);
			else
				ans += check[arr[i] ^ x];
		}
	}
	cout << ans/2;

}