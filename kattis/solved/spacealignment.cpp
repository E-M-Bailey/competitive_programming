#include <bits/stdc++.h>

using namespace std;

int main()
{
	int n;
	cin >> n;
	vector<tuple<int, int, int>> A(n);
	string ln;
	int lvl = 0;
	for (auto &[s, t, d] : A)
	{
		cin >> ln;
		if (ln.back() == '}')
			lvl--;
		for (char c : ln)
		{
			s += c == 's';
			t += c == 't';
		}
		d = lvl;
		if (ln.back() == '{')
			lvl++;
	}

	for (int num = 1; num <= 1000; num++)
	{
		bool good = true;
		int per = -1;
		for (auto [s, t, d] : A)
		{
			int amt = s + t * num;
			if (d == 0 || amt % d != 0 || (per >= 0 && amt / d != per))
			{
				if (d == 0 && amt == 0)
					continue;
				good = false;
				break;
			}
			per = amt / d;
		}
		if (!good)
			continue;
		cout << num;
		return 0;
	}
	cout << -1;
}
