// right side, 6th row, middle table, The University of Texas at Dallas
#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

int N;
vector<ll> dp, dp2;
vector<ll> a;
vector<ll> t;
vector<int> adj[100000];

ll rp(int v){
	return -dp[v] + dp2[v] + a[v];
}

void dfs(int v, int p){
	dp[v] = 0;
	ll ma = 0;
	pair<int, int> p2 = {-1, -1}, a2 = {-1, -1};
	for(int i : adj[v]){
		if(i == p) continue;
		dfs(i, v);
		dp[v] += dp[i];
		if(t[i] == 3){
			if(a2.first == -1 || a[i] > a[a2.first]){
				a2.second = a2.first;
				a2.first = i;
			}
			else if(a2.second == -1 || a[i] > a[a2.second]){
				a2.second = i;
			}
		}
		ma = max(ma, (ll)a[i]);
		if(p2.first == -1 || rp(i) > rp(p2.first)){
			p2.second = p2.first;
			p2.first = i;
		}
		else if(p2.second == -1 || rp(i) > rp(p2.second)){
			p2.second = i;
		}
	}

	dp2[v] = dp[v];
	if(p2.first == -1) return;
	dp[v] = dp[v] + ma;
	//cout << v << " " << dp[v] << endl;
	if(a2.first != p2.first){
		dp[v] = max(dp[v], dp2[v] + a[a2.first] + rp(p2.first));
	}
	else {
		if(a2.second != -1)
			dp[v] = max(dp[v], dp2[v] + rp(p2.first) + a[a2.second]);
		if(p2.second != -1)
			dp[v] = max(dp[v], dp2[v] + rp(p2.second) + a[a2.first]);
	}
}

void process(){
	cin >> N;
	dp = vector<ll>(N);
	dp2 = vector<ll>(N);
	a = vector<ll>(N);
	t = vector<ll>(N);
	for(int i = 0; i < N; i++) {
		adj[i].clear();
		cin >> a[i];
	}
	for(int i = 0; i < N; i++) {
		adj[i].clear();
		cin >> t[i];
	}
	for(int i = 1; i < N; i++){
		int u, v;
		cin >> u >> v;
		u--; v--;
		adj[u].push_back(v);
		adj[v].push_back(u);
	}
	dfs(0, -1);
	ll res = dp[0] + a[0];
	cout << res << endl;
	for(int i = 0; i < N; i++){
		//cout << dp[i] << " ";
	}
	//cout << endl;
}

int main()
{
	int t;
	cin >> t;
	while(t--){
		process();
	}
}