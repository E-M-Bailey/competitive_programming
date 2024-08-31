#include <bits/stdc++.h>

using namespace std;

#define sz(C) (int(size(C)))

int main()
{
	int n, k;
	cin >> n >> k;

	vector<vector<int>> S(k);
	vector<int>			C(k);
	for (int i = 0; i < k; i++)
	{
		cin >> C[i];
		S[i].resize(C[i]);
		for (int &s : S[i])
		{
			cin >> s;
			s--;
		}
		while (!S[i].empty() && S[i].back() < 0)
			S[i].pop_back();
	}

	auto const mv = [&](int s, int t)
	{
		assert(!S[s].empty());
		assert(sz(S[t]) < C[t]);
		S[t].push_back(S[s].back());
		S[s].pop_back();
		cout << s + 1 << ' ' << t + 1 << '\n';
	};

	int ei = int(max_element(begin(C), end(C)) - begin(C));

	vector<vector<int>> R1(k), R(k);
	int					p2 = 0;
	for (int v = 0; v < n; v++)
	{
		if (sz(R1[p2]) == C[p2])
			p2++;
		R1[p2].push_back(v);
	}
	for (int i = 0; i < ei; i++)
		R[i] = R1[i];
	for (int i1 = ei, i2 = ei + 1, j1 = 0, j2 = 0, v = R1[ei].front(); v < n; v++, j1++, j2++)
	{
		if (j1 == C[i1])
		{
			i1++;
			j1 = 0;
		}
		if (j2 == C[i2])
		{
			i2++;
			j2 = 0;
		}
		R[i2].push_back(R1[i1][j1]);
	}
	for (int i = ei + 1; i < k; i++)
		reverse(begin(R[i]), end(R[i]));

	int p1 = 0;
	while (!S[ei].empty())
	{
		while (p1 == ei || sz(S[p1]) == C[p1])
			p1++;
		mv(ei, p1);
	}

	for (int di = 0, dj = 0, w = 0; w < n; dj++, w++)
	{
		while (dj == sz(R[di]))
		{
			dj = 0;
			di++;
		}
		int v = R[di][dj];

		int ci, cj;
		for (int i = 0; i < k; i++)
			for (int j = 0; j < (int)size(S[i]); j++)
				if (S[i][j] == v)
					tie(ci, cj) = pair{i, j};

		assert(S[ei].empty());

		if (ci == di)
		{
			int fi = 0;
			while (fi == di || fi == ei)
				fi++;
			bool z = !S[fi].empty();
			if (z)
				mv(fi, ei);
			while (S[di].back() != v)
				mv(di, ei);
			mv(di, fi);
			while (sz(S[di]) > dj)
				mv(di, ei);
			mv(fi, di);
			while (sz(S[ei]) > (int)z)
				mv(ei, di);
			if (z)
				mv(ei, fi);
		}
		else
		{
			while (sz(S[di]) > dj && sz(S[ei]) + sz(S[ci]) - cj < C[ei])
				mv(di, ei);
			while (S[ci].back() != v)
				mv(ci, ei);
			mv(ci, ei);
			while (sz(S[di]) > dj)
				mv(di, ci);
			mv(ei, di);
			while (!S[ei].empty() && sz(S[di]) < C[di])
				mv(ei, di);
			while (!S[ei].empty())
				mv(ei, ci);
		}
	}
	for (int i1 = ei, i2 = ei + 1; i1 < k; i1++)
	{
		while (sz(S[i1]) < sz(R1[i1]))
		{
			while (i2 != k && S[i2].empty())
				i2++;
			if (i2 == k)
				break;
			mv(i2, i1);
		}
	}
	assert(R1 == S);
	cout << "0 0";
}
