/*
1893 시저암호

주어진 알파벳을 가능한 모든 방법으로 시프트 해보면서
원문을 시프트해서 얻을 수 있는 암호화한 문자열이 암호문에 등장할 수 있는 방법을 출력하는 것과같다.

알파벳의 최대길이가 62까지이므로 시프트의 방법또한 62가지가 될것이다.
매번 시프트할때마다 kmp를 이용해서 암호문에서 등장하는 가짓수를 체크해줘야 하므로 kmp알고리즘은 (|W|+|S|)이므로
O(62*(500000+50000))이 된다. ->약 10^7~8 정도이므로 brute-force로도 충분히 가능하다. (알파벳의 종류가 한정되어 있기 때문에)

여기서 문제에서 알려준 힌트는 암호문에서 원문이 단 한번만 나타난다고 했기 때문에
맨 처음 input에서 ABC를 0번 시프트했을때 암호문에서 ABC가 두번 보이기 때문에 no sol이된다.

구현상에서는 map을 이용했는데 왜냐면 주어진 알파벳이 A~Z순서가 아니기 때문에
각각의 글자마다 순서에 맞게 index를 부여해 주어서 시프트할때 사용해 주어야 한다.
*/
#include <iostream>
#include <vector>
#include <map>
#include <string>
using namespace std;

int main() {
	freopen("input.txt", "r", stdin);
	ios_base::sync_with_stdio(false);

	int test;
	cin >> test;
	for (int z = 0; z < test; ++z) {
		string a, w, s;
		cin >> a >> w >> s;

		int aSize = a.length(), wSize = w.length();

		map<char, int> m;
		for (int i = 0; i < aSize; ++i)
			m.insert(make_pair(a[i], i));
		
		vector<int> ans;
		for (int i = 0; i < aSize; ++i) {
			string temp = w;
			for (int j = 0; j < wSize; ++j) {
				temp[j] = a[(m[w[j]] + i) % aSize];
			}

			//search temp from s
			vector<int> pi(wSize, 0);
			for (int j = 1, matched = 0; j < wSize; ++j) {
				if (matched > 0 && temp[j] != temp[matched]) matched = pi[matched - 1];
				if (temp[j] == temp[matched]) pi[j] = ++matched;
			}
			
			//kmp
			int cnt = 0;
			for (int j = 0, matched = 0; j < s.length(); ++j) {
				if (matched > 0 && s[j] != temp[matched]) matched = pi[matched - 1];
				if (s[j] == temp[matched]) {
					matched++;
					if (matched == wSize) {
						cnt++;
						matched = pi[matched - 1];
					}
				}
			}
			if (cnt == 1)
				ans.push_back(i);
		}
		if (ans.size() == 0)
			cout << "no solution\n";
		else if (ans.size() == 1)
			cout << "unique: " << ans[0] << endl;
		else {
			cout << "ambiguous: ";
			for (int i = 0; i < ans.size(); ++i)
				cout << ans[i] << " ";
			cout << endl;
		}
	}

}