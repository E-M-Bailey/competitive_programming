#pragma GCC optimize("O3")

#include <bits/stdc++.h>

using namespace std;

int constexpr MAXN = 100'010;

int C[MAXN];
// Stably counting-sorts A into B, where keys are given by key[a * f] and are in [0, lim)
template<int f = 1, typename T>
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

// Computes the suffix array A and LCP array L of S, which has length n and values in [1, lim), in O(n).
// Heavily based on https://www.cs.helsinki.fi/u/tpkarkka/publications/icalp03.pdf.
// Preconditions: n >= 2 and S should be padded with three zeros at the end (i.e. s[n], s[n + 1], and s[n + 2] should be
// zero.)
template<typename T>
static inline void suffix_array_helper(T const S[], int A[], int n, int lim)
{
	// number of 0's, 1's, 2's, and 0's + 2's mod 3 in [0, n).
	int n0 = (n + 2) / 3, n1 = (n + 1) / 3, n2 = n / 3, n02 = n0 + n2;
	int S12[n02 + 3], A12[n02 + 3], S0[n0], A0[n0];
	S12[n02] = S12[n02 + 1] = S12[n02 + 2] = A12[n02] = A12[n02 + 1] = A12[n02 + 2] = 0;

	// Put indices not divisible by 3 in S12.
	// If n % 3 == 1, also add a dummy value at the end (hence the + (n0 - n1)).
	for (int i = 1, j = 0; i < n + (n0 - n1);)
	{
		S12[j++] = i;
		i++;
		if (i >= n + (n0 - n1))
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

	// Finalize the ranks and the suffix array for indices not divisible by 3.
	// If ranks are not unique (there are ties), recursively generate the suffix array and update the ranks.
	if (lim2 < n02)
	{
		suffix_array_helper(S12, A12, n02, lim2 + 1);
		for (int i = 0; i < n02; i++)
			S12[A12[i]] = i + 1;
	}
	// Otherwise, directly generate the suffix array.
	else
	{
		for (int i = 0; i < n02; i++)
			A12[S12[i] - 1] = i;
	}

	// Generate suffix array for indices divisible by 0:
	// First, generate the array of their indices sorted by S[i+1...]
	for (int i = 0, j = 0; i < n02; i++)
		if (A12[i] < n0)
			S0[j++] = A12[i];
	// Then, stably sort this list by S[i].
	// Now, the array is sorted lexicographically by the pair (S[i], S[i+1...]), i.e. by S[i...]
	counting_sort<3>(S0, A0, S, n0, lim);

	// Merge the suffix arrays for indices divisible, and not divisible, by 3.
	// This is similar to the merge subroutine of merge sort.
	for (int p = 0, t = n0 - n1, k = 0; k < n; k++)
	{
		int	 a	= A12[t];
		bool a1 = a < n0; // Whether a = A12[t] refers to a 1 (mod 3) or to a 2 (mod 3) suffix (true means 1 (mod 3))
		int	 i0 = A0[p], i03 = i0 * 3, i12 = a1 ? a * 3 + 1 : (a - n0) * 3 + 2;
		if (a1 ? make_tuple(S[i12], S12[A12[t] + n0]) <=
					 make_tuple(S[i03], S12[i0]) // Comparison for indices = 1 (mod 3) and ...
			   : make_tuple(S[i12], S[i12 + 1], S12[A12[t] - n0 + 1]) <=
					 make_tuple(S[i03], S[i03 + 1], S12[i0 + n0])) // for 2 (mod 3).
																   // Next suffix is 1 or 2 (mod 3).
		{
			A[k] = i12;
			if (++t == n02) // Done with 1 and 2 (mod 3) suffixes, fill in the rest of the 0 (mod 3) suffixes.
				for (k++; p < n0; k++, p++)
					A[k] = 3 * A0[p];
		}
		else
		// Next suffix is 0 (mod 3).
		{
			A[k] = i03;
			if (++p == n0) // Done with 0 (mod 3) suffixes, fill in the rest of the 1 and 2 (mod 3) suffixes.
				for (k++; t < n02; k++, t++)
				{
					a	 = A12[t];
					a1	 = a < n0;
					A[k] = a1 ? a * 3 + 1 : (a - n0) * 3 + 2;
				}
		}
	}
}

vector<int> suffix_array(string const &S)
{
	int			 n = (int)S.size();
	vector<char> S2(begin(S), end(S));
	S2.resize(n + 3);
	auto ans = vector<int>(n);
	if (n >= 2)
		suffix_array_helper(S2.data(), ans.data(), n, 256);
	return ans;
}

int main()
{
	cin.tie(0);
	ios_base::sync_with_stdio(0);

	string str;
	while (getline(cin, str))
	{
		auto A = suffix_array(str);
		int	 q;
		cin >> q;
		while (q--)
		{
			int i;
			cin >> i;
			cout << A[i] << ' ';
		}
		cout << '\n';
		getline(cin, str);
	}
}
