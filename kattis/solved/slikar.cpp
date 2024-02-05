#include <bits/stdc++.h>

using namespace std;

template<>
struct std::hash<pair<int, int>>
{
	constexpr size_t operator()(pair<int, int> x) const noexcept
	{
		return (size_t)x.first * 31 + x.second;
	}
};

vector<pair<int, int>> DIR{pair(-1, 0), pair(0, -1), pair(0, 1), pair(1, 0)};

int main()
{
	cin.tie(0)->sync_with_stdio(0);
	int r, c;
	cin >> r >> c;

	vector<string> G(r);
	for (string &GG : G)
		cin >> GG;

	unordered_set<pair<int, int>> W, S;
	for (int i = 0; i < r; i++)
		for (int j = 0; j < c; j++)
		{
			char		   g = G[i][j];
			pair<int, int> p = make_pair(i, j);
			if (g == 'S')
			{
				S.insert(p);
				G[i][j] = 'X';
			}
			else if (g == '*')
			{
				W.insert(p);
				G[i][j] = 'X';
			}
		}

	const auto nb = [&](pair<int, int> ij) -> vector<pair<int, int>>
	{
		vector<pair<int, int>> ans;
		for (pair<int, int> d : DIR)
		{
			int k = ij.first + d.first, l = ij.second + d.second;
			if (k >= 0 && k < r && l >= 0 && l < c && G[k][l] != 'X')
				ans.emplace_back(k, l);
		}
		return ans;
	};

	unordered_set<pair<int, int>> W2, S2;
	int							  ans = 0;
	for (;;)
	{
		ans++;
		W2.clear();
		S2.clear();
		for (pair<int, int> w : W)
			for (auto [i, j] : nb(w))
				if (G[i][j] != 'D')
				{
					W2.emplace(i, j);
					G[i][j] = 'X';
				}
		for (pair<int, int> s : S)
			for (auto [i, j] : nb(s))
			{
				if (G[i][j] == 'D')
				{
					cout << ans << '\n';
					return 0;
				}
				S2.emplace(i, j);
				G[i][j] = 'X';
			}

		if (S2.empty())
		{
			cout << "KAKTUS" << '\n';
			return 0;
		}
		W = move(W2);
		S = move(S2);
	}
}
