#include <bits/stdc++.h>

using namespace std;

unordered_map<string, int> D;

int id()
{
	static string s;
	cin >> s;
	return D.emplace(move(s), (int)size(D)).first->second;
}

int main()
{
	cin.tie(0)->sync_with_stdio(0);

	int n, k;
	cin >> n >> k;
	vector<vector<int>> A(n);
	for (auto &AA : A)
	{
		int t;
		cin >> t;
		AA.resize(t);
		for (int &a : AA)
			a = id();
	}

	vector<int> M(size(D));
	int			ans = 0;

	for (int mask = 0; mask < (1 << n); mask++)
	{
		if (__builtin_popcount(mask) != k)
			continue;

		for (int i = 0; i < n; i++)
		{
			if ((mask & (1 << i)) == 0)
				continue;
			for (int a : A[i])
				M[a]++;
		}

		ans += *max_element(begin(M), end(M)) <= k / 2;
		fill(begin(M), end(M), 0);
	}

	cout << ans;
}
