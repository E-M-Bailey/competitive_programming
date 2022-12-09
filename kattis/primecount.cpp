#include <bits/stdc++.h>
using namespace std;
constexpr int64_t MAXN = 100'000'000'000ll;
constexpr int64_t MAXS = 24'000'000ll;
vector<int64_t> P;
array<bool, MAXS> C{};
array<int64_t, MAXS> PI{};
void sieve()
{
	P.reserve(MAXS);
	PI[0] = PI[1] = 0;
	for (int64_t i = 2; i < MAXS; i++)
	{
		PI[i] = PI[i - 1] + !C[i];
		if (C[i]) continue;
		P.push_back(i);
		for (int64_t j = i * 2; j < MAXS; j += i)
			C[j] = true;
	}
}
int64_t p2(int64_t x, int64_t sx, int64_t a)
{
	int64_t psx = PI[sx - 1];
	//int64_t ans = (a * (a - 1) - psx * (psx - 1)) / 2;
	int64_t ans = 0;
	for (int64_t b = a + 1; b <= psx; b++) {
		int64_t p = P[b - 1];
		ans += PI[x / p] - PI[p] + 1;
	}
	return ans;
}
unordered_map<int64_t, unordered_map<int64_t, int64_t>> DP;
int64_t phi(int64_t x, int64_t a)
{
	if (x == 0 || a == 0)
		return x;
	if (DP[x].find(a) != DP[x].end())
		return DP[x][a];
	int64_t ans = phi(x, a - 1) - phi(x / P[a - 1], a - 1);
	//cerr << "phi(" << x << ',' << a << ") = " << ans << endl;
	return DP[x][a] = ans;
}
int64_t go(int64_t x)
{
	x--;
	if (x < 10)
		return PI[x];
	int64_t a = 0;
	while (a * a * a <= x)
		a++;
	a = PI[a];
	int64_t sx = 0;
	while (sx * sx <= x)
		sx++;
	sx--;
	int64_t y = phi(x, a);
	int64_t z = p2(x, sx, a);
	//cerr << a << ' ' << y << ' ' << z << endl;
	return y + a - 1 - z;
}
int main()
{
	sieve();

	//for (int64_t i = 0; i < 50; i++)
	//	cerr << PI[i] << ' ';
	//cerr << endl;
	for (int64_t x = 1; x <= 20; x++) {
		cout << x << ":" << endl;
		cout << go(x) << endl << endl;
	}

	//int64_t x;
	//cin >> x;
	//x--;
	//cout << go(x);
}

