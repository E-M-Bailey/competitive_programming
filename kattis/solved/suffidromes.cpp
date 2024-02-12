#include <bits/stdc++.h>

using namespace std;

constexpr int64_t MOD = 1000000009, X = 29, IX = 517241384;

int64_t xpow(int e)
{
	static vector<int> P{1}, N{IX};
	if (e >= 0)
	{
		while (e >= (int)size(P))
			P.push_back(int(P.back() * X % MOD));
		return P[e];
	}
	else
	{
		while (~e >= (int)size(N))
			N.push_back(int(N.back() * IX % MOD));
		return N[~e];
	}
}

struct shash
{
	int hf = 0, hb = 0, l = 0;
	shash() = default;
	explicit shash(int a) : hf(a), hb(a), l(1) {}
	shash(int HF, int HB, int L) : hf(HF), hb(HB), l(L) {}
};

bool operator==(shash a, shash b)
{
	return a.hf == b.hf && a.hb == b.hb && a.l == b.l;
}
shash operator+(shash a, shash b)
{
	int64_t hf = a.hf + b.hf * xpow(a.l);
	int64_t hb = b.hb + a.hb * xpow(b.l);
	hf %= MOD;
	hb %= MOD;
	return {(int)hf, (int)hb, a.l + b.l};
}
shash operator-(shash a, shash b)
{
	int64_t hf = a.hf - b.hf * xpow(a.l - b.l);
	int64_t hb = (a.hb - b.hb) * xpow(-b.l);
	if ((hf %= MOD) < 0)
		hf += MOD;
	if ((hb %= MOD) < 0)
		hb += MOD;
	return {(int)hf, (int)hb, a.l - b.l};
}
shash rev(shash a)
{
	return {a.hb, a.hf, a.l};
}

struct hashes
{
	int			  n = 0;
	vector<shash> S{{}};
	template<class It>
	hashes(It first, It last)
	{
		while (last != first)
			S.push_back(shash{*--last} + S.back());
		reverse(begin(S), end(S));
		n = (int)size(S) - 1;
	}
	shash operator()(int l, int r = INT_MAX) const
	{
		return S[l] - S[min(r, n)];
	}
	// suf.l <= this->n
	// or suf.l == this->n + 1 and fst is the first elem in rev(rsuf)
	bool is_pal(shash rsuf, int fst) const
	{
		if (rsuf.l > n)
			return (rsuf - shash{fst}) == S[0];
		int l = n + rsuf.l;
		return (*this)(0, l / 2) == rsuf + rev((*this)((l + 1) / 2));
	}
};

int main()
{
	cin.tie(0)->sync_with_stdio(0);
	string		a, b;
	vector<int> A, B;
	while (getline(getline(cin, a), b))
	{
		if (a == b)
		{
			cout << "No solution.\n";
			continue;
		}
		A.resize(size(a));
		B.resize(size(b));
		int n = (int)size(a), m = (int)size(b);
		for (int i = 0; i < n; i++)
			A[i] = a[i] - 'a';
		for (int i = 0; i < m; i++)
			B[i] = b[i] - 'a';

		hashes const P(begin(A), end(A)), Q(begin(B), end(B));

		set<string> ans;
		for (int l = 0; ans.empty() && l <= m + 1 && l <= n + 1; l++)
		{
			auto ah = P(0, min(l, n)), bh = Q(0, min(l, m));
			ah		 = l <= n ? ah : ah + shash{n < m && B[n] == 0};
			bh		 = l <= m ? bh : bh + shash{m < n && A[m] == 0};
			int afst = l <= n ? l == 0 ? -1 : A[l - 1] : n < m && B[n] == 0;
			int bfst = l <= m ? l == 0 ? -1 : B[l - 1] : m < n && A[m] == 0;
			if (P.is_pal(ah, afst) && !Q.is_pal(ah, afst))
			{
				string s = a.substr(0, min(l, n));
				if (l > n)
					s += n < m && B[n] == 0 ? 'b' : 'a';
				reverse(begin(s), end(s));
				ans.insert(s);
			}
			if (Q.is_pal(bh, bfst) && !P.is_pal(bh, bfst))
			{
				string s = b.substr(0, min(l, m));
				if (l > m)
					s += m < n && A[m] == 0 ? 'b' : 'a';
				reverse(begin(s), end(s));
				ans.insert(s);
			}
		}
		cout << *begin(ans) << '\n';
	}
}
