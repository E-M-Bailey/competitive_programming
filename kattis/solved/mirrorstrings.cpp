#include <bits/stdc++.h>

using namespace std;

int main()
{
	int l, r;
	cin >> l >> r;
	vector<int64_t> C(r + 1), D(r + 1);
	C[0] = D[0] = 1;
	C[1]		= 5;
	D[1]		= 2;
	int64_t ans = 0;
	for (int i = 2; i <= r; i++)
	{
		C[i] = C[i - 2] * 5 % 1000000007;
		D[i] = D[i - 2] * 2 % 1000000007;
	}
	for (int i = 0; i <= r; i++)
		if (i >= l)
			ans = (ans + C[i] + D[i]) % 1000000007;
	cout << ans;
}
