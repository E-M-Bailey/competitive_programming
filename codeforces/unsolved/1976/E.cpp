#include <bits/stdc++.h>

using namespace std;

#define sz(C)  (int(size(C)))
#define all(C) begin(C), end(C)

void go();

int main(int argc, char const *argv[])
{
	if (argc > 1)
	{
		ignore = freopen(argv[1], "r", stdin);
		ignore = freopen(argv[2], "w", stdout);
	}
	cin.tie(0)->sync_with_stdio(0);

	int tc = 1;
	// cin >> tc;
	while (tc--)
		go();
}

constexpr int M = 998244353;

void go()
{
	int n, q;
	cin >> n >> q;
	vector<pair<int, int>> Q(q);
	for (auto &[a, b] : Q)
		cin >> a;
	for (auto &[a, b] : Q)
		cin >> b;
	list<int>					L{n};
	vector<list<int>::iterator> I(n + 1, end(L));
	I[n] = begin(L);
	vector<bool>				V(n + 1, false);
	for (auto [a, b] : Q)
	{
		V[a] = V[b] = true;
		if (a < b)
			I[a] = L.insert(I[b], a);
		else
			I[b] = L.insert(next(I[a]), b);
	}
	vector<int> C(n + 1);
	for (auto it = begin(L); it != end(L);)
	{
		auto jt = next(it);
		C[*it] += (it == begin(L) || *it > *prev(it)) + (jt == end(L) || *it > *jt);
		it = jt;
	}
	int		  ct  = 0;
	long long ans = 1;
	for (int i = n; i >= 1; i--)
	{
		ct += C[i];
		if (!V[i])
			ans = ans * ct++ % M;
	}
	cout << ans;
}
