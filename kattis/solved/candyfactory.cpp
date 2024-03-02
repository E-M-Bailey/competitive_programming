#include <bits/stdc++.h>

using namespace std;

int main()
{
	int n;
	int64_t k, sum = 0, mx = 0;
	cin >> n >> k;

	for (int i = 0; i < n; i++)
	{
		int64_t a;
		cin >> a;
		sum += a;
		mx = max(mx, a);
	}

	cout << max(mx, (sum + k - 1) / k) * k - sum;
}
