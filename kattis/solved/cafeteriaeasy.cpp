#include <bits/stdc++.h>

using namespace std;

int main()
{
	cin.tie(0)->sync_with_stdio(0);
	array<array<pair<int, int>, 4>, 4> G;
	for (array<pair<int, int>, 4> &GG : G)
		fill(begin(GG), end(GG), make_pair(-1, -1));
	array<array<int, 4>, 5> A;

	const auto read = [&]()
	{
		string str;
		cin >> str;
		if (str == "_")
			return -1;
		else
		{
			stringstream sstrm(str);
			int			 ans;
			sstrm >> ans;
			return ans;
		}
	};
	for (int i = 0; i < 5; i++)
	{
		A[i][0] = read();
		A[i][1] = read();
	}
	for (int i = 0; i < 5; i++)
	{
		A[i][2] = read();
		A[i][3] = read();
	}

	for (const array<int, 4> &AA : A)
	{
		for (int i = 0; i < 4; i++)
			for (int j = 0; j < 4; j++)
			{
				if (i == j || AA[i] == -1 || AA[j] == -1)
					continue;
				int g	= gcd(AA[i], AA[j]);
				G[i][j] = make_pair(AA[j] / g, AA[i] / g);
				G[j][i] = make_pair(AA[i] / g, AA[j] / g);
			}
	}

	for (int k = 0; k < 4; k++)
		for (int i = 0; i < 4; i++)
			for (int j = 0; j < 4; j++)
			{
				if (G[i][j].first != -1 || G[i][k].first == -1 || G[k][j].first == -1)
					continue;
				int n	= G[i][k].first * G[k][j].first;
				int d	= G[i][k].second * G[k][j].second;
				int g	= gcd(n, d);
				G[i][j] = make_pair(n / g, d / g);
			}

	for (array<int, 4> &AA : A)
	{
		for (int i = 0; i < 4; i++)
			if (AA[i] >= 0)
			{
				for (int j = 0; j < 4; j++)
					AA[j] = AA[i] * G[i][j].first / G[i][j].second;
				break;
			}
	}

	for (array<int, 4> &AA : A)
		cout << AA[0] << ' ' << AA[1] << ' ';
	cout << '\n';
	for (array<int, 4> &AA : A)
		cout << AA[2] << ' ' << AA[3] << ' ';
}
