#include <bits/stdc++.h>

using namespace std;

#define sz(C) (int(size(C)))
#define all(C) begin(C), end(C)

void go();

int main(int argc, char const *argv[])
{
	if (argc > 1)
	{
		ignore = freopen(argv[1], "r", stdin);
		ignore = freopen(argv[2], "w", stdout);
	}
	cin.tie(0)->sync_with_stdio(0);

	int tc = 1;
	cin >> tc;
	while (tc--)
		go();
}

typedef long long ll;

constexpr ll M = 1000000007;

vector<ll> F{1};

ll mpow(ll a, ll b)
{
	ll ans = 1;
	if ((a %= M) < 0)
		a += M;
	if ((b %= M - 1) < 0)
		b += M - 1;
	for (; b; a = a * a % M, b /= 2)
		if (b % 2)
			ans = ans * a % M;
	return ans;
}

void go()
{
	int n, k;
	cin >> n >> k;
	for (int i = (int)size(F); i <= n + k; i++)
		F.push_back(F.back() * i % M);
	
	ll ans = 0;
	for (int s = 0; s <= (n + k - 1) / k; s++)
		ans = (ans + F[n - (s - 1) * (k - 1)] * F[n - s] % M * mpow(F[n - 1 - (s - 1) * k] * F[n], -1)) % M;
	cout << ans << '\n';
}
