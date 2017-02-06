#include <iostream>
#include <string>
#include <algorithm>
using namespace std;

const int INF = 987654321;
string N;

//N[a,b] 구간의 난이도를 반환한다.
int classify(int a, int b){
	//string에서 [a,b]를 parsing해준다.
	string M = N.substr(a,b-a+1);

	//난이도 1 = 한글자가 모두 차지하는 경우
	if( M == string(M.size(),M[0])) return 1;		//M이 한글자로 통일

	//등차수열 체크 (오름,내림차순)
	bool progressive = true;
	for(int i = 0; i < M.size()-1; ++i)
		if(M[i+1] - M[i] != M[1] - M[0])	//모든 구간에 대해서 등차가 다르면 FAIL
			progressive = false;

	//공차가 1(오름차순) 또는 -1(내림차순)이라면 난이도 2
	if(progressive && abs(M[1]-M[0]) == 1) return 2;

	//번갈아 가면서 진행된다면 간다.
	bool alternating = true;
	for(int i = 0; i < M.size(); ++i)
		if(M[i] != M[i%2])			//2칸씩 체크해보면된다. i%2 == 0인 경우 i%2 == 1인 친구로 통일
			alternating = false;
	if(alternating) return 4;		//번갈아간다면 난이도 4
	if(progressive) return 5;		//공차 1이 아닌 등차수열이라면 난이도 5
	//그 외 난이도 10
	return 10;
}

int cache[10002];

//N[begin:]을 외우는 방법 중 최소의 난이도 합을 반환한다.
int memorize(int begin){
	//base case = 수열의 끝에 도달
	if(begin == N.size()) return 0;
	//memoization
	int& ret = cache[begin];
	if(ret != -1) return ret;

	//begin 포함 3~5개를 잡아보면 된다.
	ret = INF;
	for(int L = 3; L <= 5; ++L)
		if(begin + L <= N.size())		//3,4,5칸을 잡을떄 수열 안넘어가게 끔.
			ret = min(ret, memorize(begin+L) + classify(begin,begin+L-1));
	return ret;
}
int main(){
	ios_base::sync_with_stdio(false);

	int test;
	cin >> test;
	for(int z = 0; z < test; ++z){
		cin >> N;
		fill(cache, cache+10002, -1);
		cout << memorize(0) << endl;
	}
}