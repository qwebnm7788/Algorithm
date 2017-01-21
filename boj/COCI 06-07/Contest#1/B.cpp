//택시 기하학은 맨해튼 거리를 이용한 것인데
//그림을 그려보면 알겠지만 마름모 모양이 나온다.
//x좌표 + y좌표가 r인것이므로 기울기가 일정한 1,2,3,4사분면의 직선을 그리면 된다.
//#define _USE_MATH_DEFINES		//요걸 써줘야 math.h내의 상수를 사용할수 있다.
#include <stdio.h>
#include <cmath>
using namespace std;

#define M_PI 3.14159265358979323846
int main(){
	double r;
	scanf("%lf", &r);		//double 입력시에는 포인터로 변경하게 되므로 %lf를 써야 한대
	printf("%.6f\n%.6f",2*M_PI*r,2*r*r);
}