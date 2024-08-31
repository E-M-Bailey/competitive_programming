#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

vector<int> adj[200000];

int cost[200000];

int dfs0(int v, int p){
	if(v != 0 && adj[v].size() == 1){
		cost[v] = 0;
		return 1;
	}
	int ch = 0;
	for(int c : adj[v]){
		if(c == p) continue;
		int res = dfs0(c, v);
		//cout << c << " " << cost[c] << " " << res << endl;
		cost[v] += cost[c];
		ch += res;
	}
	if(ch == 0){
		return 1;
	}
	cost[v] += 2*ch-1;
	return 0;
}

int main(){
	int N;
	cin >> N;
	if(N == 1){
		cout << 2 << endl;
		return 0;
	}
	for(int i = 1; i < N; i++){
		int u, v;
		cin >> u >> v;
		u--; v--; 
		adj[u].push_back(v);
		adj[v].push_back(u);
	}
	int res = dfs0(0, -1);
	if(res == 1){
		cost[0] += 2;
	}
	cout << cost[0] << endl;

}