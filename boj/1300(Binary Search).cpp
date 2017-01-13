// x-1 이하의 수가 k개 미만 이고 x 이하의 수가 k개 이상이라면
// x라는 수가 k번째의 수가 된다.
#include <stdio.h>
#include <algorithm>
using namespace std;

int main(){
	long long n,k;
	scanf("%lld %lld",&n, &k);

	long long low = 1LL, high = 1000000001LL;

	while(low + 1 < high){
		long long mid = (low+high)/2;

		//n의 제한이 10^5이어서 arr[n][n] 은 10^10이라서 int 범위를 넘어간다.
		//또한 k가 1인경우에는 1이 정답이 되는데 이때는 low가 1을 가지고 있기 때문에 절대로 1을 얻을 수 없으므로
		//따로 예외 처리를 해주어야 한다.
		long long cnt = 0;
		for(long long i = 1; i <= n; ++i){
			//여기서 이렇게 해준이유는 (O(N^2)으로 이중 for문을 이용하지않고)
			 //우선 모든 배열에 대해서 i번 행에는 i의 배수만이 나오게 되는데 
			//그러면 mid 이하의 수는 i=1~n에 대해서 min(n,mid/i)개를 수용할 수 있을꺼야 
			//왜냐면 mid/i가 n보다 작으면 (한줄에는 n개가 끝이니깐) 그 만큼만 가주면 그 줄까지 끝내지는거고 
			//아니라면 n개로 컷 해주고 다음줄로 넘어가야지 
			cnt += min(n,mid/i);		
		}

		if(cnt < k)
			low = mid;
		else
			high = mid;
	}
	if(k==1)
		printf("1");
	else
		printf("%lld", high);
}