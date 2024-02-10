#include <bits/stdc++.h>

using namespace std;

int main()
{
	int	   n;
	string s;
	while (cin >> n, n)
	{
		vector<int> A(n);
		for (int &a : A)
		{
			cin >> s;
			int m = (int)size(s);
			a	  = stoi(s.substr(0, m - 3)) * 100 + stoi(s.substr(m - 2));
		}
		int sum = accumulate(begin(A), end(A), 0);
		int avg = sum / n, rem = sum % n;
		int ans = 0;
		for (int a : A)
			if (a > avg)
			{
				int tgt = avg;
				if (rem)
				{
					rem--;
					tgt++;
				}
				ans += a - tgt;
			}
		cout << '$' << ans / 100 << '.' << ans / 10 % 10 << ans % 10 << '\n';
	}
}
