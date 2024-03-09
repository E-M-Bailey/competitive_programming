#include <bits/stdc++.h>

using namespace std;

typedef long double T;

struct hill
{
	T a, b, d, s, e, a0, a1, a2;
	hill(T A, T B) : a(A), b(B)
	{
		d = sqrt(b);
		s = a - d;
		e = a + d;
		a2 = -1;
		a1 = 2 * a;
		a0 = b - a * a;
	}
};

int main()
{
	int n;
	cin >> n;

	vector<tuple<T, int, T, T, T>> E;
	E.reserve(2 * n);
	//E.emplace_back(0, 0, 0, 0, 0);

	for (int i = 0; i < n; i++)
	{
		int a, b;
		cin >> a >> b;
		hill h(a, b);
		E.emplace_back(h.s, 1, h.a0, h.a1, h.a2);
		E.emplace_back(h.e, -1, -h.a0, -h.a1, -h.a2);
	}

	sort(begin(E), end(E));
	int ct = 0;
	T t = 0, a0 = 0, a1 = 0, a2 = 0;
	T ans = 0;

	for (auto [u, dct, da0, da1, da2] : E)
	{
		if (ct > 1)
			ans += u * (a0 + u * (a1 / 2 + u * (a2 / 3))) - t * (a0 + t * (a1 / 2 + t * (a2 / 3)));
		ct += dct;
		a0 += da0;
		a1 += da1;
		a2 += da2;
		t = u;
	}

	cout << fixed << setprecision(6) << ans;
}