#include <bits/stdc++.h>

using namespace std;

/*
struct ent
{
	int d, q, r;
	int64_t amt(int64_t num) const
	{
		return min({ num - 1, (int64_t)q });
	}
	int64_t fin(int64_t ct) const
	{
		if (ct < q)
			return d;
		else if (ct == q)
			return r;
		else
			return 0;
	}
	friend bool operator<(ent const &a, ent const &b)
	{
		return a.d < b.d;
	}
};*/

int main(int argc, char const *argv[])
{
	if (argc > 2)
	{
		ignore = freopen(argv[1], "r", stdin);
		ignore = freopen(argv[2], "w", stdout);
	}

	int n, c;
	cin >> n >> c;

	int64_t T = 0;
	vector<tuple<int, int, int, int>> A(n);
	for (auto &[t, d, q, r] : A)
	{
		cin >> t >> d;
		auto [qq, rr] = div(t, d);
		q = qq;
		r = rr;
		T += t;
	}
	////vector<ent> A(n);
	//for (auto &[d, q, r] : A)
	//{
	//	int t;
	//	cin >> t >> d;
	//	T += t;
	//	auto const [qq, rr] = div(t, d);
	//	q = qq;
	//	r = rr;
	//}
	//sort(rbegin(A), rend(A));


	//vector<int64_t> B;

	int64_t ans;
	const auto works = [&](int64_t num)
	{
		int64_t tim = T, rem = num * c, rfin = c;
		for (auto [t, d, q, r] : A)
		{
			int64_t qc = q + (r != 0);
			int64_t amt = min((int64_t)qc, num);
			if (rem < amt)
				return false;
			rem -= amt;
			tim -= q >= num ? num * d : t;
			rfin -= amt == num;
			//cerr << ' ' << t << ' ' << d << ' ' << q << ' ' << r << ' ' << tim << ' ' << rem << ' ' << rfin << endl;
		}
		//cerr << num << ' ' << rem << ' ' << rfin << endl;
		rfin = min(rem, rfin);
		if (tim > rfin)
			return false;
		ans = num;
		return true;
	};

	int64_t lo = 1, hi = 1;
	while (!works(hi))
		hi *= 2;
	while (lo < hi)
	{
		auto mid = (lo + hi) / 2;
		if (works(mid))
			hi = mid;
		else
			lo = mid + 1;
	}

	cout << ans - 1;
}