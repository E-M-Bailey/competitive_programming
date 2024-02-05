#include <bits/stdc++.h>
using namespace std;

#pragma GCC optimize("Ofast,unroll-loops")
#pragma GCC target("avx2,bmi,bmi2,lzcnt,popcnt")

using u16		= uint16_t;
using u32		= uint32_t;
using u64		= uint64_t;
constexpr u32 B = 1'000'000'000, MAXP = 940'198;
constexpr u16 D = 9, MAXN = 5000, MAXQ = 1000, MAXD = 377;

u32	 S[MAXP];
u32	 I[MAXN + 2];
u32	 C[MAXD];
bool V[MAXN + 1];
u16	 N[MAXQ];

u16 rd()
{
	u16 ans = 0;
	for (int c = getchar_unlocked(); c != '\n'; c = getchar_unlocked())
		ans = static_cast<u16>(10 * ans + c - '0');
	return ans;
}

void pt(u32 x)
{
	u32 m = B / 10;
	while (x < m)
		m /= 10;
	do
		putchar_unlocked(x / m + '0');
	while (x %= m, m /= 10);
}
void pt0(u32 x)
{
	u32 m = B / 10;
	do
		putchar_unlocked(x / m + '0');
	while (x %= m, m /= 10);
}

int main()
{
	ios_base::sync_with_stdio(0);
	cin.tie(0);

	u16 q	 = rd();
	u16 maxn = 0;
	for (u16 i = 0; i < q; i++)
	{
		u16 &n = N[i] = rd();
		V[n]		  = true;
		if (n > maxn)
			maxn = n;
	}

	u16 cback = 1;
	u32 s	  = 1;
	S[0] = C[0] = 1;
	I[0]		= 0;
	u64 y = 2, z = 2;
	for (u16 n = 1; n <= maxn; ++n, y += 4, ++z)
	{
		I[n]	= s;
		u64 car = 0;
		u16 c	= 0;
		while (c != cback)
		{
			car += C[c] * y;
			C[c++] = static_cast<u32>(car % B);
			car /= B;
		}
		if (car)
		{
			C[c++] = static_cast<u32>(car);
			++cback;
			car = 0;
		}
		while (c)
		{
			(car *= B) += C[--c];
			C[c] = static_cast<u32>(car / z);
			car %= z;
		}
		cback = static_cast<u16>(cback - !C[cback - 1]);
		if (V[n])
			while (c != cback)
				S[s++] = C[c++];
	}
	I[maxn + 1] = s;

	for (u16 i = 0; i < q; i++)
	{
		u16 n = N[i];
		u32 t = I[n + 1] - 1;
		pt(S[t]);
		while (t != I[n])
			pt0(S[--t]);
		putchar_unlocked('\n');
	}
}
