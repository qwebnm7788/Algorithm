/*
749B - Parallelogram is Back (약간의 기하)
Parallelogram 은 평행사변형이다.

우선 주어진 세개의 점이 A,B,C라고 하고 찾아야 하는 점을 D라고 해보자
여기서 AD가 대각선이 된다고 해보면
벡터로 생각하면 그림으로 볼수 있듯이 AD = AB+BD = AC+CD가 된다.
이 때 평행사변형의 성질을 이용하면 BD=AC, AB=CD임을 이용할 수 있고
따라서 D의 점은 (Ax + (Cx-Ax) + (Bx-Ax), Ay + (Cy-Ay) + (By-Ay))가 된다.
이를 간단하게 하면 D = (Bx+Cx-Ax,By+Cy-Ay)가 된다.

이때 주어진 세개의 점에 대해서 한번씩 다 해봐야 되니깐
A의 자리에 B를, C를 넣어봄으로써 구해줄 수 있다.
이렇게 찾아낸 점들이 모두 distinct함을 증명해보자. -> 즉 이렇게 구한 3개의 점이 정답!(무조건 3개)

우선 이렇게 찾아낸 점중에 중복되는 점이있다고 가정해보자.
AD와 BD를 이용해서 얻은 D점이 중복된다고 가정하자

위에서 찾아낸 공식을 이용하면 D점이 같아야 하므로 다음의 두 방정식이 성립한다.
Bx+Cx-Ax = Ax+Cx-Bx
By+Cy-Ay = Ay+Cy-By 이고 이를 정리하면

Bx = Ax
By = Ay 가 된다.!!

따라서 입력된 점 자체가 중복된다는 말이되는데 이것은 문제의 가정(input으로 들어오는 점은 모두 다르다.)에
모순된다 다른 점에 대해서도 다음이 성립하므로...ㅜㅜ
이렇게해서 얻은 모든 정점은 distnict 하다.
*/
#include <iostream>
using namespace std;

int main(){
	int x[3];
	int y[3];
	//input
	for(int i = 0; i < 3; ++i)
		scanf("%d %d", &x[i],&y[i]);

	printf("3\n");		//무조건 세개!
	
	//(i번 점이 A의 위치에 있다고 하면 Dx = i제외 2개의점의 합 - 2*i점의 좌표)
	//이걸 엄청 예쁘게 표현해주면 다음과 같다.
	for(int i = 0; i < 3; ++i){
		int Dx = x[0]+x[1]+x[2]-2*x[i];
		int Dy = y[0]+y[1]+y[2]-2*y[i];
		printf("%d %d\n", Dx, Dy);
	}

}