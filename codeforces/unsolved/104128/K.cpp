#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

constexpr ll MOD = 1000000007, PHI = MOD - 1;

/*
void mfreq(vector<pair<int, int>> &l, vector<pair<int, int>> &r)

vector<pair<int, int>>& F(int n)
{
	static unordered_map<int, vector<pair<int, int>>> DP;

	auto &dp = DP[n];
	if (dp.empty())

}
*/

ll mpow(ll a, ll b)
{
	if ((a %= MOD) < 0)
		a += MOD;
	if ((b %= PHI) < 0)
		b += PHI;
	ll ans = 1;
	for (; b; b /= 2, a = a * a % MOD)
		if (b % 2)
			ans = ans * a % MOD;
	return ans;
}

ll fac(int n)
{
	static vector<ll> FC{1};
	while (n >= (int)size(FC))
		FC.push_back(FC.back() * (ll)size(FC) % MOD);
	return FC[n];
}

ll nCr(int n, int r)
{
	if (r < 0 || r > n)
		return 0;
	return fac(n) * mpow(fac(r) * fac(n - r), -1) % MOD;
}

vector<vector<pair<int, ll>>> CH;
vector<pair<int, ll>>		  P;
vector<ll>					  F;
vector<int>					  S;

int left(int n)
{
	int b = n;
	while (b & (b - 1))
		b &= (b - 1);
	return 2 * n < 3 * b ? n - (b + 1) / 2 : b - 1;
}

int dfs1(int n, int p = -1, ll f = 1, ll acc = 1)
{
	int v = (int)size(P);
	CH.emplace_back();
	P.emplace_back(p, f);
	F.push_back(acc);
	S.push_back(n);

	int l = left(n);
	int r = n - 1 - l;
	if (l && r && l == r)
	{
		int w = dfs1(l, v, 2, acc * 2);
		CH[v].emplace_back(w, 2);
	}
	else
	{
		if (l)
		{
			int w = dfs1(l, v, 1, acc);
			CH[v].emplace_back(w, 1);
		}
		if (r)
		{
			int w = dfs1(r, v, 1, acc);
			CH[v].emplace_back(w, 1);
		}
	}
	return v;
}

vector<ll> H_DP;

// H/S[v]!
ll ct_hp(int v)
{
	if (v >= (int)size(H_DP))
		H_DP.resize(v + 1, -1);
	ll dp = H_DP[v];

	if (dp < 0)
	{
		if (CH[v].empty())
			dp = 1;
		else if ((int)size(CH[v]) == 1)
		{
			int w = CH[v][0].first;
			if (CH[v][0].second == 1)
				dp = ct_hp(w) * mpow(S[v], -1) % MOD;
			else
			{
				ll rec = ct_hp(w);
				// dp	   = nCr(S[v] - 1, S[w]) * rec % MOD * rec % MOD;
				dp = mpow(S[v], -1) * rec % MOD * rec % MOD;
			}
		}
		else
		{
			int w = CH[v][0].first, x = CH[v][1].first;
			// dp = nCr(S[v] - 1, S[w]) * ct_hp(w) % MOD * ct_hp(x) % MOD;
			dp = mpow(S[v], -1) * ct_hp(w) % MOD * ct_hp(x) % MOD;
		}
		H_DP[v] = dp;
	}
	return dp;
}

vector<bool> anc;

// G/(# vertices under v but not a)!
ll ct_hp_above(int v, int a)
{
	int sa = S[a];
	if (!anc[v])
		return ct_hp(v);
	else if (v == a || CH[v].empty())
		return 1;
	else if ((int)size(CH[v]) == 1)
	{
		int w = CH[v][0].first;
		if (CH[v][0].second == 1)
			// return ct_hp_above(w, a);
			return mpow(S[v] - sa, -1) * ct_hp_above(w, a) % MOD;
		else
			// return nCr(S[v] - sa - 1, anc[w] ? S[w] - sa : S[w]) * ct_hp_above(w, a) % MOD * ct_hp(w) % MOD;
			return mpow(S[v] - sa, -1) * ct_hp_above(w, a) % MOD * ct_hp(w) % MOD;
	}
	else
	{
		int w = CH[v][0].first, x = CH[v][1].first;
		// return nCr(S[v] - sa - 1, anc[w] ? S[w] - sa : S[w]) * ct_hp_above(w, a) % MOD * ct_hp_above(x, a) % MOD;
		return mpow(S[v] - sa, -1) * ct_hp_above(w, a) % MOD * ct_hp_above(x, a) % MOD;
	}
}

int main()
{
	int tc;
	cin >> tc;
	while (tc--)
	{
		CH.clear();
		P.clear();
		F.clear();
		S.clear();
		H_DP.clear();

		int n;
		cin >> n;
		dfs1(n);

		int k = (int)size(P);
		anc.assign(k, false);
		ll ans = 0;
		for (int v = 0; v < k; v++)
		{
			for (int a = v; a >= 0; a = P[a].first)
				anc[a] = true;

			//ll x = nCr(n - 1, S[v] - 1), y = ct_hp(v), z = ct_hp_above(0, v);
			ll cur = mpow(n, -1) * S[v] % MOD * ct_hp(v) % MOD * ct_hp_above(0, v) % MOD;
			ans	   = (ans + cur * F[v]) % MOD;

			for (int a = v; a >= 0; a = P[a].first)
				anc[a] = false;
		}
		cout << ans << '\n';
	}
}
