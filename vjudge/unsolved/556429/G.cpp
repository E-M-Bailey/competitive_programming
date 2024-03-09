#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

struct lines_rollback
{
	struct ent
	{
		int m;
		ll b, s;
		friend ll isectc(ent const &a, ent const &b)
		{
			auto n = b.b - a.b;
			auto d = a.m - b.m;
			if (d <= 0)
				exit(-1);
			auto ans = n >= 0 ? (n + d - 1) / d : n / d;
			long double nn = n, dd = d, dv = nn / dd;
			dv = abs(dv - roundl(dv)) <= 1e-11l ? roundl(dv) : ceill(dv);
			if (dv != (long double)(ans))
				exit(-1);
			return ans;
		}
		ll operator()(ll x) const
		{
			return x * m + b;
		}
	};
	vector<ent> S;
	vector<vector<ent>> R;
	// add in order of decreasing slope
	void add(int m, ll b)
	{
		ent e{ m, b, LLONG_MIN };
		R.emplace_back();
		if (!S.empty())
			while ((e.s = isectc(S.back(), e)) <= S.back().s)
			{
				R.back().push_back(S.back());
				S.pop_back();
			}
		S.push_back(e);
		for (auto [m, b, s] : S)
			cerr << m << ' ' << b << ' ' << s << ' ';
		cerr << endl;
	}
	void undo()
	{
		if (S.empty() || R.empty())
			exit(-1);
		S.pop_back();
		while (!R.back().empty())
		{
			S.push_back(R.back().back());
			R.back().pop_back();
		}
		R.pop_back();
	}
	ll operator()(ll x, int m_off) const
	{
		if (S.empty())
			exit(-1);
		cerr << ' ' << x << ": " << prev(partition_point(begin(S), end(S), [x](ent const &e) { return e.s <= x; }))->m << endl;
		for (auto [m, b, s] : S)
			cerr << ' ' << m << ' ' << b << ' ' << s;
		cerr << endl;
		cerr << ' ' << (*prev(partition_point(begin(S), end(S), [x](ent const &e) { return e.s <= x; })))(x) + m_off * x << ' ';
		return (*prev(partition_point(begin(S), end(S), [x](ent const &e) { return e.s <= x; })))(x) + m_off * x;
	}
};

int main(int argc, char const *argv[])
{
	if (argc > 2)
	{
		ignore = freopen(argv[1], "r", stdin);
		ignore = freopen(argv[2], "w", stdout);
	}

#if 0
	int R = 10, C = 10;
	vector<ll> L(R, 100ll), D(C, 100ll);
	D[0] = D[C - 2] = 1;
	L[2] = 1;
#elif 1
	int R = 10, C = 10;
	vector<ll> L(R), D(C);
	//mt19937_64 randy(23598788831234);
	mt19937_64 randy(chrono::duration_cast<chrono::nanoseconds>(chrono::high_resolution_clock::now().time_since_epoch()).count());
	//geometric_distribution<ll> distr(0.01);
	uniform_int_distribution<ll> distr1(1, 500);//, distr2(1, 20);
	uniform_int_distribution<ll> &distr2 = distr1;
	for (ll &l : L)
		l = distr2(randy);
	for (ll &d : D)
		d = distr1(randy);
	sort(begin(L), end(L));
	sort(begin(D), end(D));
	for (int i = 1; i < R; i++)
		L[i] += L[i - 1];
	for (int j = 1; j < C; j++)
		D[j] += D[j - 1];
	for (auto l : L)
		cerr << l << ' ';
	cerr << endl;
	for (auto d : D)
		cerr << d << ' ';
	cerr << endl;
	vector<vector<ll>> DP(R, vector<ll>(C, LLONG_MAX));
	DP[0][0] = 0;
	for (int i = 0; i < R; i++)
		for (int j = 0; j < C; j++)
		{
			if (i)
				DP[i][j] = min(DP[i][j], DP[i - 1][j] + D[j]);
			if (j)
				DP[i][j] = min(DP[i][j], DP[i][j - 1] + L[i]);
		}

	for (int i = R - 1; i >= 0; i--)
	{
		string ln;
		for (int j = 0; j < C; j++)
		{
			char ch = j && DP[i][j] == DP[i][j - 1] + L[i] ? '-' : ' ';
			while (ln.size() % 7)
				ln += ch;
			ln += to_string(DP[i][j]);
		}
		cerr << ln << '\n';
		if (i)
		{
			for (int j = 0; j < C; j++)
				cerr << (DP[i][j] == DP[i - 1][j] + D[j] ? '|' : ' ') << "      ";
			cerr << '\n';
		}
	}

	int i = 0, j = 0;
	double lam = 1;
	string str;
	ll cst = 0;
	while (i < R - 1 || j < C - 1)
	{
		char ch;
		if (j == C - 1 || (i < R - 1 && lam * (L[i + 1] - L[i]) < D[j + 1] - D[j]))
		{
			i++;
			cst += D[j];
			ch = 'N';
		}
		else
		{
			j++;
			cst += L[i];
			ch = 'E';
		}
		str += ch;
		cerr << DP[i][j] << ' ' << cst << ' ' << ch << endl;
		cerr << ' ' << i << ' ' << j << ' ' << lam * (L[i + 1] - L[i]) << ' ' << D[j + 1] - D[j] << endl;
	}
	cerr << str << endl;
	return 0;
#else
	int R, C;
	cin >> R >> C;
	vector<ll> L(R), D(C);
	for (auto &l : L)
		cin >> l;
	for (auto &d : D)
		cin >> d;
#endif

	lines_rollback S;
	for (int i = 0; i < R; i++)
		S.add(-i, L[i]);

	int y = R - 1, x = C - 1;
	string ans;
	ll cost = 0;
	while (y > 0 || x > 0)
	{
		cerr << y << ' ' << x << endl;
		if (x > 0 && S(D[x] - D[x - 1], y) == L[y])
		{
			x--;
			cost += L[y];
			ans += 'E';
		}
		else
		{
			if (y == 0)
				exit(-1);
			y--;
			cost += D[x];
			S.undo();
			ans += 'N';
		}
		cerr << L[y] << endl;
	}

	cerr << cost;
	reverse(begin(ans), end(ans));
	cout << ans;
}

/*

struct line
{
	__int128_t m, b;
};

int main(int argc, char const *argv[])
{
	if (argc > 2)
	{
		ignore = freopen(argv[1], "r", stdin);
		ignore = freopen(argv[2], "w", stdout);
	}

	int64_t RR, CC;
	cin >> RR >> CC;
	__int128_t R = RR, C = CC;

	if (R == 1)
	{
		cout << string((int)C - 1, 'E');
		return 0;
	}
	if (C == 1)
	{
		cout << string((int)R - 1, 'N');
		return 0;
	}

	vector<__int128_t> L(R), D(C);
	for (auto &l : L)
	{
		int64_t ll;
		cin >> ll;
		l = ll;
	}
	for (auto &d : D)
	{
		int64_t dd;
		cin >> dd;
		d = dd;
	}

	//if (R >= 10 && C >= 10 && min(*min_element(begin(L), end(L)), *min_element(begin(D), end(D))) > INT_MAX)
	//	return -1;

	vector<line> ST;
	vector<vector<line>> RM(R);
	for (__int128_t i = 0; i < R; i++)
	{
		line c{ -i, L[i] };
		while (ST.size() >= 2)
		{
			auto a = ST[ST.size() - 2];
			auto b = ST[ST.size() - 1];
			if (a.m <= b.m || b.m <= c.m)
				return -1;
			//double pt1 = double(b.b - a.b) / double(a.m - b.m);
			//double pt2 = double(c.b - b.b) / double(b.m - c.m);
			if ((c.b - b.b) * (a.m - b.m) < (b.b - a.b) * (b.m - c.m))
			{
				RM[i].push_back(b);
				ST.pop_back();
			}
			else
				break;
		}
		ST.push_back(c);
		//for (auto [m, b] : ST)
		//	cerr << m << ' ' << b << ' ';
		//cerr << endl;
	}
	//cerr << endl;

	//__int128_t cost = D[0] * (R - 1);
	//cerr << cost << endl;

	string ans;
	__int128_t i = R - 1;

	for (__int128_t j = C - 1; j > 0;)
	{
		//cerr << (int)i << ' ' << (int)j << endl;
		__int128_t x = D[j] - D[j - 1];
		__int128_t lo = 0, hi = (__int128_t)ST.size() - 1;
		if (ST.empty())
			return -1;
		//cerr << (int)x << endl;
		while (lo < hi)
		{
			__int128_t mid = (lo + hi + 1) / 2;
			if (mid <= 0 || mid >= (__int128_t)ST.size())
				return -1;
			auto a = ST[mid - 1];
			auto b = ST[mid];
			if (a.m <= b.m)
				return -1;
			//double pt = double(b.b - a.b) / double(a.m - b.m);
			//if (pt < x)
			if (b.b - a.b <= x * (a.m - b.m))
				lo = mid;
			else
				hi = mid - 1;
		}
		__int128_t dc = x * (ST[lo].m + i) + ST[lo].b;
		//cerr << dc << ' ' << L[i] << endl;
		if (dc > L[i])
			return -1;
		if (dc == L[i] || i == 0)
		{
			ans += 'E';
			j--;
		}
		else
		{
			if (i < 0 || i != -ST.back().m)
				return -1;
			ST.pop_back();
			while (!RM[i].empty())
			{
				ST.push_back(RM[i].back());
				RM[i].pop_back();
			}
			ans += 'N';
			i--;
		}
		//cost += x * (ST[lo].m - 1) + ST[lo].b;
		//cerr << x << ": chose " << ST[lo].m << ' ' << ST[lo].b << endl;

		//auto tgt = ST[lo].m;
		//while (!ST.empty() && ST.back().m != tgt)
		//{
		//	i--;
		//	if (i < 0 || i != R - ST.back().m)
		//		return -1;
		//	ST.pop_back();
		//	while (!RM[i].empty())
		//	{
		//		ST.push_back(RM[i].back());
		//		RM[i].pop_back();
		//	}
		//	ans += 'N';
		//}
		//if (ST.empty())
		//{
		//	return -1;
		//}
		//for (auto [m, b] : ST)
		//	cerr << m << ' ' << b << ' ';
		//cerr << endl;
		//ans += 'E';
	}
	//cerr << cost << endl;

	if (i < 0)
		return -1;

	ans += string(i, 'N');
	reverse(begin(ans), end(ans));

	int e = 0, n = 0;
	for (char c : ans)
	{
		(c == 'E' ? e : n)++;
	}
	if (n != R - 1 || e != C - 1)
		return -1;


	cout << ans;
}*/