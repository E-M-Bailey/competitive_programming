#include <bits/stdc++.h>
using namespace std;

#pragma GCC optimize("O3,unroll-loops")
#pragma GCC optimize("avx2,bmi,bmi2,lzcnt,popcnt")

#define rep(i,a,b) for (int i = a; i<(b); ++i)
#define all(x) begin(x),end(x)
#define sz(x) int(size(x))
typedef long long ll;
typedef pair<int, int> pii;
typedef vector<int> vi;

pair<int, int> const DIR[4]{
make_pair(1, 0),
make_pair(0, 1),
make_pair(-1, 0),
make_pair(0, -1)
};

void solve(string s)
{
	unordered_map<char, int> I;
	I['R'] = 0;
	I['U'] = 1;
	I['L'] = 2;
	I['D'] = 3;

	int n = sz(s);
	vi B(n);
	rep(i, 0, n)
		B[i] = I[s[i]];

	vector<int> A;
	vector<int> f;
	int ind = 0;
	f.push_back(1);
	while(ind+1 < n){
		if(B[ind]%2 == B[ind+1]%2){
			ind++;
			f.back()++;
		}
		else{
			A.push_back(B[ind]);
			ind++;
			f.push_back(1);
		}
	}
	A.push_back(B[ind]);
	if(f.back() >= 3) cout << "impossible\n";
	
	vector<pair<int, int>> ans;
	//reverse(begin(A), end(A));
	int x = 0, y = 0, d = 1<<21;
	for (int i = 0; i < n; i++)
	{
		auto [dx, dy] = DIR[A[i]];
		ans.emplace_back(x-dx, y-dy);
		x += dx * d;
		y += dy * d;
		ans.emplace_back(x + dx, y + dy);
		d /= 2;
	}
	rep(i, 0, sz(ans))
	{
		ans[i].first -= x;
		ans[i].second -= y;
	}
	x = -x;
	y = -y;
	sort(all(ans));
	ans.erase(unique(all(ans)), end(ans));
	cout << x << ' ' << y << '\n' << sz(ans) << '\n';
	for (auto [xx, yy] : ans)
		cout << xx << ' ' << yy << '\n';
}

int main()
{
#ifdef DBG
	freopen("in.txt", "r", stdin);
	freopen("out.txt", "w", stdout);
#endif
	cin.tie(0)->sync_with_stdio(0);
	cin.exceptions(cin.failbit);

	string s;
	cin >> s;
	solve(s);
}

// g++ -g -O2 -std=gnu++20 -static -DDBG X.cpp && ./a.out