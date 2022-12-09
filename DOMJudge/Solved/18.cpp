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

int main() {
#ifdef DEBUG
	freopen("in.txt", "r", stdin);
	freopen("out.txt", "w", stdout);
#endif
	cin.tie(0)->sync_with_stdio(0);
	cin.exceptions(cin.failbit); // remove for weird input formats

	int n;
	ll m;
	cin >> n >> m;
	for (int q = 2;; q++) {
		for (int p = q - 1; p >= 1; p--) {
			ll v = 0, pn = 1;
			bool safe = true;
			bool psafe = true;
			for (int i = 0; i < n; i++) {
				if (!psafe || v > (m - pn) / q) {
					safe = false;
					break;
				}
				v = v * q + pn;
				if (pn > m / p)
					psafe = false;
				pn *= p;
			}

			if (!safe && p == 1) {
				cout << "impossible";
				return 0;
			}
			if (!safe || m % v)
				continue;
			cout << (q - p) << ' ' << q;
			return 0;
		}
	}
}
// test: g++ -DDEBUG -g -O2 -std=gnu++17 -static <file> && ./a.out