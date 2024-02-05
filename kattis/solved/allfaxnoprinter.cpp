#include <bits/stdc++.h>

using namespace std;

int main()
{
	cin.tie(0)->sync_with_stdio(0);
	int n, k;
	cin >> n >> k;
	map<int, int> S1, S2;
	S1[0]  = k;
	S2[0]  = k;
	int s1 = 0, s2 = 0;
	for (int i = 0; i < n; i++)
	{
		int a, b, in;
		cin >> a >> in;
		b = a + in;
		if (S1.begin()->first <= a)
		{
			if (--S1.begin()->second == 0)
				S1.erase(S1.begin());
			S1[b]++;
			s1++;
		}
		else
		{
			auto last = prev(S1.end());
			if (last->first > b)
			{
				if (--last->second == 0)
					S1.erase(last);
				S1[b]++;
			}
		}

		if (S2.begin()->first <= a)
		{
			if (--S2.begin()->second == 0)
				S2.erase(S2.begin());
			S2[b]++;
			s2++;
		}

		cout << s1 - s2 << '\n';
	}
}
