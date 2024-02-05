#include <bits/stdc++.h>

using namespace std;

int constexpr PTS[31]{100, 75, 60, 50, 45, 40, 36, 32, 29, 26, 24, 22, 20, 18, 16, 15,
					  14,  13, 12, 11, 10, 9,  8,  7,  6,  5,  4,  3,  2,  1,  0};

int main()
{
	int n;
	cin >> n;
	map<int, map<int, map<int, vector<int>>>> A;
	vector<int>								  ans(n);
	for (int i = 0; i < n; i++)
	{
		int s, p, f;
		cin >> s >> p >> f >> ans[i];
		A[-s][p][f].push_back(i);
	}

	int rank = 0;
	for (auto const &[s, AA] : A)
		for (auto const &[p, AAA] : AA)
			for (auto const &[f, AAAA] : AAA)
			{
				int pts = 0;
				for (int i : AAAA)
					pts += PTS[min(rank++, 30)];
				pts = (pts + (int)AAAA.size() - 1) / (int)AAAA.size();
				for (int i : AAAA)
					ans[i] += pts;
			}

	for (int a : ans)
		cout << a << '\n';
}
