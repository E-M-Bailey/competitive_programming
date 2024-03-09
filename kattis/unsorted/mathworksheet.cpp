#include <bits/stdc++.h>

using namespace std;

int main()
{
	int n;
	bool fst = true;
	while (cin >> n, n)
	{
		if (!fst)
			cout << '\n';
		fst = false;
		vector<string> ans(n);
		int len = 0;
		for (auto &s : ans)
		{
			int a, b;
			char op;
			cin >> a >> op >> b;
			s = to_string(op == '+' ? a + b : op == '-' ? a - b : a * b);
			len = max(len, (int)size(s));
		}
		int ct = 1;
		while ((ct + 1) * (len + 1) - 1 <= 50)
			ct++;
		for (int i = 0; i < n; i++)
		{
			string pad;
			while (pad.size() + ans[i].size() < len)
				pad += ' ';
			cout << pad << ans[i];
			if (i < n - 1)
				cout << ((i + 1) % ct == 0 ? '\n' : ' ');
		}
		cout << "\n";
	}
}