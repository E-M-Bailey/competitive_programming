#include <bits/stdc++.h>

using namespace std;

int solve(vector<pair<int, int>> const &A, vector<pair<int, int>> const &B)
{
	static map<int, int> S;

	int ans = INT_MAX;
	int n = (int)size(A), m = (int)size(B);
	int t = min(A[0].first, B[0].first);
	int i = 0, j = 0;
	while (i < n || j < m)
	{
		while (i < n && A[i].first == t)
		{
			auto [x, y]	   = A[i++];
			auto [it, ins] = S.emplace(y, x);
			if (!ins)
				it->second = x;

			while (it != begin(S))
			{
				auto jt		= prev(it);
				auto [q, p] = *jt;
				if (y - q > x - p)
					break;
				S.erase(jt);
			}
			for (map<int, int>::iterator jt; (jt = next(it)) != end(S);)
			{
				auto [q, p] = *jt;
				if (q - y > x - p)
					break;
				S.erase(jt);
			}
		}
		while (j < m && B[j].first == t)
		{
			auto [x, y] = B[j++];
			auto it		= S.lower_bound(y);
			if (it != end(S))
			{
				auto [q, p] = *it;
				ans			= min(ans, x - p + q - y);
			}
			if (it != begin(S))
			{
				auto [q, p] = *prev(it);
				ans			= min(ans, x - p + y - q);
			}
		}
		t = min(i < n ? A[i].first : INT_MAX, j < m ? B[j].first : INT_MAX);
	}
	S.clear();
	return ans;
}

int main()
{
	cin.tie(0)->sync_with_stdio(0);
	int					   n, m;
	vector<pair<int, int>> A, B;
	while (cin >> n, n)
	{
		A.resize(n);
		for (auto &[a, b] : A)
			cin >> a >> b;
		cin >> m;
		B.resize(m);
		for (auto &[c, d] : B)
			cin >> c >> d;
		sort(begin(A), end(A));
		sort(begin(B), end(B));
		cout << min(solve(A, B), solve(B, A)) << '\n';
	}
}
