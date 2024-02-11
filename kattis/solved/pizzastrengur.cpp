#include <bits/stdc++.h>

using namespace std;

mt19937_64					  randy(91384901384139251ull);
uniform_int_distribution<int> distr(0, 3);

int main()
{
	cin.tie(0)->sync_with_stdio(0);
	int n;
	cin >> n;
	string s(1, '\0');
	int	   g = 0;

	for (;;)
	{
		int i = distr(randy);
		if (g & (1 << i))
			continue;
		g |= 1 << i;
		s.back() = "PIZA"[i];
		int q;
		if (__builtin_popcount(g) < 4 || (int)size(s) == n)
		{
			cout << s << '\n' << flush;
			cin >> q;
		}
		else
			q = 1;
		if (q == 2)
			break;
		else if (q == 1)
		{
			g = 0;
			s.push_back('\0');
		}
	}
}
