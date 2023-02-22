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

int n, k;
ll m;
vector<pll> A;
pll get(int i, int j) {
	return { i < 0 ? -1 : A[i].first, j < 0 ? -1 : A[j].second };
}
ll cost(int i, int j) {
	auto [s, t] = get(i, j);
	ll d = t - s + 1;
	return d * d;
}
ll overlap(int i) {
	auto [s, t] = get(i, i - 1);
	if (s >= t) return 0;
	ll d = t - s + 1;
	return d * d;
}
int main() {
#ifdef DEBUG
	freopen("in.txt", "r", stdin);
	freopen("out.txt", "w", stdout);
#endif
	cin.tie(0)->sync_with_stdio(0);
	cin.exceptions(cin.failbit); // remove for weird input formats
	cin >> n >> m >> k;
	A.resize(n);

	for (auto& [s, t] : A) {
		cin >> s >> t;
		if (s > t) swap(s, t);
	}
	sort(all(A), [](const pii& l, const pii& r) {return l.first != r.first ? l.first < r.first : l.second > r.second;});
	{
		int j = 0;
		ll t = -1;
		for (int i = 0; i < n; i++)
			if (A[i].second > t) {
				A[j++] = A[i];
				t = A[i].second;
			}
		A.resize(n = j);
	}

	ll lo = 0, hi = m * m
}
// test: g++ -DDEBUG -g -O2 -std=gnu++17 -static <file> && ./a.out