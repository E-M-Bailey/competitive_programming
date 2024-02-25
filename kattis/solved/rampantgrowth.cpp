#include <bits/stdc++.h>

using namespace std;

int constexpr MOD = 998244353;

int main()
{
	int r, c;
	cin >> r >> c;
	int64_t ans = r;
	for (int i = 1; i < c; i++)
		ans = ans * (r - 1) % MOD;
	cout << ans;
}
