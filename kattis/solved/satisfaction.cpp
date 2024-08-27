#pragma GCC optimize("Ofast,no-stack-protector,unroll-loops")
#pragma GCC target("sse,sse2,sse3,ssse3,sse4,sse4.1,sse4.2,popcnt,abm,mmx,avx,avx2,fma,tune=native")

#include <bits/stdc++.h>
#include <immintrin.h>
#include <nmmintrin.h>

using namespace std;

#define BUFS 1 << 20
alignas(256) static inline char buf[BUFS];
static inline int iptr, optr;

// number of variables
static inline int k = 0;

// variable name -> id
static inline int ids[91];

// variable id -> name
static inline char vars[20];

alignas(256) static inline __m256i ARENA[1 << 19];
alignas(256) static inline int F[1 << 19];
static inline int nxt, fnxt;

// var_st[i] is the set of assignments where variable i is set to true.
// alignas(256) static inline __m256i var_st[81920];

template<int K, int L = 1 << max(K - 8, 0)>
__attribute__((always_inline)) static inline int alc() noexcept
{
	int ans;
	if (fnxt)
	{
		fnxt--;
		ans = F[fnxt];
	}
	else
	{
		ans = nxt;
		nxt += L;
	}
	return ans;
}
__attribute__((always_inline)) static inline void dealc(int a) noexcept
{
	F[fnxt++] = a;
}

template<int K, int L = 1 << max(K - 8, 0)>
__attribute__((always_inline)) static inline __m256i fmask() noexcept
{
	if constexpr (K == 1)
		return _mm256_setr_epi64x(
			0x0000000000000003ll, 0x0000000000000000ll, 0x0000000000000000ll, 0x0000000000000000ll);
	else if constexpr (K == 2)
		return _mm256_setr_epi64x(
			0x000000000000000fll, 0x0000000000000000ll, 0x0000000000000000ll, 0x0000000000000000ll);
	else if constexpr (K == 3)
		return _mm256_setr_epi64x(
			0x00000000000000ffll, 0x0000000000000000ll, 0x0000000000000000ll, 0x0000000000000000ll);
	else if constexpr (K == 4)
		return _mm256_setr_epi64x(
			0x000000000000ffffll, 0x0000000000000000ll, 0x0000000000000000ll, 0x0000000000000000ll);
	else if constexpr (K == 5)
		return _mm256_setr_epi64x(
			0x00000000ffffffffll, 0x0000000000000000ll, 0x0000000000000000ll, 0x0000000000000000ll);
	else if constexpr (K == 6)
		return _mm256_setr_epi64x(
			0xffffffffffffffffll, 0x0000000000000000ll, 0x0000000000000000ll, 0x0000000000000000ll);
	else if constexpr (K == 7)
		return _mm256_setr_epi64x(
			0xffffffffffffffffll, 0xffffffffffffffffll, 0x0000000000000000ll, 0x0000000000000000ll);
	else
		return _mm256_setr_epi64x(
			0xffffffffffffffffll, 0xffffffffffffffffll, 0xffffffffffffffffll, 0xffffffffffffffffll);
}

template<int K, bool DB = true, int L = 1 << max(K - 8, 0)>
__attribute__((always_inline)) static inline int avx_or(int a, int b) noexcept
{
	for (int i = 0; i < L; i++)
		ARENA[a + i] = _mm256_or_si256(ARENA[a + i], ARENA[b + i]);
	if constexpr (DB)
		dealc(b);
	return a;
}
template<int K, bool DB = true, int L = 1 << max(K - 8, 0)>
__attribute__((always_inline)) static inline int avx_and(int a, int b) noexcept
{
	for (int i = 0; i < L; i++)
		ARENA[a + i] = _mm256_and_si256(ARENA[a + i], ARENA[b + i]);
	if constexpr (DB)
		dealc(b);
	return a;
}
template<int K, bool DB = true, int L = 1 << max(K - 8, 0)>
__attribute__((always_inline)) static inline int avx_andnot(int a, int b) noexcept
{
	for (int i = 0; i < L; i++)
		ARENA[a + i] = _mm256_andnot_si256(ARENA[a + i], ARENA[b + i]);
	if constexpr (DB)
		dealc(b);
	return a;
}
// TODO lazily evaluate this
template<int K, int L = 1 << max(K - 8, 0)>
__attribute__((always_inline)) static inline int avx_var(int id, bool fl) noexcept
{
	static __m256i const M[8]{
		_mm256_set1_epi64x(0xaaaaaaaaaaaaaaaall),
		_mm256_set1_epi64x(0xccccccccccccccccll),
		_mm256_set1_epi64x(0xf0f0f0f0f0f0f0f0ll),
		_mm256_set1_epi64x(0xff00ff00ff00ff00ll),
		_mm256_set1_epi64x(0xffff0000ffff0000ll),
		_mm256_set1_epi64x(0xffffffff00000000ll),
		_mm256_setr_epi64x(0x0000000000000000ll, 0xffffffffffffffffll, 0x0000000000000000ll, 0xffffffffffffffffll),
		_mm256_setr_epi64x(0x0000000000000000ll, 0x0000000000000000ll, 0xffffffffffffffffll, 0xffffffffffffffffll)};
	static const __m256i zero = _mm256_setzero_si256();
	static const __m256i ones = _mm256_set1_epi32(-1);

	int a = alc<K>();
	if constexpr (K < 8)
	{
		if (fl)
			ARENA[a] = _mm256_xor_si256(M[id], fmask<K>());
		else
			ARENA[a] = M[id];
	}
	else if (id < 8)
	{
		if (fl)
			for (int i = 0; i < L; i++)
				ARENA[a + i] = _mm256_xor_si256(M[id], fmask<K>());
		else
			for (int i = 0; i < L; i++)
				ARENA[a + i] = M[id];
	}
	else
	{
		int bit = 1 << (id - 8);
		if (fl)
			for (int i = 0; i < L; i++)
				ARENA[a + i] = (i & bit) ? zero : ones;
		else
			for (int i = 0; i < L; i++)
				ARENA[a + i] = (i & bit) ? ones : zero;
	}
	return a;
}
template<int K, int L = 1 << max(K - 8, 0)>
__attribute__((always_inline)) static inline int avx_any(int a) noexcept
{
	for (int i = 0; i < L; i++)
		if (!_mm256_testz_si256(ARENA[a + i], ARENA[a + i]))
			return true;
	return false;
}
template<int K, int L = 1 << max(K - 8, 0)>
__attribute__((always_inline)) static inline pair<bool, bool> avx_var_cz(int id, int a) noexcept
{
	bool c = true, z = true;
	int	 i = 0;

	static __m256i const M[8]{
		_mm256_set1_epi64x(0xaaaaaaaaaaaaaaaall),
		_mm256_set1_epi64x(0xccccccccccccccccll),
		_mm256_set1_epi64x(0xf0f0f0f0f0f0f0f0ll),
		_mm256_set1_epi64x(0xff00ff00ff00ff00ll),
		_mm256_set1_epi64x(0xffff0000ffff0000ll),
		_mm256_set1_epi64x(0xffffffff00000000ll),
		_mm256_setr_epi64x(0x0000000000000000ll, 0xffffffffffffffffll, 0x0000000000000000ll, 0xffffffffffffffffll),
		_mm256_setr_epi64x(0x0000000000000000ll, 0x0000000000000000ll, 0xffffffffffffffffll, 0xffffffffffffffffll)};
	static const __m256i zero = _mm256_setzero_si256();
	static const __m256i ones = _mm256_set1_epi32(-1);

	if (K < 8 || id < 8)
		for (; (c || z) && i < L; i++)
		{
			c &= _mm256_testc_si256(M[id], ARENA[a + i]);
			z &= _mm256_testz_si256(M[id], ARENA[a + i]);
		}
	else
	{
		int bit = 1 << (id - 8);
		for (; (c || z) && i < L; i++)
		{
			c &= _mm256_testc_si256(i & bit ? ones : zero, ARENA[a + i]);
			z &= _mm256_testz_si256(i & bit ? ones : zero, ARENA[a + i]);
		}
	}
	return {c, z};
}

template<int K, bool N, int L = 1 << max(K - 8, 0)>
static inline int eval_or() noexcept;
// B -> "~"* ("(" S ")" + <variable>)
template<int K, bool N, int L = 1 << max(K - 8, 0)>
__attribute__((always_inline)) static inline int eval_literal() noexcept
{
	bool flip = N;
	// skip the ~'s and determine whether there is an even or odd number of them.
	while (buf[iptr] == '~')
	{
		iptr++;
		flip = !flip;
	}
	// For "(" S ")", skip the parenthesis and recursively evaluate S.
	// For <variable>, look up its evaluation.
	int ans;
	if (buf[iptr] == '(')
	{
		iptr++;
		if (flip)
			ans = eval_or<K, 1>();
		else
			ans = eval_or<K, 0>();
	}
	else
		ans = avx_var<K>(ids[(int)buf[iptr]], flip);

	iptr++;
	return ans;
}
// A -> B ("&" B)*
template<int K, bool N, int L = 1 << max(K - 8, 0)>
__attribute__((always_inline)) static inline int eval_and() noexcept
{
	// Recursively evaluate the first B
	int ans = eval_literal<K, N>();
	while (buf[iptr] == '&')
	{
		// Skip the &
		iptr++;
		// Recursively evaluate subsequent B's and update the result.
		if constexpr (N)
			ans = avx_or<K>(ans, eval_literal<K, N>());
		else
			ans = avx_and<K>(ans, eval_literal<K, N>());
	}
	return ans;
}
// S -> A ("|" A)*
template<int K, bool N, int L>
static inline int eval_or() noexcept
{
	// Recursively evaluate the first A
	int ans = eval_and<K, N>();
	while (buf[iptr] == '|')
	{
		// Skip the |
		iptr++;
		// Recursively evaluate subsequent A's and update the result.
		if constexpr (N)
			ans = avx_and<K>(ans, eval_and<K, N>());
		else
			ans = avx_or<K>(ans, eval_and<K, N>());
	}
	return ans;
}

__attribute__((always_inline)) static inline void skip() noexcept
{
	while (buf[iptr] == ' ' || buf[iptr] == '\n' || buf[iptr] == '\t')
		iptr++;
}

// static inline void run_ur() noexcept
// {
//  for (;;)
//  {
//      skip();
//      if (buf[iptr] == 'i')
//      {
//          iptr += 3;
//          skip();
//          while (buf[iptr] != ' ' && buf[iptr] != '\n' && buf[iptr] != '\t')
//              iptr++;
//          iptr++;
//          skip();
//          iptr += 5;
//          run_ur();
//          if (buf[iptr] == 'e')
//          {
//              iptr += 5;
//              run_ur();
//          }
//          iptr += 2;
//      }
//      else if (buf[iptr] == 'c')
//      {
//          iptr += 11;
//          buf[optr++] = '>';
//          buf[optr++] = 'u';
//          buf[optr++] = 'n';
//          buf[optr++] = 'r';
//          buf[optr++] = 'e';
//          buf[optr++] = 'a';
//          buf[optr++] = 'c';
//          buf[optr++] = 'h';
//          buf[optr++] = 'a';
//          buf[optr++] = 'b';
//          buf[optr++] = 'l';
//          buf[optr++] = 'e';
//          buf[optr++] = '\n';
//      }
//      else
//          break;
//  }
// }
static inline int ur_stack[1 << 13];

static inline void run_ur() noexcept
{
	int ur_nxt		   = 0;
	ur_stack[ur_nxt++] = 0;
	while (ur_nxt)
	{
		switch (ur_stack[ur_nxt - 1])
		{
		case 0:
			skip();
			if (buf[iptr] == 'i')
			{
				iptr += 3;
				skip();
				while (buf[iptr] != ' ' && buf[iptr] != '\n' && buf[iptr] != '\t')
					iptr++;
				iptr++;
				skip();
				iptr += 5;
				ur_stack[ur_nxt - 1] = 1;
				ur_stack[ur_nxt++]	 = 0;
				break;
			}
			else if (buf[iptr] == 'c')
			{
				iptr += 11;
				buf[optr++] = '>';
				buf[optr++] = 'u';
				buf[optr++] = 'n';
				buf[optr++] = 'r';
				buf[optr++] = 'e';
				buf[optr++] = 'a';
				buf[optr++] = 'c';
				buf[optr++] = 'h';
				buf[optr++] = 'a';
				buf[optr++] = 'b';
				buf[optr++] = 'l';
				buf[optr++] = 'e';
				buf[optr++] = '\n';
			}
			else
				ur_nxt--;
			break;
		case 1:
			ur_stack[ur_nxt - 1] = 2;
			if (buf[iptr] == 'e')
			{
				iptr += 5;
				ur_stack[ur_nxt++] = 0;
			}
			break;
		case 2:
			iptr += 2;
			ur_stack[ur_nxt - 1] = 0;
			break;
		}
	}
}

template<int K, bool T = true, int L = 1 << max(K - 8, 0)>
static inline void run(int st, int mask0, int mask1) noexcept
{
	bool first_chkpt = !T;
	bool ur			 = false;
	for (;;)
	{
		skip();
		if (buf[iptr] == 'i')
		{
			iptr += 3;
			skip();
			int cond = eval_or<K, 0>();
			iptr++;
			skip();
			iptr += 5;
			cond = avx_and<K, 0>(cond, st);
			if (ur)
				run_ur();
			else
				run<K, false>(cond, mask0, mask1);
			if (buf[iptr] == 'e')
			{
				iptr += 5;
				cond = avx_andnot<K, 0>(cond, st);
				if (ur)
					run_ur();
				else
					run<K, false>(cond, mask0, mask1);
			}
			dealc(cond);
			iptr += 2;
		}
		else if (buf[iptr] == 'c')
		{
			iptr += 11;
			bool reachable = !ur && avx_any<K>(st);
			buf[optr++]	   = '>';
			if (!reachable)
			{
				buf[optr++] = 'u';
				buf[optr++] = 'n';
				buf[optr++] = 'r';
				buf[optr++] = 'e';
				buf[optr++] = 'a';
				buf[optr++] = 'c';
				buf[optr++] = 'h';
				buf[optr++] = 'a';
				buf[optr++] = 'b';
				buf[optr++] = 'l';
				buf[optr++] = 'e';
				buf[optr++] = '\n';
				ur			= true;
			}
			else
			{
				if (first_chkpt)
				{
					for (int i = 0; i < K; i++)
					{
						int bit = 1 << i;
						if (bit & (mask0 | mask1))
							continue;
						auto [c, z] = avx_var_cz<K>(i, st);
						if (c)
							mask1 |= bit;
						else if (z)
							mask0 |= bit;
					}
					first_chkpt = false;
				}
				for (int i = 0; i < K; i++)
				{
					int bit = 1 << i;
					if (mask1 & bit)
						buf[optr++] = vars[i];
					else if (mask0 & bit)
						buf[optr++] = char(vars[i] | 32);
				}
				buf[optr++] = '\n';
			}
		}
		else
			break;
	}
}

template<int K, int L = 1 << max(K - 8, 0)>
static void solve()
{
	int st = alc<K>();
	// initially all assignments are possible
	for (int i = 0; i < L; i++)
		ARENA[st + i] = fmask<K>();
	run<K>(st, 0, 0);
}

int main()
{
	read(STDIN_FILENO, buf, BUFS);

	int seen = 0;

	for (int i = 0; buf[i] != '\0';)
	{
		if ('A' <= buf[i] && buf[i] <= 'Z')
			seen |= 1 << (buf[i] - 'A');
		i++;
	}

	for (char c = 'A'; c <= 'Z'; c++)
		if (seen & (1 << (c - 'A')))
		{
			ids[(int)c] = k;
			vars[k++]	= c;
		}

	switch (k)
	{
#define C(a)                                                                                                           \
	case a:                                                                                                            \
		solve<a>();                                                                                                    \
		break;
		C(1)
		C(2)
		C(3)
		C(4)
		C(5)
		C(6)
		C(7)
		C(8)
		C(9)
		C(10)
		C(11)
		C(12)
		C(13)
		C(14)
		C(15)
		C(16)
		C(17)
		C(18)
		C(19)
		C(20)
#undef C
	default:
		__builtin_unreachable();
	}

	write(STDOUT_FILENO, buf, optr);
}
