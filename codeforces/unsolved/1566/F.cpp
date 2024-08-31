#include <bits/stdc++.h>

using namespace std;

int main()
{
	cin.tie(0)->sync_with_stdio(0);

	int tc;
	cin >> tc;
	while (tc--)
	{
		vector<int> X;
		int			n, m;
		cin >> n >> m;
		vector<int>			   A(n);
		vector<pair<int, int>> I(m);
		for (int &a : A)
		{
			cin >> a;
			X.push_back(a);
		}
		for (auto &[l, r] : I)
		{
			cin >> l >> r;
			X.push_back(l);
			X.push_back(r);
		}
		sort(begin(X), end(X));
		X.erase(unique(begin(X), end(X)), end(X));
		for (int &a : A)
			a = int(lower_bound(begin(X), end(X), a) - begin(X));
		for (auto &[l, r] : I)
		{
			l = int(lower_bound(begin(X), end(X), l) - begin(X));
			r = int(lower_bound(begin(X), end(X), r) - begin(X));
		}
		sort(begin(A), end(A));

		I.erase(remove_if(begin(I),
						  end(I),
						  [&](pair<int, int> lr)
						  {
							  return lower_bound(begin(A), end(A), lr.first) !=
									 upper_bound(begin(A), end(A), lr.second);
						  }),
				end(I));

		vector<vector<pair<int, int>>> II(n + 1);
		for (auto [l, r] : I)
			II[lower_bound(begin(A), end(A), l) - begin(A)].emplace_back(l, r);

		vector<vector<pair<int, int>>> C(n + 1);

		C[0].emplace_back(0, 0);
		for (auto [l, r] : II[0])
			C[0][0].second = max(C[0][0].second, X[A[0]] - X[r]);
		C[n].emplace_back(0, 0);
		for (auto [l, r] : II[n])
			C[n][0].first = max(C[n][0].first, X[l] - X[A[n - 1]]);

		for (int i = 1; i < n; i++)
		{
			sort(rbegin(II[i]), rend(II[i]));
			int cr = 0;
			for (auto [l, r] : II[i])
			{
				C[i].emplace_back(X[l] - X[A[i - 1]], cr);
				cr = max(cr, X[A[i]] - X[r]);
			}
			C[i].emplace_back(0, cr);
		}

		long long c1 = 0, c2 = 0;
		for (auto const &CC : C)
		{
			long long d11 = LLONG_MAX, d12 = LLONG_MAX, d21 = LLONG_MAX, d22 = LLONG_MAX;
			for (auto [a, b] : CC)
			{
				d11 = min(d11, 1ll * a + 1ll * b);
				d12 = min(d12, 1ll * a + 2ll * b);
				d21 = min(d21, 2ll * a + 1ll * b);
				d22 = min(d22, 2ll * a + 2ll * b);
			}
			tie(c1, c2) = pair{min(c1 + d21, c2 + d11), min(c1 + d22, c2 + d12)};
		}

		cout << c1 << '\n';
	}
}
