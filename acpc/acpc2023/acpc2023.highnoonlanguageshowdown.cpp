#include <bits/stdc++.h>

using namespace std;

int main()
{
	int64_t N, k;
	cin >> N >> k;
	bool good = false;
	for (int64_t n = 1; n <= N; n++)
	{
		int64_t lg = 64 - __builtin_clzll(n);
		good |= n >= k * lg;
	}
	cout << (good ? "Good to go!" : "Tweak the bounds!");
}