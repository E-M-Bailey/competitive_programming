#include <bits/stdc++.h>

using namespace std;

int main()
{
	unordered_map<string, vector<int>> I;

	int n, k;
	cin >> n >> k;

	while (k--)
	{
		int	   i;
		string s;
		cin >> i >> s;
		I[s].push_back(i);
	}

	for (auto &[s, II] : I)
		sort(begin(II), end(II));

	vector<pair<int, int>> F, G;
	F.emplace_back(0, 1);
	int m;
	cin >> m;
	while (m--)
	{
		string s;
		cin >> s;
		int j = 0, sum = 0;
		for (int i : I[s])
		{
			while (j < F.size() && F[j].first <= i)
				sum += F[j++].second;
			if (sum)
				G.emplace_back(i, min(2, sum));
		}
		F.swap(G);
		G.clear();
	}
	int sum = 0;
	for (auto [j, f] : F)
		sum += f;

	if (sum == 0)
		cout << "impossible";
	else if (sum == 1)
		cout << "unique";
	else
		cout << "ambiguous";
}
