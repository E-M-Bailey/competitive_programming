#include <bits/stdc++.h>

using namespace std;

int main()
{
	int b;
	string P, M, ans;
	while (cin >> b, b > 0)
	{
		cin >> P >> M;
		int m = 0;
		for (char c : M)
			m = m * b + c - '0';
		int r = 0;
		int64_t pw = 1;
		while (!P.empty())
		{
			int c = P.back() - '0';
			P.pop_back();
			r = int((r + c * pw) % m);
			pw = pw * b % m;
		}
		do
		{
			ans += char(r % b + '0');
		} while (r /= b);
		while (!ans.empty())
		{
			cout << ans.back();
			ans.pop_back();
		}
		cout << '\n';
	}
}