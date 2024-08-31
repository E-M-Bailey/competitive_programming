#include <bits/stdc++.h>

using namespace std;

#define rep(i, a, b) for (int i = a; i < b; i++)
#define sz(C)		 int(size(C))

template<class T>
struct RMQ
{
	vector<vector<T>> jmp;
	RMQ(const vector<T> &V) : jmp(1, V)
	{
		for (int pw = 1, k = 1; pw * 2 <= sz(V); pw *= 2, ++k)
		{
			jmp.emplace_back(sz(V) - pw * 2 + 1);
			rep(j, 0, sz(jmp[k])) jmp[k][j] = max(jmp[k - 1][j], jmp[k - 1][j + pw]);
		}
	}
	T query(int a, int b)
	{
		if (a >= b)
			return 0;
		int dep = 31 - __builtin_clz(b - a);
		return max(jmp[dep][a], jmp[dep][b - (1 << dep)]);
	}
};

int solve(int n, vector<int> const &A)
{
	vector<int> B = A;
	sort(begin(B), end(B));
	B.erase(unique(begin(B), end(B)), end(B));
	int						k = (int)size(B);
	unordered_map<int, int> CC;
	for (int i = 0; i < k; i++)
		CC[B[i]] = i;
	vector<vector<int>> I(k);
	for (int i = 0; i < n; i++)
		I[CC[A[i]]].push_back(i);

	// Bounds for a < B[i]
	vector<int> L(k + 1), R(k + 1);
	L[0] = n - 1;
	for (int i = 0; i < k; i++)
	{
		L[i + 1] = min(L[i], I[i].front());
		R[i + 1] = max(R[i], I[i].back());
	}

	int m = B.front(), M = B.back(), D = M - m;

	RMQ<int> Q(A);

	int lo = 0, hi = D;
	while (lo < hi)
	{
		int d = (lo + hi) / 2;
		int x = D - d;
		int p = M - d, q = M - x;
		// Bounds for a < B[i] <= p
		int idx = int(lower_bound(begin(B), end(B), p) - begin(B));
		int l = L[idx], r = R[idx];
		bool good = Q.query(l, r + 1) <= q;
		// cerr << "  " << d << ' ' << p << ' ' << q << ' ' << l << ' ' << r << ' ' << Q.query(l, r + 1) << endl;
		if (good)
			hi = d;
		else
			lo = d + 1;
	}
	// cerr << ' ' << lo << endl;
	return lo;
}

int main(int argc, char const *argv[])
{
	if (argc > 1)
	{
		ignore = freopen(argv[1], "r", stdin);
		ignore = freopen(argv[2], "w", stdout);
	}
	int tc;
	cin >> tc;
	while (tc--)
	{
		int n;
		cin >> n;
		vector<int> A(n);
		for (int &a : A)
			cin >> a;
		int ans = solve(n, A);
		for (int &a : A)
			a = 1000000000 - a;
		ans = min(ans, solve(n, A));
		cout << ans << '\n';
	}
}
