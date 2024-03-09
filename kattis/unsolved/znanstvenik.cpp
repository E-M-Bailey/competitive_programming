#pragma GCC optimize("Ofast")

#include <bits/stdc++.h>

using namespace std;

unsigned char G[1000u][1000u];
unsigned H[1000u], R, C, i, j, h, m, k;
unsigned long long BS[1u << 26];

int main()
{
	cin.tie(nullptr);
	ios_base::sync_with_stdio(false);

	cin >> R >> C;

	for (i = R; i--;)
		for (j = C; j--;)
			cin >> G[i][j];

	for (i = 0; i < R; ++i)
	{
		for (j = C; j--;)
		{
			H[j] = (unsigned)((127ull * H[j] + G[i][j]) % 4'000'000'007u);
			h = H[j] >> 6;
			m = 1u << (H[j] & 0x3fu);
			if (BS[h] & m)
				break;
			BS[h] |= m;
		}
		if (++j == 0)
			break;

		for (k = C; k-- != j;)
		{
			BS[H[k] >> 6] = 0;
		}
		for (--j; j--;)
		{
			H[j] = (unsigned)((127ull * H[j] + G[i][j]) % 4'000'000'007u);
		}
	}
	cout << R - 1 - i;
}

// hash-based solution:
/*
unsigned char G[1000u][1000u];
unsigned H[1000u], R, C, i, j, h, m, k;
unsigned long long BS[1u << 26];

int main()
{
	cin.tie(nullptr);
	ios_base::sync_with_stdio(false);

	cin >> R >> C;

	for (i = R; i--;)
		for (j = C; j--;)
			cin >> G[i][j];

	// for (j = C; j--;)
	// 	cerr << H[j] << ' ';
	// cerr << endl;
	for (i = 0; i < R; ++i)
	{
		// Jenkins's one-at-a-time hash
		for (j = C; j--;)
		{
			h = H[j] + G[i][j];
			// cerr << ' ' << j << '-' << h << '-';
			h += h << 10;
			// cerr << h << '-';
			H[j] = h ^= h >> 6;
			// cerr << h << '\n';
			h += h << 3;
			h ^= h >> 11;
			h += h << 15;
			m = 1u << (h & 0x3fu);
			h >>= 6;
			if (BS[h] & m)
				break;
			BS[h] |= m;
		}
		if (++j == 0)
			break;

		for (k = C; k-- != j;)
		{
			h = H[k];
			h += h << 3;
			h ^= h >> 11;
			h += h << 15;
			BS[h >> 6] = 0;
		}
		for (j--; j--;)
		{
			// cerr << ' ' << j << endl;
			h = H[j] + G[i][j];
			h += h << 10;
			H[j] = h ^= h >> 6;
		}
		// for (j = C; j--;)
		// 	cerr << G[i][j] << ' ' << H[j] << ' ';
		// cerr << endl;
	}
	// for (j = C; j--;)
	// 	cerr << G[i][j] << ' ' << H[j] << ' ';
	// cerr << endl;
	cout << R - 1 - i;
}
*/