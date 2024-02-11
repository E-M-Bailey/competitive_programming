#include <bits/stdc++.h>

using namespace std;

array<bool, 200> V{};

int main()
{
	cin.tie(0)->sync_with_stdio(0);
	char cmd;
	int	 n;
	cin >> cmd >> n;

	for (int i = 0; i < 6; i++)
	{
		int c = "aeiouy"[i];
		V[c] = V[cmd ^ 32] = true;
	}

	string ln;
	getline(cin, ln);
	while (n--)
	{
		getline(cin, ln);
		if (cmd == 'D')
		{
			for (char c : ln)
			{
				bool cp = 'A' <= c && c <= 'Z';

				if (V[c])
					cout << (cp ? "Ub" : "ub") << char(c | 32);
				else
					cout << c;
			}
		}
		else
		{
			for (int i = 0; i < (int)size(ln); i++)
			{
				if (i + 2 < (int)size(ln) && (ln[i] == 'U' || ln[i] == 'u') && ln[i + 1] == 'b' && V[ln[i + 2]])
					i += 2;
				cout << ln[i];
			}
		}
		cout << '\n';
	}
}
