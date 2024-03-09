#include <bits/stdc++.h>
using namespace std;

typedef long double ldf;

int N, Q;
int par[300000];
vector<int> adj[300000];

void process(int v, int sz, vector<int> &p){
	if(sz == 0) return;
	if(adj[v].size() == 0){
		for(int i = 0; i < sz; i++) p[i] = v;
		return;
	}
	vector<vector<int>> pp(adj[v].size(), vector<int>(0));
	for(int i = 0; i < adj[v].size(); i++){
		int ns = (sz-i+adj[v].size()-1)/adj[v].size();
		pp[i] = vector<int>(ns, 0);
		process(adj[v][i], (sz-i+adj[v].size()-1)/adj[v].size(), pp[i]);
	}
	int ind = 0;
	for(int i = 0; i < pp[0].size(); i++){
		for(int e = 0; e < pp.size(); e++){
			p[ind++] = pp[e][i];
		}
	}
}

int main()
{
	cin >> N >> Q;
	par[0] = -1;
	for(int i = 1; i < N; i++){
		cin >> par[i];
		adj[par[i]].push_back(i);
	}
	vector<int> v;
	process(0, Q, v);
	for(int i : v) cout << i << endl;
}