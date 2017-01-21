//그냥 set을 한번 써봤다.
#include <iostream>
#include <set>
using namespace std;
int main(){
	set<int> s;
	int x;
	for(int i = 0; i < 10; ++i){
		cin >> x;
		s.insert(x%42);
	}
	cout << s.size();
}

/*
혹은
bool arr[42];
for(int i = 0; i < 10; ++i){
	scanf("%d", &x);
	arr[x%42] = true;
}
int ans = 0;
for(int i = 0; i < 42; ++i){
	if(arr[i])
		ans++;
}
printf("%d", ans);

도 가능.