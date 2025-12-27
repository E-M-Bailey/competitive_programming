#include <bits/stdc++.h>

using namespace std;

int main()
{
	int n;
	string dummy;
	bool nfst = false;
	while (cin >> n, n)
	{
		if (nfst)
			cout << '\n';
		nfst = true;
		getline(cin, dummy);
		vector<string> in(n);
		int m = 0;
		for (auto &row : in)
		{
			getline(cin, row);
			m = max(m, (int)row.size());
		}
		for (auto &row : in)
			row.resize(m, ' ');

		string out;
		for (int i = 0; i < m; i++)
		{
			out.clear();
			for (int j = 0; j < n; j++)
			{
				char c = in[n - 1 - j][i];
				if (c == '|')
					c = '-';
				else if (c == '-')
					c = '|';
				if (c != ' ')
				{
					out.resize(j, ' ');
					out.push_back(c);
				}
			}
			cout << out << '\n';
		}
	}
}