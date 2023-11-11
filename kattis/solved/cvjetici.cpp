#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
#define sz(c) int(size(c))

struct FT
{
	vector<ll> s;
	FT(int n) : s(n) {}
	void update(int pos, ll dif)
	{
		for (; pos < sz(s); pos |= pos + 1)
			s[pos] += dif;
	}
	ll query(int pos)
	{
		ll res = 0;
		for (; pos > 0; pos &= pos - 1)
			res += s[pos - 1];
		return res;
	}
};

int main()
{
	int n;
	cin >> n;
	FT T(100002);
	while (n--)
	{
		int l, r;
		cin >> l >> r;
		auto vl = T.query(l), vr = T.query(r);
		cout << vl + vr << '\n';
		T.update(l - 1, -vl);
		T.update(l, 1 + vl);
		T.update(r - 1, -1 - vr);
		T.update(r, vr);
	}
}
