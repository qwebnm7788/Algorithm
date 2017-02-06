/*
749A - Bachgold Problem
최대한 많은 소수로 합을 구해주려면 가장 작은 소수로의 덧셈을 해주면 되는데
가장 작은 소수는 2이다.
N이 짝수라면 그냥 2의 합으로써 표현이 가능하고 그 횟수는 N/2와 같다.
N이 홀수라면 계속 2로 더해가다보면 마지막으로 남아지는 친구가 3이될꺼야 짝수에서 1이 더 많아진거니깐

따라서 2씩 줄여나가면서 값을 출력해주면 간단하게 구현할 수 있다.
*/
#include <iostream>
#include <vector>
using namespace std;

int main(){
	int n;
	cin >> n;

	vector<int> ans;
	while(n>3){
		ans.push_back(2);
		n-=2;
	}
	ans.push_back(n);
	cout << ans.size() << endl;
	for(int i = 0; i < ans.size(); ++i)
		cout << ans[i] << " ";
}

/*
가운데의 while문을 다른 방식으로 짜보면
for(int i = 1; i < n/2; ++i)
	ans.push_back(2);

if(n%2==0)		짝수 일때
	ans.push_back(2);
else			홀수 일때
	ans.push_back(3);
이 된다.
*/