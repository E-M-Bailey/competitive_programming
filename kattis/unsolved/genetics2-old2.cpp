#pragma GCC optimize("Ofast,no-stack-protector,unroll-loops")
#pragma GCC target("sse,sse2,sse3,ssse3,sse4,sse4.1,sse4.2,popcnt,abm,mmx,avx,avx2,fma,tune=native")

#include <bits/stdc++.h>
#include <immintrin.h>
#include <nmmintrin.h>

using namespace std;

typedef unsigned long long ull;
typedef unsigned		   ul;

#define BUFS (5u << 22)
#define MAXN 4104

#include "genetics2.h"

char BUF[BUFS];

#define ASSUME_NOT(C)                                                                                                  \
	if (C)                                                                                                             \
	__builtin_unreachable()

// Intentionally leaks memory
template<int M>
static inline void solve(int n, int m, int k, int pos)
{
	ASSUME_NOT(n < 3);
	ASSUME_NOT(n > 4100);
	ASSUME_NOT(m < 3);
	ASSUME_NOT(m > 4100);
	ASSUME_NOT(k < 1);
	ASSUME_NOT(k > m);
	ASSUME_NOT(m > 256 * M);
	ASSUME_NOT(m <= 256 * (M - 1));
	ASSUME_NOT(pos < 6);
	ASSUME_NOT(pos > 15);

	int *__restrict P	  = (int *)aligned_alloc(256, MAXN * sizeof(int));
	__m256i *__restrict A = (__m256i *)aligned_alloc(256, 2 * MAXN * M * sizeof(__m256i));

	alignas(1024) static constexpr int R[MAXN] RDEF;

	for (int i = 1; i < n; i++)
	{
		int r = R[i];
		ASSUME_NOT(r < 0);
		ASSUME_NOT(r > i);
		P[i] = P[r];
		P[r] = i;
	}

	__m256i const popcnt0 = _mm256_setr_epi8(
		0, 1, 1, 2, 1, 2, 2, 3, 1, 2, 2, 3, 2, 3, 3, 4, 0, 1, 1, 2, 1, 2, 2, 3, 1, 2, 2, 3, 2, 3, 3, 4);
	__m256i const popcnt1 = _mm256_sub_epi8(_mm256_setzero_si256(), popcnt0);
	__m256i const lo_mask = _mm256_set1_epi8(0x0f);
	__m256i const midpt	  = _mm256_set1_epi8((char)128);

	__m256i const ones		  = _mm256_set1_epi64x(-1);
	__m256i const fmask_shamt = _mm256_setr_epi64x(63, 127, 191, 255);
	__m256i const ones_cnt	  = _mm256_set1_epi64x((m - 1) & 255);
	__m256i const fmask		  = _mm256_srlv_epi64(ones, _mm256_subs_epu16(fmask_shamt, ones_cnt));

	__m256i d0, d1, d2, d3, d4, d5, d6, d7;
	__m256i x0, x1, x2, x3, x4, x5, x6, x7;
	__m256i y0, y1, y2, y3, y4, y5, y6, y7;
	__m256i a0, a1;
	__m256i b0, b1;
	__m256i o0, o1;
	__m256i lo0, lo1;
	__m256i hi0, hi1;
	__m256i sum0, sum1, sum2, sum3;
	__m256i sum256;
	__m128i sum128;

	for (int i = 0; i < n; i++)
	{
		int p					= P[i];
		__m256i *__restrict pal = (__m256i *)&BUF[pos + p * (m + 1)];
		__m256i *__restrict AA	= A + i * M;
		__m256i *__restrict BB	= AA + MAXN * M;

#pragma GCC ivdep
#pragma GCC unroll 17
		for (int l = 0; l < M; l++)
		{
			d0 = _mm256_loadu_si256(pal + l * 8 + 0);
			d1 = _mm256_loadu_si256(pal + l * 8 + 1);
			d2 = _mm256_loadu_si256(pal + l * 8 + 2);
			d3 = _mm256_loadu_si256(pal + l * 8 + 3);
			d4 = _mm256_loadu_si256(pal + l * 8 + 4);
			d5 = _mm256_loadu_si256(pal + l * 8 + 5);
			d6 = _mm256_loadu_si256(pal + l * 8 + 6);
			d7 = _mm256_loadu_si256(pal + l * 8 + 7);

			x0 = _mm256_slli_epi16(d0, 6);
			x1 = _mm256_slli_epi16(d1, 6);
			x2 = _mm256_slli_epi16(d2, 6);
			x3 = _mm256_slli_epi16(d3, 6);
			x4 = _mm256_slli_epi16(d4, 6);
			x5 = _mm256_slli_epi16(d5, 6);
			x6 = _mm256_slli_epi16(d6, 6);
			x7 = _mm256_slli_epi16(d7, 6);

			y0 = _mm256_slli_epi16(d0, 5);
			y1 = _mm256_slli_epi16(d1, 5);
			y2 = _mm256_slli_epi16(d2, 5);
			y3 = _mm256_slli_epi16(d3, 5);
			y4 = _mm256_slli_epi16(d4, 5);
			y5 = _mm256_slli_epi16(d5, 5);
			y6 = _mm256_slli_epi16(d6, 5);
			y7 = _mm256_slli_epi16(d7, 5);

			AA[l] = _mm256_setr_epi32(_mm256_movemask_epi8(x0),
									  _mm256_movemask_epi8(x1),
									  _mm256_movemask_epi8(x2),
									  _mm256_movemask_epi8(x3),
									  _mm256_movemask_epi8(x4),
									  _mm256_movemask_epi8(x5),
									  _mm256_movemask_epi8(x6),
									  _mm256_movemask_epi8(x7));
			BB[l] = _mm256_setr_epi32(_mm256_movemask_epi8(y0),
									  _mm256_movemask_epi8(y1),
									  _mm256_movemask_epi8(y2),
									  _mm256_movemask_epi8(y3),
									  _mm256_movemask_epi8(y4),
									  _mm256_movemask_epi8(y5),
									  _mm256_movemask_epi8(y6),
									  _mm256_movemask_epi8(y7));
		}

		AA[M - 1] = _mm256_and_si256(AA[M - 1], fmask);
		BB[M - 1] = _mm256_and_si256(BB[M - 1], fmask);
	}

	ull *__restrict bad	 = (ull *)calloc(4161u * 4160u / 64, 8);
	ull *__restrict seen = bad + 4160u / 64;

	for (int i = 0; i < n; i++)
	{
		ull mi = 1ull << i % 64;
		ul	ii = i * (4160u / 64u);
		if (bad[i / 64] & mi)
			continue;
		bool badi			   = false;
		__m256i *__restrict Ai = A + i * M;
		__m256i *__restrict Bi = Ai + MAXN * M;

		for (int j = 0; j < n; j++)
		{
			ull mj = 1ull << j % 64;
			if (i == j || (seen[ii + j / 64] & mj))
				continue;
			seen[j * (4160u / 64u) + i / 64] |= mi;

			sum0				   = midpt;
			sum1				   = midpt;
			sum2				   = _mm256_setzero_si256();
			sum3				   = _mm256_setzero_si256();
			__m256i __restrict *Aj = A + j * M;
			__m256i __restrict *Bj = Aj + MAXN * M;
#pragma GCC unroll 8
			for (int p = 0; p < M; p += 2)
			{
				a0	 = _mm256_xor_si256(Ai[p + 0], Aj[p + 0]);
				b0	 = _mm256_xor_si256(Bi[p + 0], Bj[p + 0]);
				o0	 = _mm256_or_si256(a0, b0);
				lo0	 = _mm256_and_si256(o0, lo_mask);
				hi0	 = _mm256_and_si256(_mm256_srli_epi16(o0, 4), lo_mask);
				sum0 = _mm256_add_epi8(sum0, _mm256_shuffle_epi8(popcnt0, lo0));
				sum1 = _mm256_add_epi8(sum1, _mm256_shuffle_epi8(popcnt1, hi0));
				if (p + 1 >= M)
					break;
				a1	 = _mm256_xor_si256(Ai[p + 1], Aj[p + 1]);
				b1	 = _mm256_xor_si256(Bi[p + 1], Bj[p + 1]);
				o1	 = _mm256_or_si256(a1, b1);
				lo1	 = _mm256_and_si256(o1, lo_mask);
				hi1	 = _mm256_and_si256(_mm256_srli_epi16(o1, 4), lo_mask);
				sum2 = _mm256_add_epi8(sum2, _mm256_shuffle_epi8(popcnt0, hi1));
				sum3 = _mm256_add_epi8(sum3, _mm256_shuffle_epi8(popcnt1, lo1));
			}
			sum256		= _mm256_sad_epu8(_mm256_add_epi8(sum0, sum2), _mm256_add_epi8(sum1, sum3));
			sum128		= _mm_add_epi64(_mm256_castsi256_si128(sum256), _mm256_extracti128_si256(sum256, 1));
			long long c = _mm_cvtsi128_si64(sum128) + _mm_extract_epi64(sum128, 1);

			ASSUME_NOT(c < 0);
			ASSUME_NOT(c > m);
			if ((int)c != k)
			{
				badi = true;
				bad[j / 64] |= mj;
				break;
			}
		}
		if (badi)
			bad[i / 64] |= mi;
		else
		{
			printf("%d", P[i] + 1);
			return;
		}
	}
	__builtin_unreachable();
}

// static inline void shuf(int P[MAXN], int n, mt19937_64 &randy)
// {
//  ull i = 1;
//  if (n % 2 == 0)
//  {
//      if (!unif1(2, randy))
//          swap(P[0], P[1]);
//      i = 2;
//  }
//  while (i != n)
//  {
//      ull rnd = unif1((i + 1) * (i + 2), randy);
//      swap(P[i], P[rnd / (i + 2)]);
//      swap(P[i + 1], P[rnd % (i + 2)]);
//      i += 2;
//  }
// }
#ifdef GEN
static inline ull unif1(ull lim, mt19937_64 &randy)
{
	__uint128_t ans = randy() * __uint128_t(lim);
	ull			lo	= ull(ans);
	if (lo < lim)
		while (lo < -lim % lim)
		{
			ans = randy() * __uint128_t(lim);
			lo	= ull(ans);
		}
	return ull(ans >> 64);
}
void gen()
{
	ofstream   os("genetics2.h");
	mt19937_64 randy(SEED);
	// for (int k = 0; k < 1; k++)
	// {
	int RR[MAXN]{};
	// int    i = 1;
	// if (n % 2 == 0)
	for (int i = 1; i < MAXN; i++)
		RR[i] = uniform_int_distribution<int>(0, i - 1)(randy);
	os << "#define RDEF ";
	for (ull i = 0; i < MAXN; i++)
		os << (i ? ',' : '{') << RR[i];
	os << "}\n";
	// }
	os << "#define SEED " << SEED + 1 << "ull";
}
#endif

int main()
{
#ifdef GEN
	gen();
#else
	fread(BUF, 1, BUFS, stdin);

	int n = 0, m = 0, k = 0, pos = 0;
	do
		n = int(10 * n + BUF[pos] - '0');
	while (BUF[++pos] != ' ');
	pos++;
	do
		m = int(10 * m + BUF[pos] - '0');
	while (BUF[++pos] != ' ');
	pos++;
	do
		k = int(10 * k + BUF[pos] - '0');
	while (BUF[++pos] != '\n');
	pos++;

	switch ((m + 255) / 256)
	{
#define C(a)                                                                                                           \
	case a:                                                                                                            \
		solve<a>(n, m, k, pos);                                                                                        \
		break;
#define C4(a) C(a) C(a + 1) C(a + 2) C(a + 3)
		C4(1)
		C4(5)
		C4(9)
		C4(13)
		C(17)
#undef C4
#undef C
	}
#endif
}
