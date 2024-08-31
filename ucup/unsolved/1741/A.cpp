#include <bits/stdc++.h>

using namespace std;

int constexpr M = 998244353;

int fac(int n)
{
	static vector<int> F{1};
	while ((int)size(F) <= n)
		F.push_back(int((long long)F.size() * F.back() % M));
	return F[n];
}

int main()
{
	cin.tie(0)->sync_with_stdio(0);

	int T;
	cin >> T;

	while (T--)
	{
		int n, m1, m2;
		cin >> n >> m1 >> m2;
		map<pair<int, int>, int> A;
		for (int i = 0; i < n; i++)
		{
			int x;
			cin >> x;
			int a1 = x % m1;
			int a2 = -(x % m2);
			A[pair{a1, a2}]++;
		}
		if (!is_sorted(begin(A),
					   end(A),
					   [&](pair<pair<int, int>, int> a, pair<pair<int, int>, int> b)
					   {
						   return pair{a.first.second, a.first.first} < pair{b.first.second, b.first.first};
					   }))
		{
			cout << "0\n";
			continue;
		}

		long long ans = 1;
		for (auto [a, f] : A)
			ans = ans * fac(f) % M;
		cout << ans << '\n';
	}
}
