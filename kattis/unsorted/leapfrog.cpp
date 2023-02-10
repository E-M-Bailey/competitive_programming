#include <bits/stdc++.h>

using namespace std;

int64_t euclid(int64_t a, int64_t b, int64_t& x, int64_t& y)
{
	if (!b) return x = 1, y = 0, a;
	int64_t d = euclid(b, a % b, y, x);
	return y -= a / b * x, d;

}

int64_t crt(int64_t a, int64_t m, int64_t b, int64_t n)
{
	if (n > m) swap(a, b), swap(m, n);
	int64_t x, y, g = euclid(m, n, x, y);
	x = (b - a) % n * x % n / g * m + a;
	return x < 0 ? x + m * n / g : x;
}

int main(int argc, const char* argv[])
{
	if (argc > 1)
	{
		ignore = freopen(argv[1], "r", stdin);
		ignore = freopen(argv[2], "w", stdout);
	}

	int n;
	cin >> n;
	vector<int64_t> X(n), D(n);
	int64_t maxp = 0;
	unordered_map<int64_t, int> I;
	vector<int64_t> P;
	for (int i = 0; i < n; i++)
	{
		cin >> X[i] >> D[i];
		maxp = max(maxp, D[i]);
		if (I.try_emplace(D[i], size(I)).second)
			P.push_back(D[i]);
	}
	int m = size(I);

	vector<vector<int64_t>> M(m);
	vector<vector<int64_t>> S(m);
	int  bestH = 0;

	for (int i = 0; i < m; i++)
	{
		int64_t p = P[i];
		unordered_map<int64_t, int> F;
		unordered_map<int64_t, int64_t> SP;
		int maxf = 0;
		for (int j = 0; j < n; j++)
			if (D[j] == p)
			{
				int64_t mod = X[j] % p;
				maxf = max(maxf, ++F[mod]);
				SP[mod] = max(SP[mod], X[j]);
			}
		for (auto [mod, f] : F)
			if (f == maxf)
			{
				M[i].push_back(mod);
				S[i].push_back(SP[mod]);
			}
		bestH += maxf;
	}

	vector<int> IDX(m);

	const auto incr = [m, &IDX, &M]()
	{
		for (int i = 0; i < m; i++)
		{
			if (++IDX[i] < size(M[i]))
				return true;
			IDX[i] = 0;
		}
		return false;
	};

	int64_t bestS = numeric_limits<int64_t>::max();

	//cerr << M[1][0] << ' ' << S[1][0] << endl;

	do
	{
		int64_t x = M[0][IDX[0]], s = S[0][IDX[0]], pp = P[0];
		for (int i = 1; i < m; i++)
		{
			x = crt(x, pp, M[i][IDX[i]], P[i]);
			pp *= P[i];
			s = max(s, S[i][IDX[i]]);
		}
		int64_t sp = s;
		sp -= sp % pp;
		sp += x;
		if (sp < s)
			sp += pp;
		//cerr << sp << endl;
		bestS = min(bestS, sp);
	} while (incr());

	cout << bestS << ' ' << bestH;

}