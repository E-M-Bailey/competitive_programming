/*
BEGIN ANNOTATION
PROBLEM URL: https://open.kattis.com/problems/satisfaction
TAGS: recursion, recursive descent, parsing, string, string parsing, ast, abstract syntax tree, bitset, constant factor, optimization, SIMD
EXPLANATION:
We can parse the programming language using recursive descent. Then, we can solve the problem by recursing on the
resulting abstract syntax tree.

Let k <= 20 be the number of variables which occur in the program. Let run(l, A) be a function which interprets the
statement list l. A is the set of variable assignments that can reach this part of the program, represented by a bitset
of size 2^k.
For each statement s in l:
	if s is "checkpoint":
		if A is empty, print "unreachable".
		otherwise:
			for each variable v in alphabetical order:
				let V be the set of assignments where v is true and ~V be the set where v is false.
				if ~V and A are disjoint, print v uppercase since it must be true.
				otherwise, if V and A are disjoint, print v lowercase since it must be false.
	otherwise, s is an "if" statement:
		recursively compute the set B of assignments satisfying s's condition.
		let l_1 be the statement list inside the condition.
		run(l_1, A & B), since an assignment must satisfy B to get inside the "if" statement.
		if s has an "else" clause:
			let l_2 be the statement list inside the clause.
			run(l_2, A & ~B), since an assignment must not satisfy B to get inside the "else" clause.

To parse a boolean expression, taking precedence into account, use this grammer:
	S -> A "|" S
	A -> B "&" A
	B -> "~" B + C
	C -> "(" S ")" + <variable>

Using a bitset is already sufficient to pass under time and memory constraints, but some extra constant-factor
optimizations are possible:

 - Solve the problem as you parse it instead of constructing the abstract syntax tree. This also simplifies the
   implementation considerably.

 - To reduce recursion and bitset operations, replace the boolean expression grammer with:
	   S -> A ("|" A)*
	   A -> B ("&" B)*
	   B -> "~"* ("(" S ")" + <variable>)
   This allows you to ignore consecutive pairs of ~'s (double negation).

 - Accelerate bitset operations with SIMD instructions.

 - Make k a template parameter for better constant folding.

 - Avoid unnecessary copying of bitsets.

END ANNOTATION
*/

#pragma GCC optimize("Ofast,no-stack-protector,unroll-loops")
#pragma GCC target("sse,sse2,sse3,ssse3,sse4,sse4.1,sse4.2,popcnt,abm,mmx,avx,avx2,fma")
#ifndef GODBOLT
#pragma GCC target("tune=native")
#endif

#include <bits/stdc++.h>
#include <immintrin.h>
#include <nmmintrin.h>

using namespace std;

// number of variables
int k = 0;

// variable name -> id
int ids[91];

// variable id -> name
char vars[20];

vector<string> tokens;

// This section is an implementation of bitset operations using SIMD instructions. You can skip to line 154
// without missing anything important.

// Lookup table for single bits
alignas(256) uint64_t const BITS[256 * 4]{ 0, 0, 0, 0x0000000000000001ll, 0, 0, 0, 0x0000000000000002ll, 0, 0, 0, 0x0000000000000004ll, 0, 0, 0, 0x0000000000000008ll, 0, 0, 0, 0x0000000000000010ll, 0, 0, 0, 0x0000000000000020ll, 0, 0, 0, 0x0000000000000040ll, 0, 0, 0, 0x0000000000000080ll, 0, 0, 0, 0x0000000000000100ll, 0, 0, 0, 0x0000000000000200ll, 0, 0, 0, 0x0000000000000400ll, 0, 0, 0, 0x0000000000000800ll, 0, 0, 0, 0x0000000000001000ll, 0, 0, 0, 0x0000000000002000ll, 0, 0, 0, 0x0000000000004000ll, 0, 0, 0, 0x0000000000008000ll, 0, 0, 0, 0x0000000000010000ll, 0, 0, 0, 0x0000000000020000ll, 0, 0, 0, 0x0000000000040000ll, 0, 0, 0, 0x0000000000080000ll, 0, 0, 0, 0x0000000000100000ll, 0, 0, 0, 0x0000000000200000ll, 0, 0, 0, 0x0000000000400000ll, 0, 0, 0, 0x0000000000800000ll, 0, 0, 0, 0x0000000001000000ll, 0, 0, 0, 0x0000000002000000ll, 0, 0, 0, 0x0000000004000000ll, 0, 0, 0, 0x0000000008000000ll, 0, 0, 0, 0x0000000010000000ll, 0, 0, 0, 0x0000000020000000ll, 0, 0, 0, 0x0000000040000000ll, 0, 0, 0, 0x0000000080000000ll, 0, 0, 0, 0x0000000100000000ll, 0, 0, 0, 0x0000000200000000ll, 0, 0, 0, 0x0000000400000000ll, 0, 0, 0, 0x0000000800000000ll, 0, 0, 0, 0x0000001000000000ll, 0, 0, 0, 0x0000002000000000ll, 0, 0, 0, 0x0000004000000000ll, 0, 0, 0, 0x0000008000000000ll, 0, 0, 0, 0x0000010000000000ll, 0, 0, 0, 0x0000020000000000ll, 0, 0, 0, 0x0000040000000000ll, 0, 0, 0, 0x0000080000000000ll, 0, 0, 0, 0x0000100000000000ll, 0, 0, 0, 0x0000200000000000ll, 0, 0, 0, 0x0000400000000000ll, 0, 0, 0, 0x0000800000000000ll, 0, 0, 0, 0x0001000000000000ll, 0, 0, 0, 0x0002000000000000ll, 0, 0, 0, 0x0004000000000000ll, 0, 0, 0, 0x0008000000000000ll, 0, 0, 0, 0x0010000000000000ll, 0, 0, 0, 0x0020000000000000ll, 0, 0, 0, 0x0040000000000000ll, 0, 0, 0, 0x0080000000000000ll, 0, 0, 0, 0x0100000000000000ll, 0, 0, 0, 0x0200000000000000ll, 0, 0, 0, 0x0400000000000000ll, 0, 0, 0, 0x0800000000000000ll, 0, 0, 0, 0x1000000000000000ll, 0, 0, 0, 0x2000000000000000ll, 0, 0, 0, 0x4000000000000000ll, 0, 0, 0, 0x8000000000000000ll, 0, 0, 0x0000000000000001ll, 0, 0, 0, 0x0000000000000002ll, 0, 0, 0, 0x0000000000000004ll, 0, 0, 0, 0x0000000000000008ll, 0, 0, 0, 0x0000000000000010ll, 0, 0, 0, 0x0000000000000020ll, 0, 0, 0, 0x0000000000000040ll, 0, 0, 0, 0x0000000000000080ll, 0, 0, 0, 0x0000000000000100ll, 0, 0, 0, 0x0000000000000200ll, 0, 0, 0, 0x0000000000000400ll, 0, 0, 0, 0x0000000000000800ll, 0, 0, 0, 0x0000000000001000ll, 0, 0, 0, 0x0000000000002000ll, 0, 0, 0, 0x0000000000004000ll, 0, 0, 0, 0x0000000000008000ll, 0, 0, 0, 0x0000000000010000ll, 0, 0, 0, 0x0000000000020000ll, 0, 0, 0, 0x0000000000040000ll, 0, 0, 0, 0x0000000000080000ll, 0, 0, 0, 0x0000000000100000ll, 0, 0, 0, 0x0000000000200000ll, 0, 0, 0, 0x0000000000400000ll, 0, 0, 0, 0x0000000000800000ll, 0, 0, 0, 0x0000000001000000ll, 0, 0, 0, 0x0000000002000000ll, 0, 0, 0, 0x0000000004000000ll, 0, 0, 0, 0x0000000008000000ll, 0, 0, 0, 0x0000000010000000ll, 0, 0, 0, 0x0000000020000000ll, 0, 0, 0, 0x0000000040000000ll, 0, 0, 0, 0x0000000080000000ll, 0, 0, 0, 0x0000000100000000ll, 0, 0, 0, 0x0000000200000000ll, 0, 0, 0, 0x0000000400000000ll, 0, 0, 0, 0x0000000800000000ll, 0, 0, 0, 0x0000001000000000ll, 0, 0, 0, 0x0000002000000000ll, 0, 0, 0, 0x0000004000000000ll, 0, 0, 0, 0x0000008000000000ll, 0, 0, 0, 0x0000010000000000ll, 0, 0, 0, 0x0000020000000000ll, 0, 0, 0, 0x0000040000000000ll, 0, 0, 0, 0x0000080000000000ll, 0, 0, 0, 0x0000100000000000ll, 0, 0, 0, 0x0000200000000000ll, 0, 0, 0, 0x0000400000000000ll, 0, 0, 0, 0x0000800000000000ll, 0, 0, 0, 0x0001000000000000ll, 0, 0, 0, 0x0002000000000000ll, 0, 0, 0, 0x0004000000000000ll, 0, 0, 0, 0x0008000000000000ll, 0, 0, 0, 0x0010000000000000ll, 0, 0, 0, 0x0020000000000000ll, 0, 0, 0, 0x0040000000000000ll, 0, 0, 0, 0x0080000000000000ll, 0, 0, 0, 0x0100000000000000ll, 0, 0, 0, 0x0200000000000000ll, 0, 0, 0, 0x0400000000000000ll, 0, 0, 0, 0x0800000000000000ll, 0, 0, 0, 0x1000000000000000ll, 0, 0, 0, 0x2000000000000000ll, 0, 0, 0, 0x4000000000000000ll, 0, 0, 0, 0x8000000000000000ll, 0, 0, 0x0000000000000001ll, 0, 0, 0, 0x0000000000000002ll, 0, 0, 0, 0x0000000000000004ll, 0, 0, 0, 0x0000000000000008ll, 0, 0, 0, 0x0000000000000010ll, 0, 0, 0, 0x0000000000000020ll, 0, 0, 0, 0x0000000000000040ll, 0, 0, 0, 0x0000000000000080ll, 0, 0, 0, 0x0000000000000100ll, 0, 0, 0, 0x0000000000000200ll, 0, 0, 0, 0x0000000000000400ll, 0, 0, 0, 0x0000000000000800ll, 0, 0, 0, 0x0000000000001000ll, 0, 0, 0, 0x0000000000002000ll, 0, 0, 0, 0x0000000000004000ll, 0, 0, 0, 0x0000000000008000ll, 0, 0, 0, 0x0000000000010000ll, 0, 0, 0, 0x0000000000020000ll, 0, 0, 0, 0x0000000000040000ll, 0, 0, 0, 0x0000000000080000ll, 0, 0, 0, 0x0000000000100000ll, 0, 0, 0, 0x0000000000200000ll, 0, 0, 0, 0x0000000000400000ll, 0, 0, 0, 0x0000000000800000ll, 0, 0, 0, 0x0000000001000000ll, 0, 0, 0, 0x0000000002000000ll, 0, 0, 0, 0x0000000004000000ll, 0, 0, 0, 0x0000000008000000ll, 0, 0, 0, 0x0000000010000000ll, 0, 0, 0, 0x0000000020000000ll, 0, 0, 0, 0x0000000040000000ll, 0, 0, 0, 0x0000000080000000ll, 0, 0, 0, 0x0000000100000000ll, 0, 0, 0, 0x0000000200000000ll, 0, 0, 0, 0x0000000400000000ll, 0, 0, 0, 0x0000000800000000ll, 0, 0, 0, 0x0000001000000000ll, 0, 0, 0, 0x0000002000000000ll, 0, 0, 0, 0x0000004000000000ll, 0, 0, 0, 0x0000008000000000ll, 0, 0, 0, 0x0000010000000000ll, 0, 0, 0, 0x0000020000000000ll, 0, 0, 0, 0x0000040000000000ll, 0, 0, 0, 0x0000080000000000ll, 0, 0, 0, 0x0000100000000000ll, 0, 0, 0, 0x0000200000000000ll, 0, 0, 0, 0x0000400000000000ll, 0, 0, 0, 0x0000800000000000ll, 0, 0, 0, 0x0001000000000000ll, 0, 0, 0, 0x0002000000000000ll, 0, 0, 0, 0x0004000000000000ll, 0, 0, 0, 0x0008000000000000ll, 0, 0, 0, 0x0010000000000000ll, 0, 0, 0, 0x0020000000000000ll, 0, 0, 0, 0x0040000000000000ll, 0, 0, 0, 0x0080000000000000ll, 0, 0, 0, 0x0100000000000000ll, 0, 0, 0, 0x0200000000000000ll, 0, 0, 0, 0x0400000000000000ll, 0, 0, 0, 0x0800000000000000ll, 0, 0, 0, 0x1000000000000000ll, 0, 0, 0, 0x2000000000000000ll, 0, 0, 0, 0x4000000000000000ll, 0, 0, 0, 0x8000000000000000ll, 0, 0, 0x0000000000000001ll, 0, 0, 0, 0x0000000000000002ll, 0, 0, 0, 0x0000000000000004ll, 0, 0, 0, 0x0000000000000008ll, 0, 0, 0, 0x0000000000000010ll, 0, 0, 0, 0x0000000000000020ll, 0, 0, 0, 0x0000000000000040ll, 0, 0, 0, 0x0000000000000080ll, 0, 0, 0, 0x0000000000000100ll, 0, 0, 0, 0x0000000000000200ll, 0, 0, 0, 0x0000000000000400ll, 0, 0, 0, 0x0000000000000800ll, 0, 0, 0, 0x0000000000001000ll, 0, 0, 0, 0x0000000000002000ll, 0, 0, 0, 0x0000000000004000ll, 0, 0, 0, 0x0000000000008000ll, 0, 0, 0, 0x0000000000010000ll, 0, 0, 0, 0x0000000000020000ll, 0, 0, 0, 0x0000000000040000ll, 0, 0, 0, 0x0000000000080000ll, 0, 0, 0, 0x0000000000100000ll, 0, 0, 0, 0x0000000000200000ll, 0, 0, 0, 0x0000000000400000ll, 0, 0, 0, 0x0000000000800000ll, 0, 0, 0, 0x0000000001000000ll, 0, 0, 0, 0x0000000002000000ll, 0, 0, 0, 0x0000000004000000ll, 0, 0, 0, 0x0000000008000000ll, 0, 0, 0, 0x0000000010000000ll, 0, 0, 0, 0x0000000020000000ll, 0, 0, 0, 0x0000000040000000ll, 0, 0, 0, 0x0000000080000000ll, 0, 0, 0, 0x0000000100000000ll, 0, 0, 0, 0x0000000200000000ll, 0, 0, 0, 0x0000000400000000ll, 0, 0, 0, 0x0000000800000000ll, 0, 0, 0, 0x0000001000000000ll, 0, 0, 0, 0x0000002000000000ll, 0, 0, 0, 0x0000004000000000ll, 0, 0, 0, 0x0000008000000000ll, 0, 0, 0, 0x0000010000000000ll, 0, 0, 0, 0x0000020000000000ll, 0, 0, 0, 0x0000040000000000ll, 0, 0, 0, 0x0000080000000000ll, 0, 0, 0, 0x0000100000000000ll, 0, 0, 0, 0x0000200000000000ll, 0, 0, 0, 0x0000400000000000ll, 0, 0, 0, 0x0000800000000000ll, 0, 0, 0, 0x0001000000000000ll, 0, 0, 0, 0x0002000000000000ll, 0, 0, 0, 0x0004000000000000ll, 0, 0, 0, 0x0008000000000000ll, 0, 0, 0, 0x0010000000000000ll, 0, 0, 0, 0x0020000000000000ll, 0, 0, 0, 0x0040000000000000ll, 0, 0, 0, 0x0080000000000000ll, 0, 0, 0, 0x0100000000000000ll, 0, 0, 0, 0x0200000000000000ll, 0, 0, 0, 0x0400000000000000ll, 0, 0, 0, 0x0800000000000000ll, 0, 0, 0, 0x1000000000000000ll, 0, 0, 0, 0x2000000000000000ll, 0, 0, 0, 0x4000000000000000ll, 0, 0, 0, 0x8000000000000000ll, 0, 0, 0 };

// SIMD-enabled bitset (this could probably be optimized further, but it does slightly outperform std::bitset):
template<int K>
struct fast_bitset_large
{
	static constexpr int N = 1 << K, M = N / 256;
	alignas(256) __m256i data[M];

	[[gnu::always_inline]] inline fast_bitset_large &operator|=(fast_bitset_large const &B) noexcept
	{
		for (int i = 0; i < M; i++)
			data[i] = _mm256_or_si256(data[i], B.data[i]);
		return *this;
	}
	[[gnu::always_inline]] inline fast_bitset_large &operator&=(fast_bitset_large const &B) noexcept
	{
		for (int i = 0; i < M; i++)
			data[i] = _mm256_and_si256(data[i], B.data[i]);
		return *this;
	}
	[[gnu::always_inline]] inline fast_bitset_large &set() noexcept
	{
		__m256i const ONES = _mm256_set1_epi64x(-1ll);
		for (int i = 0; i < M; i++)
			data[i] = ONES;
		return *this;
	}
	[[gnu::always_inline]] inline fast_bitset_large &set(int i) noexcept
	{
		data[i / 256] = _mm256_or_si256(data[i / 256], _mm256_load_si256((__m256i *)(BITS + i % 256 * 4)));
		return *this;
	}
	[[gnu::always_inline]] inline fast_bitset_large &flip() noexcept
	{
		__m256i const ONES = _mm256_set1_epi64x(-1ll);
		for (int i = 0; i < M; i++)
			data[i] = _mm256_xor_si256(data[i], ONES);
		return *this;
	}
	[[gnu::always_inline]] inline bool none() const noexcept
	{
		for (int i = 0; i < M; i++)
			if (!_mm256_testz_si256(data[i], data[i]))
				return false;
		return true;
	}

	inline friend ostream &operator<<(ostream &os, fast_bitset_large const &A)
	{
		for (int i = M; i-- > 0;)
		{
			for (int j = 4; j-- > 0;)
				os << bitset<64>(((uint64_t *)(A.data + i))[j]);
		}
		return os;
	}
};

template<int K>
[[gnu::always_inline]] inline fast_bitset_large<K> operator|(fast_bitset_large<K> const &A, fast_bitset_large<K> const &B) noexcept
{
	fast_bitset_large<K> ans;
	for (int i = 0; i < fast_bitset_large<K>::M; i++)
		ans.data[i] = _mm256_or_si256(A.data[i], B.data[i]);
	return ans;
}
template<int K>
[[gnu::always_inline]] inline fast_bitset_large<K> operator&(fast_bitset_large<K> const &A, fast_bitset_large<K> const &B) noexcept
{
	fast_bitset_large<K> ans;
	for (int i = 0; i < fast_bitset_large<K>::M; i++)
		ans.data[i] = _mm256_and_si256(A.data[i], B.data[i]);
	return ans;
}

// Returns whether B is disjoint from ~A and from A, respectively.
template<int K>
[[gnu::always_inline]] inline pair<bool, bool> test_cz(fast_bitset_large<K> const &A, fast_bitset_large<K> const &B) noexcept
{
	bool a = true, b = true;
	for (int i = 0; i < fast_bitset_large<K>::M; i++)
	{
		a &= _mm256_testc_si256(A.data[i], B.data[i]);
		b &= _mm256_testz_si256(A.data[i], B.data[i]);
	}
	return { a, b };
}

// Returns whether B is disjoint from ~A and from A, respectively.
template<size_t N>
[[gnu::always_inline]] inline pair<bool, bool> test_cz(bitset<N> const &A, bitset<N> const &B) noexcept
{
	return { (~A & B).none(), (A & B).none() };
}

template<int K>
using fast_bitset = conditional_t < K < 8,
	bitset<1 << K>,
	fast_bitset_large<K>>;

template<int K>
struct solver
{
	// var_st[i] is the set of assignments where variable i is set to true.
	static fast_bitset<K> var_st[K];

	// S -> A ("|" A)*
	static constexpr fast_bitset<K> eval_or(char const *&ptr) noexcept
	{
		// Recursively evaluate the first A
		fast_bitset<K> ans = eval_and(ptr);
		while (*ptr == '|')
		{
			// Skip the |
			ptr++;
			// Recursively evaluate subsequent A's and update the result.
			ans |= eval_and(ptr);
		}
		return ans;
	}
	// A -> B ("&" B)*
	static constexpr fast_bitset<K> eval_and(char const *&ptr) noexcept
	{
		// Recursively evaluate the first B
		fast_bitset<K> ans = eval_literal(ptr);
		while (*ptr == '&')
		{
			// Skip the &
			ptr++;
			// Recursively evaluate subsequent B's and update the result.
			ans &= eval_literal(ptr);
		}
		return ans;
	}
	// B -> "~"* ("(" S ")" + <variable>)
	static constexpr fast_bitset<K> eval_literal(char const *&ptr) noexcept
	{
		bool flip = false;
		// skip the ~'s and determine whether there is an even or odd number of them.
		while (*ptr == '~')
		{
			ptr++;
			flip = !flip;
		}
		// For "(" S ")", skip the parenthesis and recursively evaluate S.
		// For <variable>, look up its evaluation.
		fast_bitset<K> ans = *ptr == '(' ? eval_or(++ptr) : var_st[ids[(int)*ptr]];
		// skip variable name or closing parenthesis
		ptr++;
		// flip iff an odd number of ~'s
		if (flip)
			ans.flip();
		return ans;
	}

	// Run the statement list starting with the token *it, given that only assignments in st can make it here.
	static void run(vector<string>::const_iterator &it, fast_bitset<K> st)
	{
		// For each statement:
		for (;; it++)
		{
			// "if"
			if (it->front() == 'i')
			{
				// Skip "if"
				char const *ptr = (++it)->c_str();
				// Evaluate the condition for all assignments
				fast_bitset<K> cond = eval_or(ptr);
				// Skip the condition and "then", then run the statement list inside given st & cond
				run(it += 2, cond & st);
				// else
				if (it->front() == 'e')
				{
					cond.flip();
					// Skip "else", then run the statement list inside given st & ~cond
					run(++it, cond &= st);
				}
			}
			else if (it->front() == 'c')
			{
				cout << '>';
				// no assignments are possible:
				if (st.none())
					cout << "unreachable\n";
				else
				{
					for (int i = 0; i < K; i++)
					{
						auto [c, z] = test_cz(var_st[i], st);
						// st disjoint from ~var_st[i]: no assignments have variable i set to false
						if (c)
							cout << vars[i];
						// st disjoint from var_st[i]: no assignments have variable i set to true
						else if (z)
							cout << char(vars[i] | 32);
					}
					cout << '\n';
				}
			}
			else
				break;
		}
	}

	static void solve()
	{
		// calculate var_st[i] for all i
		for (int i = 0; i < K; i++)
			for (int j = 0; j < (1 << K); j++)
				if ((1 << i) & j)
					var_st[i].set(j);

		fast_bitset<K> st;
		// initially all assignments are possible
		st.set();
		auto it = cbegin(tokens);
		// run the program
		run(it, st);
	}
};
template<int K>
fast_bitset<K> solver<K>::var_st[K];

int main()
{
	cin.tie(0)->sync_with_stdio(0);

	// read and tokenize input
	for (string token; cin >> token;)
	{
		// determine which variables are used in this token
		for (char c : token)
			if ('A' <= c && c <= 'Z' && find(vars, vars + k, c) == vars + k)
				vars[k++] = c;
		// add this token to the list
		tokens.push_back(move(token));
	}
	// add dummy end token
	tokens.push_back("e");

	// sort variables alphabetically
	sort(vars, vars + k);
	// find variables' indices in alphabetic order (aka their id's)
	for (int i = 0; i < k; i++)
		ids[(int)vars[i]] = i;

	// since K is a template parameter, it can't be assigned dynamically at runtime, so this switch is necessary.
	switch (k)
	{
	case 1: solver<1>::solve(); break;
	case 2: solver<2>::solve(); break;
	case 3: solver<3>::solve(); break;
	case 4: solver<4>::solve(); break;
	case 5: solver<5>::solve(); break;
	case 6: solver<6>::solve(); break;
	case 7: solver<7>::solve(); break;
	case 8: solver<8>::solve(); break;
	case 9: solver<9>::solve(); break;
	case 10: solver<10>::solve(); break;
	case 11: solver<11>::solve(); break;
	case 12: solver<12>::solve(); break;
	case 13: solver<13>::solve(); break;
	case 14: solver<14>::solve(); break;
	case 15: solver<15>::solve(); break;
	case 16: solver<16>::solve(); break;
	case 17: solver<17>::solve(); break;
	case 18: solver<18>::solve(); break;
	case 19: solver<19>::solve(); break;
	case 20: solver<20>::solve(); break;
	}
}