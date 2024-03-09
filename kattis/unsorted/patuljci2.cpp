#include <bits/stdc++.h>

using namespace std;

int main()
{
	int n, c;
	cin >> n >> c;
	vector<vector<int>> I(c);
	for (int i = 0; i < n; i++)
	{
		int col;
		cin >> col;
		I[col - 1].push_back(i);
	}

	int m;
	cin >> m;
	while (m--)
	{
		int a, b;
		cin >> a >> b;
		a--;
		bool fnd = false;
		for (int col = 0; col < c; col++)
		{
			auto fst = lower_bound(begin(I[col]), end(I[col]), a);
			auto lst = lower_bound(begin(I[col]), end(I[col]), b);
			if ((lst - fst) > (b - a) / 2)
			{
				//cerr << (b - a) / 2 << ' ' << lst - fst << endl;
				fnd = true;
				cout << "yes " << col + 1 << '\n';
				break;
			}
		}
		if (!fnd)
			cout << "no\n";
	}
}