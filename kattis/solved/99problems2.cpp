#include <bits/stdc++.h>

using namespace std;

int main()
{
	int n, q;
	cin >> n >> q;

	multiset<int> D;
	while (n--)
	{
		int d;
		cin >> d;
		D.insert(d);
	}

	while (q--)
	{
		int t, d;
		cin >> t >> d;
		auto it = D.upper_bound(d);
		if (t == 1)
		{
			if (it == D.end())
				cout << -1;
			else
			{
				cout << *it;
				D.erase(it);
			}
		}
		else
		{
			if (it == D.begin())
				cout << -1;
			else
			{
				cout << *--it;
				D.erase(it);
			}
		}
		cout << '\n';
	}
}
