#include <bits/stdc++.h>

using namespace std;

int main()
{
	cin.tie(0)->sync_with_stdio(0);
	int64_t n, p, x, y;
	cin >> n >> p >> x >> y;
	cout << x * p + y * (p / (n - 1));
}
