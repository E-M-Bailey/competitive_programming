#include <bits/stdc++.h>

using namespace std;

int main()
{
	int n, q;
	string s;
	cin >> n >> s >> q;
	vector<int> T(n, 0);
	bool u;
	int ts = -1;
	for (int i = 0; i < q; i++)
	{
		int t, x;
		char c;
		cin >> t >> x >> c;
		--x;

		if (t == 1)
		{
			s[x] = c;
			T[x] = i;
		}
		else
		{
			ts = i;
			u = t == 3;
		}
	}

	for (int i = 0; i < n; i++)
		if (T[i] < ts)
			s[i] = u ? s[i] & ~32 : s[i] | 32;
	cout << s;
}