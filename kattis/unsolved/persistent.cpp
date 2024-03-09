#pragma GCC optimize("O3")

#include <bits/stdc++.h>

using namespace std;

typedef vector<uint32_t> ubig;

[[gnu::always_inline]] static inline ubig &fma(ubig &A, uint32_t m, uint32_t a)
{
	uint64_t c = a;
	for (int i = 0; i < (int)A.size(); i++)
	{
		c = c + (uint64_t)A[i] * m;
		A[i] = (uint32_t)c;
		c >>= 32;
	}
	if (c)
		A.push_back((uint32_t)c);
	return A;
}
[[gnu::always_inline]] static inline ubig &operator+=(ubig &A, uint32_t b)
{
	uint64_t c = b;
	for (int i = 0; c && i < (int)A.size(); i++)
	{
		c += A[i];
		A[i] = (uint32_t)c;
		c >>= 32;
	}
	if (c)
		A.push_back((uint32_t)c);
	return A;
}
[[gnu::always_inline]] static inline ubig &operator*=(ubig &A, uint32_t b)
{
	uint64_t c = 0;
	for (int i = 0; i < (int)A.size(); i++)
	{
		c = c + (uint64_t)A[i] * b;
		A[i] = (uint32_t)c;
		c >>= 32;
	}
	if (c)
		A.push_back((uint32_t)c);
	return A;
}
[[gnu::always_inline]] static inline ubig &operator/=(ubig &A, uint32_t b)
{
	uint64_t c = 0;
	for (int i = (int)A.size() - 1; i >= 0; i--)
	{
		c = (c << 32) + A[i];
		A[i] = (uint32_t)(c / b);
		c = c % b;
	}
	if (c)
		exit(-1);
	if (!A.empty() && A.back() == 0)
		A.pop_back();
	return A;
}
[[gnu::always_inline]] static inline uint32_t operator%(ubig const &A, uint32_t b)
{
	uint64_t c = 0;
	for (int i = (int)A.size() - 1; i >= 0; i--)
		c = ((c << 32) + A[i]) % b;
	return (uint32_t)c;
}

ubig const ONE{ 1 };

int main()
{
	cin.tie(0);
	ios_base::sync_with_stdio(0);

	string s;
	ubig x;
	string ans;
	while (cin >> s, s != "-1")
	{
		if ((int)s.size() == 1)
		{
			cout << '1' << s << '\n';
			continue;
		}
		int C[10]{};

		while (s.back() == '0')
		{
			C[2]++;
			C[5]++;
			s.pop_back();
		}

		x.clear();
		for (char c : s)
			fma(x, 10, c - '0');

		int c2 = 0;
		for (int i = 0; i < (int)x.size(); i++)
		{
			if (x[i])
			{
				c2 += __builtin_ctz(x[i]);
				break;
			}
			else
				c2 += 32;
		}

		x.erase(begin(x), begin(x) + c2 / 32);
		int shamt = c2 % 32;
		if (shamt)
			for (int i = 1; i < (int)x.size(); i++)
				x[i - 1] = (x[i - 1] >> shamt) | (x[i] << (32 - shamt));
		x.back() >>= shamt;
		if (x.back() == 0)
			x.pop_back();
		C[2] += c2;
		C[8] += C[2] / 3;
		C[2] %= 3;
		C[4] += C[2] / 2;
		C[2] %= 2;

		while (x % 3486784401u == 0)
		{
			x /= 3486784401u;
			C[9] += 10;
		}
		while (x % 1977326743u == 0)
		{
			x /= 1977326743u;
			C[7] += 11;
		}
		while (x % 1220703125u == 0)
		{
			x /= 1220703125u;
			C[5] += 13;
		}

#pragma GCC unroll 4
		for (int i : {9, 7, 5, 3})
			while (x % i == 0)
			{
				x /= i;
				C[i]++;
			}
		if (x != ONE)
		{
			cout << "There is no such number.\n";
			continue;
		}

		if (C[2] && C[3])
		{
			C[2] = C[3] = 0;
			C[6] = 1;
		}
		else if (C[3] && C[4])
		{
			C[3] = C[4] = 0;
			C[2] = C[6] = 1;
		}
		ans.clear();
#pragma GCC unroll 8
		for (int i = 2; i <= 9; i++)
			while (C[i]--)
				ans += (char)(i + '0');
		if ((int)ans.size() == 1)
			cout << '1';
		cout << ans << '\n';
	}
}