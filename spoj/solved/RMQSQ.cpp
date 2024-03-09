#include <bits/stdc++.h>

using namespace std;

// Based on https://codeforces.com/blog/entry/78931.
template<typename T>
class rmq
{
public:
	int m;
	vector<T> A;
	vector<uint64_t> M;
	vector<int> S;

private:
	inline int argmin(int i, int j) const
	{
		return A[i] < A[j] ? i : j;
	}

	// queries [l, l + 64)
	inline int argquery_64(int l) const
	{
		return l + 63 - __builtin_clzll(M[l]);
	}

	// queries [l, l + s) for s < 64
	inline int argquery_small(int l, int s) const
	{
		return l + 63 - __builtin_clzll(M[l] & (((uint64_t)1 << s) - 1));
	}

public:
	template<typename It>
	inline rmq(It first, It last) : A(first, last), M(A.size()), S(A.size())
	{
		m = (int)A.size() / 64;
		uint64_t mask = 0;
		for (int i = (int)A.size(); i-- > 0; mask <<= 1)
		{
			while (mask && A[i] < A[i + __builtin_ctzll(mask & -mask)])
				mask &= mask - 1;
			M[i] = mask |= 1;
		}
		for (int i = 0; i < m; i++)
			S[i] = argquery_64(64 * i);
		for (int k = 0, s = 1; s * 2 <= m; k++, s *= 2)
			for (int i = 0; i + s * 2 <= m; i++)
				S[m * (k + 1) + i] = argmin(S[m * k + i], S[m * k + i + s]);
	}

	inline int argquery(int l, int r) const
	{
		if (r - l < 64)
			return argquery_small(l, r - l);
		int ans = argmin(argquery_64(l), argquery_64(r - 64));
		int il = (l + 63) / 64, ir = r / 64;
		if (il < ir)
		{
			int k = 31 - __builtin_clz(ir - il);
			ans = argmin(ans, argmin(S[m * k + il], S[m * k + ir - (1 << k)]));
		}
		return ans;
	}

	inline int query(int l, int r) const
	{
		return A[argquery(l, r)];
	}
};

int main()
{
	cin.tie(0);
	ios_base::sync_with_stdio(0);

	int n;
	cin >> n;
	int A[n];
	for (int i = 0; i < n; i++)
		cin >> A[i];
	rmq<int> R(A, A + n);

	int q;
	cin >> q;
	for (int i = 0; i < q; i++)
	{
		int l, r;
		cin >> l >> r;
		cout << R.query(l, r + 1) << '\n';
	}
}
