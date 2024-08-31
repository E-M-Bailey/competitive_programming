#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
typedef long double ld;

int const M1 = 1000000007, M2 = 1000000009, M3 = 1000000607;

int const N = 9600000;

ld const S5 = sqrtl(5), PHI = (1 + S5) / 2;
ld const LS5 = log10l(S5), LPHI = log10l(PHI);

int main()
{
	tuple<int, int, int> F[N];
	ld FL[N];
	F[1] = F[0] = {1, 1, 1};
	FL[1] = FL[0] = 0;
	for (int i = 0; i + 2 < N; i++)
	{
		auto [a1, a2, a3] = F[i];
		auto [b1, b2, b3] = F[i + 1];
		F[i + 2] = {
			(a1 + b1) % M1,
			(a2 + b2) % M2,
			(a3 + b3) % M3,
		};
		FL[i + 2] = i > 30 ? (i + 3) * LPHI - LS5 : log10l(a1 + b1);
	}

	map<tuple<int, int, int>, int> J;
	
	ll ans = 0;
	int n;
	cin >> n;
	vector<string> A(n);
	for (string &a : A)
		cin >> a;
	sort(begin(A), end(A), [&](string &a, string &b)
	{
		return size(a) != size(b) ? size(a) < size(b) : a < b;
	});
	for (int i = 0; i < n; i++)
	{
		string &s = A[i];
		int a1 = 0, a2 = 0, a3 = 0;
		ld al = 0, p10 = 1;
		for (int i = 0; i < (int)size(s); i++)
		{
			int d = s[i] - '0';
			a1 = int((10ll * a1 + d) % M1);
			a2 = int((10ll * a2 + d) % M2);
			a3 = int((10ll * a3 + d) % M3);
			if (i < 20)
			{
				al += p10 * d;
				p10 /= 10;
			}
		}
		al = log10l(al) + (size(s) - 1);

		int j = int(lower_bound(begin(FL), end(FL), al) - begin(FL));
		for (int k = max(0, j - 3); k <= j + 3; k++)
		{
			auto [b1, b2, b3] = F[k];
			int c1 = (M1 + b1 - a1) % M1;
			int c2 = (M2 + b2 - a2) % M2;
			int c3 = (M3 + b3 - a3) % M3;
			ans += J[{c1, c2, c3}];
		}

		J[{a1, a2, a3}]++;
	}
	cout << ans;
}

