#include <bits/stdc++.h>

using namespace std;

#define sz(C)  (int(size(C)))
#define all(C) begin(C), end(C)

void go();

int main(int argc, char const *argv[])
{
	if (argc > 1)
	{
		ignore = freopen(argv[1], "r", stdin);
		ignore = freopen(argv[2], "w", stdout);
	}
	cin.tie(0)->sync_with_stdio(0);

	int tc = 1;
	cin >> tc;
	while (tc--)
		go();
}

typedef vector<int> vi;

// from KACTL
vi zfunc(const string &S)
{
	vi	z(sz(S));
	int l = -1, r = -1;
	for (int i = 1; i < sz(S); i++)
	{
		z[i] = i >= r ? 0 : min(r - i, z[i - l]);
		while (i + z[i] < sz(S) && S[i + z[i]] == S[z[i]])
			z[i]++;
		if (i + z[i] > r)
			l = i, r = i + z[i];
	}
	return z;
}

long long f(long long a, long long b, long long c)
{
	if (a > b)
		swap(a, b);
	a			= min(a, c);
	b			= min(b, c);
	c			= min(c, a + b);
	long long x = a + b - c;
	return (a + 1) * (b + 1) - x * (x + 1) / 2;
}

void go()
{
	string s;
	cin >> s;
	int n = sz(s);

	string		t;
	vector<int> I;
	for (int i = 0; i < n; i++)
		if (s[i] != 'a')
		{
			t.push_back(s[i]);
			I.push_back(i);
		}

	int m = sz(t);
	if (!m)
	{
		cout << n - 1 << '\n';
		return;
	}
	// else if (m == 1)
	// {
	// 	int a = I[0], b = n - 1 - I[0];
	// 	cout << f(a, b, 0) << '\n';
	// 	return;
	// }

	vector<int> Z = zfunc(t);
	int			p = -1;
	for (int i = 1; i < m; i++)
		if (Z[i] + i == m)
		{
			p = i;
			break;
		}
	if (p < 0)
		p = m;

	int					   k = m / p;
	vector<pair<int, int>> J(k);
	vector<int>			   C(k + 1);
	int					   pr = 0;
	for (int i = 0; i < k; i++)
	{
		J[i].first	= I[p * i];
		J[i].second = I[p * (i + 1) - 1] + 1;
		C[i]		= J[i].first - pr;
		pr			= J[i].second;
	}
	C[k] = n - pr;

	long long ans = 0;
	for (int l = 1; l <= k; l++)
	{
		int L = l * p;
		if (m % L)
			continue;
		int	   a = C[0], b = C[k], c = 2 * n;
		int	   i1 = J[0].first, j1 = J[l - 1].second;
		string u	= s.substr(i1, j1 - i1);
		bool   good = true;
		for (int i = l; good && i < k; i += l)
		{
			int	   i2 = J[i].first, j2 = J[i + l - 1].second;
			string v = s.substr(i2, j2 - i2);
			good &= u == v;
			c = min(c, C[i]);
		}
		if (good)
			ans += f(a, b, c);
	}
	cout << ans << '\n';
}
