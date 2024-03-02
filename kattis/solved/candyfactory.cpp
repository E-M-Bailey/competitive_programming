#include <bits/stdc++.h>

using namespace std;

int main()
{
	int64_t n, k, a, m = 0, s = 0;
	cin >> n >> k;
	while (n--)
	{
		cin >> a;
		m = max(m, a);
		s += a;
	}
	cout << max(m, (s + k - 1) / k) * k - s;
}
