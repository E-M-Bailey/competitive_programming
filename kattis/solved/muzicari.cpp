#include <bits/stdc++.h>

using namespace std;

int main()
{
	cin.tie(0)->sync_with_stdio(0);
	int t, n;
	cin >> t >> n;
	vector<bitset<5056>> S(n + 1);
	S[n][0] = true;
	vector<int> A(n);
	for (int &a : A)
		cin >> a;
	for (int i = n; i > 0; i--)
	{
		S[i - 1] |= S[i] | S[i] << A[i - 1];
	}
	while (!S[0][t])
		t--;
	int x = 0, y = 0;
	for (int i = 0; i < n; i++)
	{
		int a = A[i];
		if (a <= t && S[i + 1][t - a])
		{
			cout << x << ' ';
			x += a;
			t -= a;
		}
		else
		{
			cout << y << ' ';
			y += a;
		}
	}
}
