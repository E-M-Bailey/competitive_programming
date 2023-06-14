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

const int LIM = 1e7 + 1;

int main()
{
#ifdef DBG
	freopen("in.txt", "r", stdin);
	freopen("out.txt", "w", stdout);
#endif
	cin.tie(0)->sync_with_stdio(0);
	cin.exceptions(cin.failbit);

	vi HP(LIM, 0);
	//HP[1] = 1;
	rep(i, 2, LIM)
	{
		if (HP[i]) continue;
		for (int j = i; j < LIM; j += i)
			HP[j] = i;
	}

	int n;
	cin >> n;
	vi A(n);
	for (int &a : A)
		cin >> a;
	vector<vector<int>> I(LIM);
	rep(i, 0, n)
	{
		int a = A[i];
		while (a > 1)
		{
			int p = HP[a];
			I[p].push_back(i);
			while (a % p == 0)
				a /= p;
		}
	}

	vector<int> L(n), R(n);
	rep(i, 0, n)
	{

		int a = A[i];
		int l = 0, r = n;
		while (a > 1)
		{
			int p = HP[a];
			auto it = lower_bound(all(I[p]), i);
			if (it != I[p].begin())
				l = max(l, *prev(it) + 1);
			it++;
			if (it != I[p].end())
				r = min(r, *it);
			while (a % p == 0)
				a /= p;
		}
		L[i] = l;
		R[i] = r;
	}

	
}

// g+ -g -O2 -std=gnu++20 -static -DDBG X.cpp && ./a.out