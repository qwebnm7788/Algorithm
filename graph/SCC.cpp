#include <iostream>
#include <vector>
#include <stack>
#include <algorithm>
using namespace std;

const int MAX = 10000;

//SN -> SCC�� ���� sn[i] -> i ������ ���� SCC�� ��ȣ

int V, E, cnt, dfsn[MAX], SN, sn[MAX];
vector<int> adj[MAX];
//SCC�� ����Ǿ������� ���θ� ����.
bool finished[MAX];
stack<int> S;
vector<vector<int>> SCC;

//�ڽ��� ���� ������ �� �� ���� ���� �湮������ ��ȯ�Ѵ�.
int dfs(int curr) {
	//�湮 ���� ����
	dfsn[curr] = ++cnt;
	//���ÿ� ����
	S.push(curr);

	//result�� ��ȯ��
	int result = dfsn[curr];
	//���� ���� ��ȸ
	for (int next : adj[curr]) {
		//���� �湮���� ���� �̿�
		if (dfsn[next] == 0) {
			//next�� �������� next�� ��Ʈ�� �ϴ� ����Ʈ���� dfs ��� ���� result�� ���ؼ� �ּҰ��� ��´�.
			result = min(result, dfs(next));
		}
		else if (!finished[next]) {
			//�湮�� �ߴµ� ���� SCC�� ������� ���� ����
			result = min(result, dfsn[next]);
		}
	}

	//curr�� ���� �ؿ� ģ������ ���� ������ �ְ� ���� ������ ��쿡�� SCC�� �����Ѵ�.
	//�� �ؿ� ����Ʈ���� (�� �߿��� �̹� SCC�� �������� ģ���� ���� �� �־�) �ϳ��� SCC�� �̷��.
	if (result == dfsn[curr]) {
		vector<int> currSCC;

		while (1) {
			int t = S.top();
			S.pop();
			currSCC.push_back(t);
			finished[t] = true;
			sn[t] = SN;
			if (t == curr)
				break;
		}
		SCC.push_back(currSCC);
		SN++;
	}

	return result;
}


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////



#include <iostream>
#include <vector>
#include <stack>
#include <algorithm>
using namespace std;

//�׷����� ��������Ʈ ǥ��
vector<vector<int>> adj;

//�� ������ ������Ʈ ��ȣ (0���� ����)
//���� SCC�� ���ϴ� ������ �� ������Ʈ ��ȣ�� ���� �ϴ�.
vector<int> sccId;

//�� ������ �߰� ����
vector<int> discovered;

//������ ��ȣ�� ��� ����
stack<int> st;

int sccCounter, vertexCounter;

//here�� ��Ʈ�� �ϴ� ����Ʈ������ ������ ����/ ���������� ���ؼ� �� �� �ִ� ���� �� �ּ� �߰߼����� ��ȯ�Ѵ�.
//�̹� SCC�� ������ ģ���� ���� ���������� �����ϴµ� �ֳĸ� �� ģ���� ���ؼ��� ���� �ű�δ� �� �� ������ �ű⼭�� �� ������ �� �� ���� ����(���� �׷����ϱ�)
int scc(int here) {
	int ret = discovered[here] = ++vertexCounter;

	//���ÿ� here�� �ִ´�. here�� �ļյ��� ��� ���ÿ��� here���� �ö󰡰� �Ǵµ�
	//���߿� SCC�� ���� �� here���� �̴� �������� here�� ���� SCC�� �ִ� ���� ������� �� �ִ�.

	for (int i = 0; i < adj[here].size(); ++i) {
		int there = adj[here][i];

		//(here,there)�� tree edge
		if (discovered[there] == -1) {
			ret = min(ret, scc(there));
		}
		else if (sccId[there] == -1) {
			//there�� �����ؾ� �ϴ� cross edge�� �ƴ϶� ���� scc�� Ŀ���� �ȵ� ģ����� üũ �غ��� ��
			//������ �����̶�� there�� here�� �����̶�� �Ҹ��� there�� �߰߼����� ret�� ���ؼ� �ּҰ��� ����ȴ�.
			//������ �����̶�� there�� here�� �ڼ��̶�� �Ҹ��ε� scc�� �̹� �����ٸ� ���� �ٸ� SCC�� ���Ѵٴ� �ǹ̰� �Ǵϱ� �� üũ�� �ʿ䰡 ����.
			//�׷��� scc�� ������ �ʾҴٸ� ������ ������ here���� there�� �ٸ���η� �ѹ� ���ٿԴٴ� ���ε� �� �� ��Ͱ� Ǯ���鼭 ������ �� ����������
			//�׷��� ���� ������ģ���� �� ������ �ʾƵ� ���� ���� �� �ִ� ������ �� ������ ����
			//���������߿� �̹� SCC�� ���� ģ������ �ű⼭ ���� Ʈ���� �Ѿ���� ���ϱ� ������ Ŀ���� �Ѱ��̴ϱ� �� ģ������ üũ�� �ʿ�� ����.
			ret = min(ret, discovered[there]);
		}
	}

	//here���� �θ�� �ö󰡴� ������ ������ ���θ� üũ�Ѵ�.
	if (ret == discovered[here]) {
		//here�� ��Ʈ���ϴ� ����Ʈ������ �ö� �� �ִ� �ִ� ���̰� �ᱹ�� here�����ۿ� ���� ���Ѵٸ�
		//here���� here�� �θ�� �ö󰡴� ������ Ŀ���ؼ� here���� ģ������ �ϳ��� SCC �� ������ �� �� �ִ�.
		
		//�׷��� here�� ��Ʈ�� �ϴ� ����Ʈ������ ���ÿ� �����ִ� ģ������ ��� �ϳ��� ������Ʈ�� ���´� (�� ���ο� �� �ٸ� SCC�� ���� �� �ְ� �װ� �̹� ���ÿ��� ����������)
		while (true) {
			int t = st.top();
			st.pop();
			sccId[t] = sccCounter;
			if (t == here)
				break;
		}

		++sccCounter;
	}
	return ret;

}


//Ÿ�� �˰���
vector<int> tarjanSCC() {
	//�迭 ��� �ʱ�ȭ
	sccId = discovered = vector<int>(adj.size(), -1);

	//ī�����ʱ�ȭ
	sccCounter = vertexCounter = 0;

	//��� ������ ���ؼ� scc ȣ�� -> �ֳĸ� ���� �׷����� �ƴ� �� �ֱ� ��������
	for (int i = 0; i < adj.size(); ++i) {
		if (discovered[i] == -1)
			scc(i);
	}
	return sccId;
}


