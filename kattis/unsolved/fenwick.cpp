#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

int main()
{
	cin.tie(0)->sync_with_stdio(0);
	int n, q;
	cin >> n >> q;
	vector<ll> T(n);
	
	while (q--)
	{
		char c;
		cin >> c;
		if (c == '?')
		{
			int i;
			long long s = 0;
			cin >> i;
			for (; i; i &= i - 1)
				s += T[i - 1];
			cout << s << '\n';
		}
		else
		{
			int i, d;
			cin >> i >> d;
			for (; i < n; i |= i + 1)
				T[i] += d;
		}
	}
}
