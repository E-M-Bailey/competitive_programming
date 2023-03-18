#include <bits/stdc++.h>

using namespace std;

struct dso
{
	int n;
	vector<int> R, P, L;
	dso(vector<int>&& lens): n(size(lens)), R(n), P(n), L(move(lens))
	{
		iota(begin(P), end(P), 0);
	}
	int find(int x)
	{
		while (x != P[x])
			tie(x, P[x]) = make_pair(P[x], P[P[x]]);
		return x;
	}
	bool onion(int x, int y)
	{
		x = find(x);
		y = find(y);
		if (x == y)
			return false;
		if (R[x] < R[y])
			swap(x, y);
		P[y] = x;
		R[x] += R[x] == R[y];
		if (L[y] < L[x])
			L[x] = L[y];
		return true;
	}
};

int main(int argc, const char* argv[])
{
	int n, m;
	cin >> n >> m;

	unordered_map<string, int> CC;
	vector<string> ICC;
	vector<int> A(n);

	CC.reserve(n + 2 * m);
	ICC.reserve(n + 2 * m);

	string s, t;
	for (int i = 0; i < n; i++)
	{
		cin >> s;
		auto [it, ins] = CC.try_emplace(s, size(CC));
		if (ins)
			ICC.push_back(move(s));
		A[i] = it->second;
	}

	vector<pair<int, int>> E(m);
	for (auto& [u, v] : E)
	{
		cin >> s >> t;
		auto [it, ins] = CC.try_emplace(s, size(CC));
		if (ins)
			ICC.push_back(move(s));
		u = it->second;
		tie(it, ins) = CC.try_emplace(t, size(CC));
		if (ins)
			ICC.push_back(move(t));
		v = it->second;
	}

	int k = size(CC);
	vector<int> lens(k);
	for (int i = 0; i < k; i++)
		lens[i] = size(ICC[i]);
	dso D(move(lens));

	for (auto [u, v] : E)
		D.onion(u, v);

	int ans = 0;
	for (int a : A)
		ans += D.L[D.find(a)];
	cout << ans;
}