#include <bits/stdc++.h>

using namespace std;

int main(int argc, const char* argv[])
{
	int n;
	int64_t t;
	cin >> n >> t;

	int64_t d = 0;
	int64_t cur = 0;
	int64_t ans = 0;

	const auto adv = [&](int64_t d2, int64_t b)
	{
		int64_t amt = min(d2 - d, cur);
		//cerr << amt << endl;
		ans += amt;
		cur -= amt;
		d = d2;
		cur += b;
	};

	for (int i = 0; i < n; i++)
	{
		int64_t d2, b;
		cin >> d2 >> b;
		adv(d2, b);
	}
	adv(t + 1, 0);

	cout << ans;
}