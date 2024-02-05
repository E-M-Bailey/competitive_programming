#include <bits/stdc++.h>

using namespace std;

int main()
{
	cin.tie(0)->sync_with_stdio(0);
	stringstream buf;
	string		 S;
	while (cin >> S)
	{
		buf << S << ": ";
		int			n = S.size();
		vector<int> D;
		for (char c : S)
			D.push_back(c - '0');
		int sum = accumulate(begin(D), end(D), 0);
		if (sum % n != 0)
		{
			buf << "invalid # of balls\n";
			continue;
		}
		int b = sum / n;

		vector<int> I(n, 0);
		for (int i = 0; i < n; i++)
		{
			int d = D[i];
			if (d != 0)
				I[(i + d) % n]++;
		}

		bool valid = true;
		for (int i = 0; i < n && valid; i++)
			valid &= I[i] == min(1, D[i]);

		if (valid)
			buf << "valid with " << b << " balls\n";
		else
			buf << "invalid pattern\n";
	}
	cout << buf.str();
}
