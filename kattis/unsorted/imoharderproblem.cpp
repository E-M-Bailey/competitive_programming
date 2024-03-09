#include <bits/stdc++.h>

using namespace std;

typedef long double T;

int main(int argc, char const *argv[])
{
	if (argc > 1)
	{
		ignore = freopen(argv[1], "r", stdin);
		ignore = freopen(argv[2], "w", stdout);
	}

	string s;
	cin >> s;
	int n = (int)s.size();

	T ans = 0;

	int64_t t = 0, h = 0, q = 0;

	for (int i = 0; i < n; i++)
	{
		switch (s[i])
		{
		case 'H':
			h++;
			ans += 2 * (i + 1);
			break;
		case '?':
			q++;
			ans += i + 1;
			break;
		case 'T':
			t++;
			break;
		}
	}

	//cerr << fixed << setprecision(7) << ans << '\n' << h * (h + q) + 0.25l * (q + 1) * q;

	ans -= h * (h + q) + 0.25l * (q + 1) * q;

	cout << fixed << setprecision(7) << ans;
}