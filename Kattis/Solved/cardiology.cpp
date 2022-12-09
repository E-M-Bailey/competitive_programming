#include <bits/stdc++.h>
using namespace std;

#pragma GCC optimize("O3,unroll-loops")
#pragma GCC target("avx2,bmi,bmi2,lzcnt,popcnt")

#define rep(i, a, b) for (int i = a; i < (b); ++i)
#define all(x) begin(x), end(x)
#define rall(x) rbegin(x), rend(x)
#define sz(x) (int)(x).size()
typedef long long ll;
typedef pair<int, int> pii;
typedef pair<ll, ll> pll;
typedef vector<int> vi;
typedef vector<ll> vll;

template<class T> constexpr T MAX = numeric_limits<T>::max();
template<class T> constexpr T MIN = numeric_limits<T>::min();

using namespace chrono;
mt19937_64 randy(duration_cast<nanoseconds>(high_resolution_clock::now().time_since_epoch()).count());

ll getS(ll a, ll pr, ll c, ll ba, vll& D) {
	if (a == ba) return 0;
	ll i = a / c;
	if (D[i] >= 0) return D[i];
	//cerr << i << endl;
	return D[i] = 1 + getS(i + pr, pr, c, ba, D);
}

int main() {
#ifdef DEBUG
	freopen("in.txt", "r", stdin);
	freopen("out.txt", "w", stdout);
#endif
	cin.tie(0)->sync_with_stdio(0);
	cin.exceptions(cin.failbit); // remove for weird input formats

	ll r, c;
	cin >> r >> c;

	ll i0 = (r - 1) / 2, i1 = r / 2, j0 = (c - 1) / 2, j1 = c / 2;

	ll bestP = 0, bestI = 0, bestJ = 0, bestD = i0 + j0;
	for (ll p = 1; p < c; p++) {
		//cerr << p << ' ' << c << endl;
		ll i = p * r / (c - 1);
		if (p * r % (c - 1) == 0) {
			if (i == r)
				i = r - 1;
			else
				continue;
		}
		if (i >= r) break;
		ll a = i + p * r;
		ll j = a % c;
		ll d = (i <= i0 ? i0 - i : i - i1) + (j <= j0 ? j0 - j : j - j1);
		if (d < bestD) {
			//cerr << d << ' ' << bestD << endl;
			bestP = p;
			bestI = i;
			bestJ = j;
			bestD = d;
		}
	}

	ll s = 0;
	vll D(r, -1);
	//cerr << bestP + 1 << ' ' << bestI << endl;
	for (int i = 0; i < r; i++)
		s = max(s, getS(i * c + (bestJ + 1) % c, bestP * r, c, bestI + bestP * r, D));
	cout << bestP + 1 << ' ' << bestI + 1 << ' ' << bestJ + 1 << ' ' << s << endl;	
}
// test: g++ -DDEBUG -g -O2 -std=gnu++17 -static <file> && ./a.out
