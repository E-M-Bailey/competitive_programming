#include <bits/stdc++.h>

using namespace std;

int ds(int n)
{
	int ans = 0;
	for (; n; n /= 10)
		ans += (n % 10) * (n % 10);
	return ans;
}

int main()
{
	vector<bool> C(10001);
	C[0] = C[1] = true;
	for (int i = 2; i <= 10000; i++)
	{
		if (C[i]) continue;
		for (int j = i * 2; j <= 10000; j += i)
			C[j] = true;
	}

	vector<int> ST, H(10001, -1);
	vector<bool> OS(10001);
	for (int i = 0; i <= 10000; i++)
		if (C[i])
			H[i] = 0;
	for (int i = 0; i <= 10000; i++)
	{
		bool ans;
		for (int j = i;; j = ds(j))
		{
			if (OS[j])
			{
				ans = true;
				break;
			}
			ST.push_back(j);
			OS[j] = true;
			if (H[j] >= 0)
			{
				ans = H[j];
				break;
			}
		}
		for (int k : ST)
		{
			OS[k] = false;
			H[k] = ans;
		}
		ST.clear();
	}

	int T;
	cin >> T;
	for (int i = 1; i <= T; i++)
	{
		int k, m;
		cin >> k >> m;
		cout << k << ' ' << m << ' ' << (H[m] ? "YES\n" : "NO\n");
	}
}