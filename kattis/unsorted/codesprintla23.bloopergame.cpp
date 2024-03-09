#include <bits/stdc++.h>

using namespace std;

typedef long double T;

int main(int argc, char const *argv[])
{
	if (argc > 2)
	{
		ignore = freopen(argv[1], "r", stdin);
		ignore = freopen(argv[2], "w", stdout);
	}

	int n, l;
	T p;
	cin >> n >> l >> p;
	p = -log(p);
	vector<T> X(n);
	for (auto &x : X)
		cin >> x;


	sort(rbegin(X), rend(X));
	while (!X.empty() && X.back() == 1)
	{
		X.pop_back();
		n--;
	}
	if (X.empty())
	{
		cout << 1;
		return 0;
	}
	for (auto &x : X)
		x = log(log(x)) / p;


	int lo = 0, hi = n - 1;
	while (lo < hi)
	{
		int mid = (lo + hi + 1) / 2;
		int64_t cost = 0;
		for (int i = 0; i < mid; i++)
			cost += int64_t(X[i] - X[mid]);
		if (cost > l)
			hi = mid - 1;
		else
			lo = mid;
	}
	for (int i = 0; i < lo; i++)
	{
		int ct = int(X[i] - X[lo]);
		X[i] -= ct;
		l -= ct;
	}
	int ct_all = l / (lo + 1);
	for (int i = 0; i <= lo; i++)
	{
		X[i] -= ct_all;
		l -= ct_all;
	}
	sort(rbegin(X), rend(X));
	for (int i = 0; i < l; i++)
		X[i] -= 1;

	T ans = 1;
	for (T x : X)
		ans *= exp(-exp(x * p));

	cout << fixed << setprecision(7) << ans;
	//for (auto x : X)
	//	cerr << exp(-exp(x * p)) << ' ';
	//cerr << endl;
	//for (auto x : X)
	//	cerr << exp(-exp(x * p)) << ' ';
	//cerr << endl;

	/*
		multiset<long double> M;
		int n, l;
		cin >> n >> l;
		long double p;
		cin >> p;
		//p = log(p);
		for (int i = 0; i < n; i++)
		{
			long double x;
			cin >> x;
			//M.insert(log(log(x)));
			M.insert(log(x));
		}
		decltype(M)::iterator it1, it2;
		while (l && *(it1 = begin(M)) / *(it2 = prev(end(M))) < p + 1e-9)
		{
			M.insert(*it2 + p);
			M.erase(it2);
			l--;
		}

		auto amt = l / n;
		vector<long double> MV(begin(M), end(M));
		M.clear();
		for (auto x : MV)
			M.insert(x + amt * p);
		l %= n;
		while (l)
		{
			it2 = prev(end(M));
			M.insert(*it2 + p);
			M.erase(it2);
			l--;
		}

		long double ans = 1;
		for (auto x : M)
		{
			//cerr << exp(-exp(x)) << endl;
			ans *= exp(-exp(x));
		}
		cout << fixed << setprecision(7) << ans;
		*/
}
