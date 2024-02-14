#include <bits/stdc++.h>

using namespace std;

constexpr int64_t P1 = 1000000007, A1 = 29, I1 = 758620695, P2 = 1000000009, A2 = 31, I2 = 838709685;

int main()
{
	cin.tie(0)->sync_with_stdio(0);
	int	   l;
	string S;
	cin >> l >> S;

	int lo = 0, hi = l;

	unordered_set<int64_t> H;
	while (hi - lo > 1)
	{
		int		k  = (hi + lo) / 2;
		int64_t h1 = 0, h2 = 0;
		int64_t b1 = 1, b2 = 1;
		for (int i = 0; i < k; i++)
		{
			if (i)
			{
				b1 = b1 * A1 % P1;
				b2 = b2 * A2 % P2;
			}
			h1 = (h1 + b1 * (S[i] - 'a')) % P1;
			h2 = (h2 + b2 * (S[i] - 'a')) % P2;
		}
		H.insert((h1 << 32) | h2);
		bool uniq = true;
		for (int i = k; uniq && i < l; i++)
		{
			h1 = (I1 * (h1 + P1 - S[i - k] + 'a') + b1 * (S[i] - 'a')) % P1;
			h2 = (I2 * (h2 + P2 - S[i - k] + 'a') + b2 * (S[i] - 'a')) % P2;
			uniq &= H.insert((h1 << 32) | h2).second;
		}
		(uniq ? hi : lo) = k;
		H.clear();
	}
	cout << lo;
}
