#include <bits/stdc++.h>

using namespace std;

void go();

int main()
{
	cin.tie(0)->sync_with_stdio(0);
	int tc = 1;
	cin >> tc;
	while (tc--)
		go();
}

typedef long long ll;

void go()
{
	int m;
	ll	x;
	cin >> m >> x;
	vector<ll>	C(m);
	vector<int> H(m);
	for (int i = 0; i < m; i++)
	{
		cin >> C[i] >> H[i];
	}
	int		   k = accumulate(begin(H), end(H), 0);
	vector<ll> M(k + 1, LLONG_MIN / 2);
	M[0]	= 0;
	int ans = 0;
	for (int i = 0; i < m; i++)
	{
		for (int j = k; j >= H[i]; j--)
			if ((M[j] = max(M[j], M[j - H[i]] - C[i])) >= 0)
				ans = max(ans, j);
		for (int j = 0; j <= k; j++)
			if (M[j] >= 0)
				M[j] += x;
	}
	cout << ans << '\n';
}
