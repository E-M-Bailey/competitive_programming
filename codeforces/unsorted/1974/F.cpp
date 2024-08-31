#include <bits/stdc++.h>

using namespace std;

void go();

int main()
{
	cin.tie(0)->sync_with_stdio(0);
	int tc = 1;
	cin >> tc;
	while (tc--)
		go();
}

typedef long long ll;

struct merge_sort_tree
{
	int							   n;
	vector<vector<pair<int, int>>> S;
	merge_sort_tree(vector<vector<pair<int, int>>> &&A) : n((int)A.size()), S(n * 2)
	{
		move(begin(A), end(A), begin(S) + n);
		for (int i = n - 1; i >= 1; i--)
		{
			S[i].resize(S[i * 2].size() + S[i * 2 + 1].size());
			merge(begin(S[i * 2]), end(S[i * 2]), begin(S[i * 2 + 1]), end(S[i * 2 + 1]), begin(S[i]));
		}
	}
	static int count_y(vector<pair<int, int>> const &S, int ly, int ry)
	{
		return (int)(lower_bound(begin(S), end(S), pair{ry, 0}) - lower_bound(begin(S), end(S), pair{ly, 0}));
	}
	// Number of points in [lx, rx) cross [ly, ry)
	int count(int lx, int rx, int ly, int ry)
	{
		int ans = 0;
		for (lx += n, rx += n; lx < rx; lx /= 2, rx /= 2)
		{
			if (lx % 2)
				ans += count_y(S[lx++], ly, ry);
			if (rx % 2)
				ans += count_y(S[--rx], ly, ry);
		}
		return ans;
	}
};

void go()
{
	int li = 0, lj = 0, ri, rj, n, m;
	cin >> ri >> rj >> n >> m;
	int					   a = 0, b = 0;
	vector<int>			   I, J;
	vector<pair<int, int>> P(n);
	for (auto &[i, j] : P)
	{
		cin >> i >> j;
		i--;
		j--;
		I.push_back(i);
		J.push_back(j);
	}
	sort(begin(I), end(I));
	I.erase(unique(begin(I), end(I)), end(I));
	sort(begin(J), end(J));
	J.erase(unique(begin(J), end(J)), end(J));
	vector<vector<pair<int, int>>> A(size(I));
	for (auto &[i, j] : P)
	{
		i = int(lower_bound(begin(I), end(I), i) - begin(I));
		j = int(lower_bound(begin(J), end(J), j) - begin(J));
		A[i].emplace_back(j, i);
	}
	for (auto &AA : A)
		sort(begin(AA), end(AA));

	merge_sort_tree T(move(A));
	auto const qry = [&](int l1, int r1, int l2, int r2)
	{
		l1 = int(lower_bound(begin(I), end(I), l1) - begin(I));
		r1 = int(lower_bound(begin(I), end(I), r1) - begin(I));
		l2 = int(lower_bound(begin(J), end(J), l2) - begin(J));
		r2 = int(lower_bound(begin(J), end(J), r2) - begin(J));
		return T.count(l1, r1, l2, r2);
	};
	for (int t = 0; t < m; t++)
	{
		int &c = t % 2 ? b : a;
		char ch;
		int	 k;
		cin >> ch >> k;
		if (ch == 'U')
		{
			c += qry(li, li + k, lj, rj);
			li += k;
		}
		else if (ch == 'D')
		{
			c += qry(ri - k, ri, lj, rj);
			ri -= k;
		}
		else if (ch == 'L')
		{
			c += qry(li, ri, lj, lj + k);
			lj += k;
		}
		else
		{
			c += qry(li, ri, rj - k, rj);
			rj -= k;
		}
	}
	cout << a << ' ' << b << '\n';
}
