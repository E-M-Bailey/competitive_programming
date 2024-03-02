#include <bits/stdc++.h>

using namespace std;

struct frac
{
	int n, d;

	friend bool operator==(frac l, frac r)
	{
		return l.n * r.d == r.n * l.d;
	}
	friend bool operator<(frac l, frac r)
	{
		return l.n * r.d < r.n * l.d;
	}
	friend frac operator*(frac l, frac r)
	{
		return {l.n * r.n, l.d * r.d};
	}
	friend frac operator/(frac l, frac r)
	{
		return {l.n * r.d, l.d * r.n};
	}
	friend frac red(frac f)
	{
		int g = gcd(f.n, f.d);
		return {f.n / g, f.d / g};
	}

	friend istream &operator>>(istream &is, frac &f)
	{
		static string str;
		is >> str;
		auto pos = str.find('/');
		f.n		 = stoi(str.substr(0, pos));
		f.d		 = stoi(str.substr(pos + 1));
		return is;
	}
};

int main()
{
	frac F[12];
	for (frac &f : F)
		cin >> f;
	sort(begin(F), end(F));
	vector<frac> K;

	for (int i = 1; i <= 6; i++)
	{
		K.clear();
		frac	  fac = red(F[i] / F[0]);
		set<frac> S;
		int l = 1;
		for (frac f : F)
		{
			auto it = S.find(f);
			if (it != end(S))
				S.erase(it);
			else
			{
				K.push_back(red(frac{fac.d * f.d, f.n}));
				l = lcm(l, K.back().d);
				S.insert(red(f * fac));
			}
		}
		if (!S.empty())
			continue;

		cout << fac.n * l << ' ' << fac.d * l << '\n';
		for (auto [n, d] : K)
			cout << l / d * n << ' ';
		return 0;
	}
	cout << "impossible";
}
