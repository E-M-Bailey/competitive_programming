#include <bits/stdc++.h>

using namespace std;

// RMQ with O(n) construction/memory and O(1) queries assuming n = O(2 ^ w), where w is the machine word size.
// Based on https://codeforces.com/blog/entry/78931.
template<class T>
class rmq
{
public:
	int				 m;
	vector<T>		 A;
	vector<uint64_t> M;
	vector<int>		 S;

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
	template<class It1, class It2>
	inline rmq(It1 first, It2 last) : A(first, last), M(A.size()), S(A.size())
	{
		m			  = (int)A.size() / 64;
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
			ans	  = argmin(ans, argmin(S[m * k + il], S[m * k + ir - (1 << k)]));
		}
		return ans;
	}

	inline int query(int l, int r) const
	{
		return A[argquery(l, r)];
	}
};
template<class It1, class It2>
rmq(It1, It2) -> rmq<typename iterator_traits<It1>::value_type>;

// Based on https://www.cs.helsinki.fi/u/tpkarkka/publications/icalp03.pdf.
class suffix_array
{
private:
	static int constexpr MAXN = 5'000'010;
	static int C[MAXN];
	// Stably counting-sorts A into B, where keys are given by a -> key[a * f] and are in [0, lim)
	template<int f = 1, class T>
	static inline void counting_sort(int const A[], int B[], T const key[], int n, int lim)
	{
		fill_n(C, lim, 0);
		for (int i = 0; i < n; i++)
			++C[(int)key[f * A[i]]];
		for (int i = 1; i < lim; i++)
			C[i] += C[i - 1];
		for (int i = n; i-- > 0;)
			B[--C[(int)key[f * A[i]]]] = A[i];
	}

	// Merge the suffix arrays for indices divisible, and not divisible, by 3.
	// This is similar to the merge subroutine used in merge sort.
	template<class T>
	static inline void
	merge(int n0, int n1, int n02, T const S[], int A[], int const A0[], int const S12[], int const A12[])
	{
		int i = 0, i0 = 0, i12 = n0 - n1; // i12 starts at n0 - n1 to skip the dummy suffix if it exists.
		while (i0 < n0 && i12 < n02)
		{
			int a0 = A0[i0], a12 = A12[i12];
			if (a12 < n0) // Merge suffixes 0 and 1 (mod 3)
			{
				int b0 = a0 * 3, b1 = a12 * 3 + 1, a2 = a12 + n0;
				// Compare by next character then remaining suffix.
				tuple<T, int> key0{S[b0], S12[a0]}, key1{S[b1], S12[a2]};
				if (key0 < key1) // Next suffix is a0 * 3.
				{
					A[i++] = b0;
					i0++;
				}
				else // Next suffix is b1.
				{
					A[i++] = b1;
					i12++;
				}
			}
			else // Merge suffixes 0 and 2 (mod 3)
			{
				int b0 = a0 * 3, b2 = (a12 - n0) * 3 + 2, a1 = a12 - n0 + 1;
				// Compare by next two characters then remaining suffix.
				tuple<T, T, int> key0{S[b0], S[b0 + 1], S12[a0 + n0]}, key2{S[b2], S[b2 + 1], S12[a1]};
				if (key0 < key2) // Next suffix is b0.
				{
					A[i++] = b0;
					i0++;
				}
				else // Next suffix is b2.
				{
					A[i++] = b2;
					i12++;
				}
			}
		}
		while (i0 < n0) // 1 and 2 (mod 3) suffixes are done: add remaining 0 (mod 3) suffixes.
		{
			A[i++] = 3 * A0[i0++];
		}
		while (i12 < n02) // 0 (mod 3) suffixes are done: add remaining 1 and 2 (mod 3) suffixes.
		{
			int a12 = A12[i12++];
			A[i++]	= a12 < n0 ? a12 * 3 + 1 : (a12 - n0) * 3 + 2;
		}
	}

	// Helper function for lcps which queries R12 in the correct order.
	static inline int query(rmq<int> const &R12, int const S12[], int a, int b)
	{
		a = S12[a];
		b = S12[b];
		if (a > b)
			swap(a, b);
		return R12.query(a, b);
	}

	template<class T>
	static inline void
	lcps(int n, int n0, int n02, T const S[], int const A[], int L[], int const S12[], int const L12[])
	{
		auto R12 = rmq<int>(L12, L12 + n02);
		L[0]	 = 0;
		// Compute a lower bound to lcp(i - 1, i) within 2 of the actual value by casework on A[i - 1] % 3 and A[i] % 3.
		for (int i = 1; i < n; i++)
		{
			int a = A[i - 1], b = A[i];
			int a3 = a % 3, b3 = b % 3;
			if (a3 > b3)
			{
				swap(a, b);
				swap(a3, b3);
			}
			if (a3 == 0)
			{
				if (b3 == 0) // 0, 0
					L[i] = S[a] == S[b] ? 1 + 3 * query(R12, S12, a / 3, b / 3) : 0;
				else if (b3 == 1) // 0, 1
					L[i] = S[a] == S[b] ? 1 + 3 * query(R12, S12, a / 3, b / 3 + n0) : 0;
				else // 0, 2
					L[i] = S[a] == S[b] ? S[a + 1] == S[b + 1] ? 2 + 3 * query(R12, S12, a / 3 + n0, b / 3 + 1) : 1 : 0;
			}
			else if (a3 == 1)
			{
				if (b3 == 1) // 1, 1
					L[i] = 3 * query(R12, S12, a / 3, b / 3);
				else // 1, 2
					L[i] = 3 * query(R12, S12, a / 3, b / 3 + n0);
			}
			else // 2, 2
				L[i] = 3 * query(R12, S12, a / 3 + n0, b / 3 + n0);
			// Find the correct value by comparing characters.
			while (S[a + L[i]] == S[b + L[i]])
				L[i]++;
		}
	}

	// Computes the suffix array A and LCP array L of S, which has length n and values in [1, lim), in O(n).
	// Preconditions: n >= 2 and S should be padded with three zeros at the end (i.e. s[n], s[n + 1], and s[n + 2]
	// should be zero.)
	template<class T>
	static inline void suffix_array_impl(T const S[], int A[], int L[], int n, int lim)
	{
		// number of 0's, 1's, 2's, and 0's + 2's mod 3 in [0, n).
		int n0 = (n + 2) / 3, n1 = (n + 1) / 3, n2 = n / 3, n02 = n0 + n2;
		int S12[n02 + 3], A12[n02 + 3], L12[n02 + 3], S0[n0], A0[n0];
		S12[n02] = S12[n02 + 1] = S12[n02 + 2] = A12[n02] = A12[n02 + 1] = A12[n02 + 2] = 0;

		// Put indices not divisible by 3 in S12.
		// If n % 3 == 1, also add a dummy value at the end (hence the + n0 - n1).
		for (int i = 1, j = 0; i < n + n0 - n1;)
		{
			S12[j++] = i;
			i++;
			if (i >= n + n0 - n1)
				break;
			S12[j++] = i;
			i += 2;
		}

		// Radix-sort each index i != 0 mod 3 by the tuple (S[i], S[i + 1], S[i + 2])
		counting_sort<1>(S12, A12, S + 2, n02, lim);
		counting_sort<1>(A12, S12, S + 1, n02, lim);
		counting_sort<1>(S12, A12, S, n02, lim);

		// Rank these indices by (S[i], S[i + 1], S[i + 2]), accounting for ties.
		// S12 is partitioned into these ranks for 1 (mod 3) indices on the left and for 2 (mod 3) indices on the right.
		int	 lim2 = 0;
		auto tup  = make_tuple(-1, -1, -1);
		for (int i = 0; i < n02; i++)
		{
			auto tup2									 = make_tuple(S[A12[i]], S[A12[i] + 1], S[A12[i] + 2]);
			S12[A12[i] / 3 + (A12[i] % 3 == 1 ? 0 : n0)] = lim2 += tup2 != tup;
			tup											 = tup2;
		}

		// Compute the ranks and the suffix array for indices not divisible by 3.
		// After this, S12 stores the unique ranks, i.e. the inverse suffix array.

		// If ranks are not unique (there are ties), recursively generate the suffix array and update the ranks.
		if (lim2 < n02)
		{
			suffix_array_impl<int>(S12, A12, L12, n02, lim2 + 1);
			for (int i = 0; i < n02; i++)
				S12[A12[i]] = i + 1;
		}
		// Otherwise, directly generate the suffix array by inverting S12.
		else
			for (int i = 0; i < n02; i++)
			{
				A12[S12[i] - 1] = i;
				L12[i]			= 0;
			}

		// Generate suffix array for indices divisible by 0:
		// First, generate the array of their indices sorted by S[i+1...]
		for (int i = 0, j = 0; i < n02; i++)
			if (A12[i] < n0)
				S0[j++] = A12[i];
		// Then, stably sort this list by S[i].
		// Now, the array is sorted lexicographically by the pair (S[i], S[i+1...]), i.e. by S[i...]
		counting_sort<3>(S0, A0, S, n0, lim);

		merge(n0, n1, n02, S, A, A0, S12, A12);
		lcps(n, n0, n02, S, A, L, S12, L12);
	}

public:
	// suffix array, inverse suffix array, lcp array
	vector<int> A, B, L;

	// O(distance(first, last) + *max_element(first, last)) time and memory
	template<class It>
	inline suffix_array(It first, It last)
	{
		typedef typename iterator_traits<It>::value_type T;
		int												 n;
		{
			vector<T> S;
			T		  lim = 0;
			S.insert(S.end(), first, last);
			for (auto &s : S)
				lim = max(lim, ++s);
			n = (int)S.size();
			S.resize(n + 3);
			A.resize(n);
			L.resize(n);
			if (n >= 2)
				suffix_array_impl<T>(S.data(), A.data(), L.data(), n, lim + 1);
		}

		B.resize(n);
		for (int i = 0; i < n; i++)
			B[A[i]] = i;
	}
};
int suffix_array::C[suffix_array::MAXN];

char str[50'000'001];
int	 main()
{
	vector<int> ans;
	ans.reserve(5'000'000);

	read(STDIN_FILENO, str, 5'000'000);

	for (int a = 0, b, c; str[a]; a = c + 1)
	{
		b = a;
		while (str[b] != '\n')
			b++;
		c = b + 1;
		while (str[c] != '\n')
			c++;

		ans.clear();
		auto [A, B, L] = suffix_array(str + a, str + c);
		int p_len	   = b - a;

		for (int i = B[0]; L[i--] >= p_len;)
			ans.push_back(A[i] - (p_len + 1));
		for (int i = B[0]; ++i < c - a && L[i] >= p_len;)
			ans.push_back(A[i] - (p_len + 1));

		sort(begin(ans), end(ans));
		for (int x : ans)
			cout << x << ' ';
		cout << '\n';
	}
}
