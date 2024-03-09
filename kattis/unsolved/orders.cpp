#include <bits/stdc++.h>

using namespace std;

int main()
{
	int n;
	cin >> n;
	vector<int> C(n);
	for (int &c : C)
		cin >> c;

	vector<int> P(30001, 0);
	P[0] = 1;
	for (int i = 0; i < n; i++)
	{
		int c = C[i];
		for (int j = c; j <= 30000; j++)
		{
			int k = j - c;
			if (P[k] == 0)
				continue;
			else if (P[k] < 0 || P[j] != 0)
				P[j] = -1;
			else
				P[j] = i + 1;
		}
	}


	int m;
	cin >> m;
	vector<int> ans;
	while (m--)
	{
		int s;
		cin >> s;
		if (P[s] == 0)
		{
			cout << "Impossible\n";
			continue;
		}

		while (s != 0)
		{
			if (P[s] < 0)
			{
				cout << "Ambiguous\n";
				ans.clear();
				break;
			}
			ans.push_back(P[s]);
			s -= C[P[s] - 1];
		}
		if (!ans.empty())
		{
			do
				cout << ans.back() << ' ';
			while (ans.pop_back(), !ans.empty());
			cout << '\n';
		}
	}
}