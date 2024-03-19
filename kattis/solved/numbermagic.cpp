#include <bits/stdc++.h>

using namespace std;

typedef unsigned long long ull;

ull constexpr TEN[20]{
	1ull,
	10ull,
	100ull,
	1000ull,
	10000ull,
	100000ull,
	1000000ull,
	10000000ull,
	100000000ull,
	1000000000ull,
	10000000000ull,
	100000000000ull,
	1000000000000ull,
	10000000000000ull,
	100000000000000ull,
	1000000000000000ull,
	10000000000000000ull,
	100000000000000000ull,
	1000000000000000000ull,
	10000000000000000000ull,
};
ull constexpr ELEVEN[20]{
	1ull,
	11ull,
	111ull,
	1111ull,
	11111ull,
	111111ull,
	1111111ull,
	11111111ull,
	111111111ull,
	1111111111ull,
	11111111111ull,
	111111111111ull,
	1111111111111ull,
	11111111111111ull,
	111111111111111ull,
	1111111111111111ull,
	11111111111111111ull,
	111111111111111111ull,
	1111111111111111111ull,
	11111111111111111111ull,
};

int dig_idx(ull x)
{
	return int(upper_bound(begin(TEN), end(TEN), x) - TEN - 1);
}

void frwd(int ops, ull cur, vector<ull> &out)
{
	out.push_back(cur);
	if (ops == 0)
	{
		return;
	}

	if (cur > 1)
		frwd(ops - 1, cur / 2, out);
	frwd(ops - 1, cur + ELEVEN[dig_idx(cur)], out);
}

void try_eleven(int ops, ull cur, vector<ull> &out, int di);

void bkwd(int ops, ull cur, vector<ull> &out)
{
	out.push_back(cur);
	if (ops == 0)
	{
		return;
	}

	bkwd(ops - 1, cur * 2, out);
	bkwd(ops - 1, cur * 2 + 1, out);

	int di = dig_idx(cur);
	try_eleven(ops, cur, out, di);
	try_eleven(ops, cur, out, di - 1);
}

void try_eleven(int ops, ull cur, vector<ull> &out, int di)
{
	if (di < 0 || di >= 19)
		return;

	ull e = ELEVEN[di];
	if (cur <= e + 1 || dig_idx(cur - e) != di)
		return;
	bkwd(ops - 1, cur - e, out);
}

int main()
{
	ull n;
	int q;
	cin >> n >> q;

	vector<ull> A, B;
	frwd(24, n, A);
	unordered_set<ull> AS(begin(A), end(A));

	while (q--)
	{
		ull m;
		cin >> m;
		bkwd(8, m, B);
		bool fnd = 0;
		for (ull b : B)
			fnd |= AS.find(b) != end(AS);
		cout << (fnd ? "YES\n" : "NO\n");
		B.clear();
	}
}
