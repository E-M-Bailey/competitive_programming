#include <bits/stdc++.h>
using namespace std;

#pragma GCC optimize("Ofast,unroll-loops")
#pragma GCC target("avx2,bmi,bmi2,lzcnt,popcnt")

#define rep(i,a,b) for(int i = a; i<(b); ++i)
#define all(x) begin(x), end(x)
#define sz(x) int(size(x))
using ll = long long;
using pii = pair<int, int>;
using vi = vector<int>;

void solve()
{
	int n;
	cin >> n;
	vi A(n), B(n), D(n);
	rep(i, 0, n)
		cin >> A[i] >> B[i] >> D[i];

	vi IX;
	// vi ID;
	for (int a : A) IX.push_back(a);
	for (int b : B) IX.push_back(b);
	//for (int d : D) ID.push_back(d);
	//IX.push_back(0);
	//IX.push_back(10001);
	sort(all(IX));
	//sort(all(ID));
	IX.erase(unique(all(IX)), end(IX));
	//ID.erase(unique(all(ID)), end(ID));
	int xx = sz(IX);
	//int dd = sz(ID);
	//vi CX(10001, -1);
	//vi CD(10001, -1);
	//rep(i, 0, xx) CX[IX[i]] = i;
	//rep(i, 0, dd) CD[ID[i]] = i;

	vector<vi> DP(xx + 1, vi(xx + 1));
	rep(s, 1, xx) for (int i = 0, j = s; j < xx; i++, j++)
	{
		int dm = 0;
		int l = IX[i], r = IX[j];
		rep(k, 0, n)
			if (l <= A[k] && B[k] <= r)
				dm = max(dm, D[k]);
		int &dp = DP[i][j];
		if (s > 1)
		{
			dp = INT_MAX;
			rep(k, i + 1, j)
				dp = min(dp, DP[i][k - 1] + DP[k + 1][j]);
		}
		dp += dm;
		//cerr << i << ' ' << j << ' ' << dp << endl;
	}

	cout << DP[0][xx - 1] << '\n';
}

int main()
{
	int T;
	cin >> T;
	while (T--)
		solve();
}