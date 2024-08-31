#include <bits/stdc++.h>

using namespace std;

int main()
{
	int t;
	cin >> t;
	while (t--)
	{
		int n, l;
		cin >> n >> l;
		int cq = 0;
		vector<pair<int, int>> A;
		for (int i = 0; i < n; i++)
		{
			int a, b;
			cin >> a >> b;
			if (a < 0 && b < 0)
				cq++;
			else
				A.emplace_back(a, b);
		}
		A.emplace_back(0, 0);
		A.emplace_back(l + 1, l + 1);
		sort(begin(A), end(A), [&](pair<int, int> ab, pair<int, int> cd)
		{
			auto [a, b] = ab;
			auto [c, d] = cd;
			int x = a < 0 ? b : a;
			int y = c < 0 ? d : c;
			return x < y;
		});

		n = (int)size(A);
		bool bad = false;
		int mq = 0, Mq = 0;
		for (int i = 0; i < n - 1; i++)
		{
			auto [a, b] = A[i];
			auto [c, d] = A[i + 1];
			int x = b < 0 ? a : b;
			int y = c < 0 ? d : c;
			bad |= x >= y;
			mq += (b >= 0 && c >= 0 && b < c - 1);
			Mq += y - x - 1;
		}
		bad |= cq < mq || cq > Mq;
		cout << (bad ? "NIE\n" : "TAK\n");
	}
}

