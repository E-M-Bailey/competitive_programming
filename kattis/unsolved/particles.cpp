#include <bits/stdc++.h>

using namespace std;

typedef long double ld;
typedef pair<int, int> pii;

int n;
vector<int> adj1[500];
int x[500], y[500];

int N;
vector<int> adj[250000];
vector<pair<ld, pii>> edges;
int par[250000];

int find(int a){
	if(a == par[a]) return a;
	return (par[a] = find(par[a]));
}
void merge(int a, int b){
	a = find(a);
	b = find(b);
	if(a == b) return;
	
}

long double res[500][500];

ld dst(int i, int e){
	return (ld)((x[i]-x[e])*(x[i]-x[e])+(y[i]-y[e])*(y[i]-y[e]));
}

int main()
{
	cin >> n;
	for(int i = 0; i < n; i++){
		int u, v;
		cin >> u >> v;
		u--; v--;
		adj1[u].push_back(v);
		adj1[v].push_back(u);
	}
	for(int i = 0; i < n; i++){
		for(int e = 0; e < n; e++){
			int ind = i*n+e;
			for(int c : adj1[i]){
				int ind2 = c*n+e;
				adj1[ind].push_back(ind2);
				ld d = min(dst(i, e), dst(c, e));
				edges.push_back(make_pair(d, make_pair(ind, ind2)));
			}
			for(int c : adj1[e]){
				int ind2 = i*n+c;
				adj1[ind].push_back(ind2);
				ld d = min(dst(i, e), dst(i, c));
				edges.push_back(make_pair(d, make_pair(ind, ind2)));
			}
		}
	}
	sort(edges.begin(), edges.end());

	

}