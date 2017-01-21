//그냥 대입했다.
#include <iostream>
using namespace std;

char arr[5][75];

void peter(int col, char word) {
	if (arr[2][col] != '*')
		arr[2][col] = '#';
	arr[0][col + 2] = arr[1][col + 1] = arr[1][col + 3] = arr[2][col + 4] = arr[3][col + 1] = arr[3][col + 3] = arr[4][col + 2] = '#';
	arr[2][col + 2] = word;
}

void wendy(int col, char word) {
	arr[2][col] = arr[0][col + 2] = arr[1][col + 1] = arr[1][col + 3] = arr[2][col + 4] = arr[3][col + 1] = arr[3][col + 3] = arr[4][col + 2] = '*';
	arr[2][col + 2] = word;
}

int main() {
	char in[15];
	scanf("%s", in);

	int size = 5 + (strlen(in) - 1) * 4;

	//초기화
	for (int i = 0; i < 5; ++i) {
		for (int j = 0; j < size; ++j)
			arr[i][j] = '.';
	}

	//첫번째 글자를 제외하고는 한줄씩이 겹친다.
	for (int i = 1; i <= strlen(in); ++i) {
		if (i == 1)
			peter(5 * (i - 1), in[i - 1]);
		else {
			if (i % 3 == 0)
				wendy(4 * (i - 1), in[i - 1]);
			else
				peter(4 * (i - 1), in[i - 1]);
		}
	}

	for (int i = 0; i < 5; ++i) {
		for (int j = 0; j < size; ++j)
			printf("%c", arr[i][j]);
		printf("\n");
	}

}