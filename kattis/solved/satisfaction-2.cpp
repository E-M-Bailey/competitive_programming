// #define TEST

#ifndef TEST
#pragma GCC optimize("Ofast,no-stack-protector,unroll-loops")
#endif
#pragma GCC target("sse,sse2,sse3,ssse3,sse4,sse4.1,sse4.2,popcnt,abm,mmx,avx,avx2,fma,tune=native")

#ifndef TEST
#define FINLINE __attribute__((always_inline)) inline
#else
#define FINLINE
#endif

#include <bits/stdc++.h>
#include <immintrin.h>
#include <nmmintrin.h>

using namespace std;

typedef unsigned long long ull;

#define BUFS (1 << 20)
alignas(256) static inline char buf[BUFS];
static inline int iptr, optr;

#define K 20
#define L (1 << (K - 8))

// variable name -> id
static inline int ids[91];

// variable id -> name
static inline char vars[K];

#define ARENAS (1 << 7)

alignas(256) static inline __m256i ARENA[ARENAS][L];
alignas(256) static inline char F[ARENAS];
static inline int nxt, fnxt;

// var_st[i] is the set of assignments where variable i is set to true.
// alignas(256) static inline __m256i var_st[81920];

#define E_IMP 0x8000000000000000ull
#define E_NEG 0x4000000000000000ull

struct const_expr;
struct mut_expr;

template<typename E>
concept expr = same_as<E, const_expr> || same_as<E, mut_expr>;

struct const_expr
{
	ull x;

	FINLINE constexpr __m256i const &operator[](int i) const noexcept;
	FINLINE							 operator bool() const noexcept;
	FINLINE constexpr explicit		 operator mut_expr() const noexcept;
};
struct mut_expr
{
	ull x;

	FINLINE constexpr __m256i &operator[](int i) const noexcept;
	FINLINE					   operator bool() const noexcept;
	FINLINE constexpr		   operator const_expr() const noexcept;
};

FINLINE static mut_expr alc() noexcept;
FINLINE static void		dealc(const_expr a) noexcept;
FINLINE static void		dealc(mut_expr a) noexcept;

// TODO: allow implicit representation of conjunctions/disjunctions of a set of variables

FINLINE static constexpr bool imp(expr auto a) noexcept
{
	return a.x & E_IMP;
}
FINLINE static constexpr bool neg(expr auto a) noexcept
{
	return a.x & E_NEG;
}
FINLINE static constexpr __m256i &subscript(expr auto a, int i) noexcept
{
	if (imp(a))
		__builtin_unreachable();

	auto y = a.x & ~E_NEG;
	if (y >= ARENAS)
		__builtin_unreachable();

	return ARENA[y][i];
}
FINLINE static constexpr bool alias(expr auto a, expr auto b) noexcept
{
	auto x = a.x ^ b.x;
	return !(x & ~E_NEG);
}

FINLINE static constexpr auto operator~(expr auto a) noexcept -> decltype(a)
{
	return {a.x ^ E_NEG};
}
FINLINE static auto operator|(mut_expr a, expr auto b) noexcept -> decltype(b)
{
	return ~(~a & ~b);
}

FINLINE static auto and_alias(mut_expr a, expr auto b) noexcept -> decltype(b)
{
	if (a.x == b.x)
		return b;
	else
	{
		dealc(b);
		return {E_IMP | E_NEG};
	}
}
FINLINE static constexpr auto and_imp_imp(expr auto a, expr auto b) noexcept -> common_type_t<decltype(a), decltype(b)>
{
	return {a.x | b.x};
}
FINLINE static constexpr auto and_imp_exp(expr auto a, expr auto b) noexcept -> common_type_t<decltype(a), decltype(b)>
{
	if (neg(a))
	{
		dealc(b);
		return a;
	}
	else
	{
		return b;
	}
}
FINLINE static constexpr auto and_exp_exp(mut_expr a, expr auto b) noexcept -> decltype(b)
{
	if (neg(a))
	{
		if (neg(b))
		{
			for (int i = 0; i < L; i++)
				a[i] = _mm256_or_si256(a[i], b[i]);
		}
		else
		{
			a.x ^= E_NEG;
			for (int i = 0; i < L; i++)
				a[i] = _mm256_andnot_si256(a[i], b[i]);
		}
	}
	else
	{
		if (neg(b))
		{
			for (int i = 0; i < L; i++)
				a[i] = _mm256_andnot_si256(b[i], a[i]);
		}
		else
		{
			for (int i = 0; i < L; i++)
				a[i] = _mm256_and_si256(a[i], b[i]);
		}
	}
	dealc(b);
	return a;
}

// If a and b are aliased and b is a const_expr, neither will be modified.
FINLINE static constexpr auto operator&(mut_expr a, expr auto b) noexcept -> decltype(b)
{
	decltype(b) ans;
	if (alias(a, b))
		ans = and_alias(a, b);
	else if (imp(a) && imp(b))
		ans = and_imp_imp(a, b);
	else if (imp(a))
		ans = and_imp_exp(a, b);
	else if (imp(b))
		ans = and_imp_exp(b, a);
	else
		ans = and_exp_exp(a, b);
	// cerr << hex << "and " << a.x << ' ' << b.x << ' ' << alias(a, b) << ' ' << ans.x << endl;
	return ans;
}
FINLINE static mut_expr var(int id) noexcept
{
	__m256i const M[8]{
		_mm256_set1_epi64x(0xaaaaaaaaaaaaaaaall),
		_mm256_set1_epi64x(0xccccccccccccccccll),
		_mm256_set1_epi64x(0xf0f0f0f0f0f0f0f0ll),
		_mm256_set1_epi64x(0xff00ff00ff00ff00ll),
		_mm256_set1_epi64x(0xffff0000ffff0000ll),
		_mm256_set1_epi64x(0xffffffff00000000ll),
		_mm256_setr_epi64x(0x0000000000000000ll, 0xffffffffffffffffll, 0x0000000000000000ll, 0xffffffffffffffffll),
		_mm256_setr_epi64x(0x0000000000000000ll, 0x0000000000000000ll, 0xffffffffffffffffll, 0xffffffffffffffffll)};
	auto a = alc();
	if (id < 8)
	{
		for (int i = 0; i < L; i++)
			a[i] = M[id];
	}
	else
	{
		int bit = 1 << (id - 8);
		for (int i = 0; i < L; i++)
			a[i] = (i & bit) ? _mm256_set1_epi32(-1) : _mm256_setzero_si256();
	}
	// cerr << "var " << vars[id] << ' ' << hex << a.x << endl;
	return a;
}
FINLINE static bool as_bool(expr auto a) noexcept
{
	// cerr << "as_bool " << hex << a.x << endl;
	if (imp(a))
		return !neg(a);
	else
	{
		if (neg(a))
		{
			for (int i = 0; i < L; i++)
				if (!_mm256_testc_si256(a[i], _mm256_set1_epi32(-1)))
					return true;
		}
		else
		{
			for (int i = 0; i < L; i++)
				if (!_mm256_testz_si256(a[i], _mm256_set1_epi32(-1)))
					return true;
		}
		return false;
	}
}
FINLINE static constexpr pair<bool, bool> var_cz(int id, expr auto a) noexcept
{
	__m256i const M[8]{
		_mm256_set1_epi64x(0xaaaaaaaaaaaaaaaall),
		_mm256_set1_epi64x(0xccccccccccccccccll),
		_mm256_set1_epi64x(0xf0f0f0f0f0f0f0f0ll),
		_mm256_set1_epi64x(0xff00ff00ff00ff00ll),
		_mm256_set1_epi64x(0xffff0000ffff0000ll),
		_mm256_set1_epi64x(0xffffffff00000000ll),
		_mm256_setr_epi64x(0x0000000000000000ll, 0xffffffffffffffffll, 0x0000000000000000ll, 0xffffffffffffffffll),
		_mm256_setr_epi64x(0x0000000000000000ll, 0x0000000000000000ll, 0xffffffffffffffffll, 0xffffffffffffffffll)};

	if (imp(a))
	{
		return {neg(a), neg(a)};
	}
	else
	{
		// whether ~v and v each are disjoint from a.
		bool c = true, z = true;
		int	 i = 0;

		if (id < 8)
		{
			__m256i maskz = M[id], maskc = _mm256_xor_si256(maskz, _mm256_set1_epi32(-1));
			if (neg(a))
				for (; (c || z) && i < L; i++)
				{
					c &= _mm256_testc_si256(a[i], maskc);
					z &= _mm256_testc_si256(a[i], maskz);
				}
			else
				for (; (c || z) && i < L; i++)
				{
					c &= _mm256_testz_si256(a[i], maskc);
					z &= _mm256_testz_si256(a[i], maskz);
				}
		}
		else
		{
			int bit = 1 << (id - 8);
			if (neg(a))
				for (; (c || z) && i < L; i++)
				{
					c &= _mm256_testc_si256(a[i], i & bit ? _mm256_setzero_si256() : _mm256_set1_epi32(-1));
					z &= _mm256_testc_si256(a[i], i & bit ? _mm256_set1_epi32(-1) : _mm256_setzero_si256());
				}
			else
				for (; (c || z) && i < L; i++)
				{
					c &= _mm256_testz_si256(a[i], i & bit ? _mm256_setzero_si256() : _mm256_set1_epi32(-1));
					z &= _mm256_testz_si256(a[i], i & bit ? _mm256_set1_epi32(-1) : _mm256_setzero_si256());
				}
		}
		return {c, z};
	}
}

FINLINE constexpr __m256i const &const_expr::operator[](int i) const noexcept
{
	return subscript(*this, i);
}
FINLINE const_expr::operator bool() const noexcept
{
	return as_bool(*this);
}
FINLINE constexpr const_expr::operator mut_expr() const noexcept
{
	return {x};
}
FINLINE constexpr __m256i &mut_expr::operator[](int i) const noexcept
{
	return subscript(*this, i);
}
FINLINE mut_expr::operator bool() const noexcept
{
	return as_bool(*this);
}
FINLINE constexpr mut_expr::operator const_expr() const noexcept
{
	return {x};
}

FINLINE static mut_expr alc() noexcept
{
	mut_expr a{fnxt ? (ull)F[--fnxt] : (ull)nxt++};
	if (a.x >= ARENAS || neg(a) || imp(a))
		__builtin_unreachable();
	// cerr << "alc " << hex << a.x << endl;
	return a;
}
FINLINE static void dealc(const_expr) noexcept {}
FINLINE static void dealc(mut_expr a) noexcept
{
	a.x &= ~E_NEG;
	if (!imp(a))
	{
		if (a.x >= ARENAS)
			__builtin_unreachable();

		F[fnxt++] = (char)a.x;
	}
}

static inline mut_expr eval_or() noexcept;
// B -> "~"* ("(" S ")" + <variable>)

FINLINE static mut_expr eval_literal() noexcept
{
	bool flip = false;
	// skip the ~'s and determine whether there is an even or odd number of them.
	while (buf[iptr] == '~')
	{
		iptr++;
		flip = !flip;
	}
	// For "(" S ")", skip the parenthesis and recursively evaluate S.
	// For <variable>, look up its evaluation.
	mut_expr ans;
	if (buf[iptr] == '(')
	{
		iptr++;
		ans = eval_or();
	}
	else
		ans = var(ids[(int)buf[iptr]]);

	iptr++;
	return flip ? ~ans : ans;
}
// A -> B ("&" B)*
FINLINE static mut_expr eval_and() noexcept
{
	// Recursively evaluate the first B
	mut_expr ans = eval_literal();
	while (buf[iptr] == '&')
	{
		// Skip the &
		iptr++;
		// Recursively evaluate subsequent B's and update the result.
		ans = ans & eval_literal();
	}
	return ans;
}
// S -> A ("|" A)*
static inline mut_expr eval_or() noexcept
{
	// Recursively evaluate the first A
	mut_expr ans = eval_and();
	while (buf[iptr] == '|')
	{
		// Skip the |
		iptr++;
		// Recursively evaluate subsequent A's and update the result.
		ans = ans | eval_and();
	}
	return ans;
}

FINLINE static void skip_ws() noexcept
{
	while (buf[iptr] == ' ' || buf[iptr] == '\n' || buf[iptr] == '\t')
		iptr++;
}
FINLINE static void skip_expr() noexcept
{
	while (buf[iptr] != ' ' && buf[iptr] != '\n' && buf[iptr] != '\t')
		iptr++;
}

static inline void run_ur() noexcept
{
	int bit		 = 1;
	int ur_stack = 0;
	while (bit)
	{
		if (bit < 0)
			__builtin_unreachable();
		// if (bit > 8)
		// 	__builtin_unreachable();
		if (bit & (bit - 1))
			__builtin_unreachable();
		// if (bit != 1 && bit != 2 && bit != 4)
		// 	__builtin_unreachable();

		if (__builtin_expect(ur_stack & bit, 0))
		{
			ur_stack &= ~bit;
			if (buf[iptr] == 's')
			{
				iptr += 3;
				ur_stack &= ~(bit <<= 1);
			}
		}
		else
		{
			skip_ws();
			switch (buf[iptr])
			{
			case 'i':
				iptr += 3;
				skip_ws();
				skip_expr();
				iptr++;
				skip_ws();
				iptr += 5;
				ur_stack |= bit;
				ur_stack &= ~(bit <<= 1);
				break;
			case 'c':
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
				break;
			default:
				bit >>= 1;
				iptr += 2;
				break;
			}
		}
	}
}

template<bool T = true>
static inline const_expr run(const_expr st, ull mask) noexcept
{
	bool first_chkpt = !T;
	for (;;)
	{
		skip_ws();
		if (buf[iptr] == 'i')
		{
			iptr += 3;
			skip_ws();
			auto cond_if = eval_or() & st;
			iptr++;
			skip_ws();
			iptr += 5;
			run<false>(cond_if, mask);
			if (buf[iptr] == 's')
			{
				iptr += 3;
				// If cond_if and st alias, then this won't modify cond_if. Otherwise, modifying cond_if is okay.
				auto cond_else = ~mut_expr(cond_if) & st;
				run<false>(cond_else, mask);
				if (!alias(cond_else, cond_if) && !alias(cond_else, st))
					dealc(mut_expr(cond_else));
			}
			if (!alias(cond_if, st))
				dealc(mut_expr(cond_if));
		}
		else if (buf[iptr] == 'c')
		{
			if constexpr (!T)
			{
				if (first_chkpt && !bool(st))
				{
					run_ur();
					return {E_IMP | E_NEG};
				}
				if (first_chkpt)
				{
					for (int i = 0; i < K; i++)
					{
						ull bit = 1ull << i;
						if ((bit | (bit << 32)) & mask)
							continue;
						auto [c, z] = var_cz(i, st);
						if (c)
							mask |= bit;
						else if (z)
							mask |= bit << 32;
					}
					first_chkpt = false;
				}
			}
			iptr += 11;
			buf[optr++] = '>';
			for (int i = 0; i < K; i++)
			{
				ull bit = 1 << i;
				if (mask & bit)
					buf[optr++] = vars[i];
				else if (mask & (bit << 32))
					buf[optr++] = char(vars[i] | 32);
			}
			buf[optr++] = '\n';
		}
		else
			break;
	}
	iptr += 2;
}

int main()
{
#ifdef TEST
	freopen("in.txt", "r", stdin);
	freopen("out.txt", "w", stdout);
#endif

	read(STDIN_FILENO, buf, BUFS);

	int seen = 0;

	for (int i = 0; buf[i] != '\0';)
	{
		if ('A' <= buf[i] && buf[i] <= 'Z')
			seen |= 1 << (buf[i] - 'A');
		i++;
	}

	int k = 0;
	for (char c = 'A'; c <= 'Z'; c++)
		if (seen & (1 << (c - 'A')))
		{
			ids[(int)c] = k;
			vars[k++]	= c;
		}

	run({E_IMP}, 0);

	write(STDOUT_FILENO, buf, optr);
}
