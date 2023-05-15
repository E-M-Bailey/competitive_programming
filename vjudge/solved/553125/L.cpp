#include <bits/stdc++.h>

using namespace std;

int gcd(int a, int b)
{
	if (b == 0)
		return a;
	while (a)
		tie(a, b) = make_pair(b % a, a);
	return b;
}

int main(int argc, const char* argv[])
{
	if (argc > 1)
	{
		ignore = freopen(argv[1], "r", stdin);
		ignore = freopen(argv[2], "w", stdout);
	}

	int X, Y;
	while (cin >> X >> Y, X || Y)
	{
		vector<pair<int, int>> P;
		do
			P.emplace_back(X, Y);
		while (cin >> X >> Y, X || Y);
		sort(begin(P), end(P));
		int n = (int)P.size();

		vector<vector<bool>> V(n, vector<bool>(n));
		vector<unordered_map<int, unordered_map<int, vector<int>>>> I(n);
		vector<tuple<int, int, int>> L;
		bool fnd = false;
		for (int i = 0; i < n; i++)
			for (int j = i + 1; j < n; j++)
			{
				if (V[i][j])
					continue;
				auto [x1, y1] = P[i];
				auto [x2, y2] = P[j];
				int dx = x2 - x1, dy = y2 - y1;
				int g = gcd(dx, abs(dy));
				dx /= g;
				dy /= g;
				auto& II = I[i][dx][dy];
				if (II.empty())
				{
					II.push_back(i);
					L.emplace_back(i, dx, dy);
				}
				for (int k : II)
					V[k][j] = true;
				II.push_back(j);
				fnd |= II.size() >= 3;
			}
		if (!fnd)
		{
			cout << "No lines were found\n";
			continue;
		}
		cout << "The following lines were found:\n";
		for (auto [i, dx, dy] : L)
		{
			const vector<int>& II = I[i][dx][dy];
			if (II.size() < 3)
				continue;
			for (int j : II)
			{
				auto [x, y] = P[j];
				cout << '(' << setw(4) << x << ',' << setw(4) << y << ')';
			}
			cout << '\n';
		}
	}
}