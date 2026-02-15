#include <bits/stdc++.h>

using namespace std;
namespace rng = ranges;
namespace vws = views;

int main()
{
	int T;
	cin >> T;
	while (T--)
	{
		int n;
		cin >> n;
		bool c67 = false;
		while (n--)
		{
			int a;
			cin >> a;
			c67 |= a == 67;
		}
		cout << (c67 ? "YES\n" : "NO\n");
	}
}
