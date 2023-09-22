#include <bits/stdc++.h>

using namespace std;

int main(int argc, const char* argv[])
{
	if (argc > 1)
	{
		ignore = freopen(argv[1], "r", stdin);
		ignore = freopen(argv[2], "w", stdout);
	}

	int T;
	cin >> T;
	while (T--)
	{
		int k, m, n;
		cin >> k >> m >> n;
		vector<uint32_t> A(n + 1, 1);
		for (int p = m; p <= n; p *= m)
			for (int i = p; i <= n; i++)
				A[i] += A[i - p];
		cout << k << ' ' << A.back() << '\n';
	}
}