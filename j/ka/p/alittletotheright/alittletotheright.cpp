#pragma GCC optimize("O3,unroll-loops")
#pragma GCC target("avx2,bmi,bmi2,lzcnt,popcnt")

#include <bits/stdc++.h>

using namespace std;

static constexpr int P = 8'191, A = 1'009;

using u16 = uint16_t;
using u64 = uint64_t;

static constinit int C[50'000]{};
static constinit u64 B[15'625]{};
static constinit u16 F[1'000'000]{};
static constinit bitset<P> H{};
static constinit int n, p, K = 0;

int main()
{
	cin.tie(0)->sync_with_stdio(0);
	cin >> n >> p;
	for (int i = 0, j = 0; i < n; j += n, j = j < p * n ? j : ++i)
	{
		cin >> C[j];
		--C[j];
	}

	int res = 0;
	for (int i = 0; i < p * n; i += n)
	{
		bool dup = false;
		for (int j = i; !dup && j < i + n; ++j)
		{
			auto bit = u64{ 1 } << (C[j] % 64);
			u64 &b = B[C[j] / 64];
			dup = exchange(b, b | bit) & bit;
		}
		if (dup)
		{
			memset(B, 0, sizeof(B));
			continue;
		}

		int h = 0;

		for (int s = 0, j = 0; j < size(B); ++j)
			for (u64 b = B[j]; b; b &= b - 1) [[unlikely]]
			{
				int c = j * 64 + __builtin_ctzll(b);
				F[c] = s++;
			}

		for (int j = i; j < i + n; ++j)
		{
			C[j] = F[C[j]];
			h = (A * h + C[j]) % P;
		}

		for (int j = 0; j < size(B); ++j)
		{
			if (B[j] == 0) [[likely]]
				continue;
			memset(F + j * 64, 0, 64 * sizeof(F[0]));
			B[j] = 0;
		}

		res += !H.test(h);
		H.set(h);
	}

	cout << res;
}
