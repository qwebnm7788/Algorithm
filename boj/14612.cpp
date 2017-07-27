#include <iostream>
#include <vector>
#include <algorithm>
#include <string>

using namespace std;


int main(){
	ios_base::sync_with_stdio(false);
	int n,m;
	cin >> n >> m;

	vector<pair<int,int>> table;

	string inst;
	int s,t;
	for(int i = 0; i < n; ++i){
		cin >> inst;
		if(inst == "order"){
			cin >> s >> t;
			table.push_back({t,s});
		}else if(inst == "sort"){
			sort(table.begin(),table.end());
		}else{
			cin >> s;
			int found;
			for(int j = 0; j < table.size(); ++j){
				if(table[j].second == s){
					found = j;
					break;
				}
			}
			table.erase(table.begin() + found);
		}
		if(table.empty()){
			cout << "sleep\n";
		}else{
			for(int j = 0; j < table.size(); ++j){
				cout << table[j].second << " ";
			}
			cout << endl;
		}
	}
}

