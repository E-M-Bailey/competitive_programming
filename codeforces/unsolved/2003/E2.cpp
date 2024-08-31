#include <bits/stdc++.h>

using namespace std;

int main()
{
	int t;
	cin >> t;
	while (t--)
	{
		int n, m;
		cin >> n >> m;
		
		vector<pair<int, int>> A(n);
		for (auto &[l, r] : A)
			cin >> l >> r;
		
		sort(begin(A), end(A));

		vector<pair<pair<int, int>, pair<int, int>>> B;

		bool bad = false;

		for (auto [l, r] : A)
		{
			if (B.empty() || B.back().first.second < r)
				B.emplace_back(pair{l, r}, pair{l, r});
			else
			{
				auto &[un, is] = B.back();
				auto &[lu, ru] = un;
				auto &[li, ri] = is;
				lu = min(lu, l);
				ru = max(ru, r);
				li = max(li, l);
				ri = min(ri, r);
				bad |= li >= ri;
			}
		}
		if (bad)
		{
			cout << "-1\n";
			continue;
		}

		vector<pair<int, int>> I;
		for (int i = 0; i < (int)size(B); i++)
		{
			if (i == 0)
			{
				for (int j = 1; j < B[i].first.first; j++)
					I.emplace_back(0, 1);
			}
			
			auto [ad, bc] = B[i];
			auto [a, d] = ad;
			auto [b, c] = bc;
			I.emplace_back(b - a + 1, c - a);

			int r = i == (int)size(B) - 1 ? n + 1 : B[i + 1].first.first;
			for (int j = d + 1; j < r; j++)
				I.emplace_back(0, 1);
		}



	}
}

