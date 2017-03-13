#include <cstdio>
int main(){
	long long a,b,c;
	scanf("%lld %lld %lld", &a, &b, &c);
	long long x = a*b*c;
	int arr[10] = {0};
	while(x>0){
		arr[x%10]++;
		x /= 10;
	} 
	for(int i = 0; i < 10; ++i) printf("%d\n", arr[i]);
}