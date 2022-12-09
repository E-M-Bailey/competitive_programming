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
vector<vi> C;
vector<vi> D;

int f(int k, int n) {
	if (n == 0) return 0;
	if (k == 0) return INT_MAX / 2;
	return D[k - 1][n - 1]; 
}

void row(int k, int nLo, int nHi, int iLo, int iHi) {
	if (nLo >= nHi) return;
	int n = (nLo + nHi) / 2;
	int o = -1;
	int d = INT_MAX / 2;
	int lim = min(iHi, n + 1);
	for (int i = iLo; i < lim; i++) {
		int v = f(k - 1, i) + C[i][n];
		if (v < d) {
			d = v;
			o = i;
		}
	}
	//assert(o >= 0);
	D[k - 1][n - 1] = d;
	row(k, nLo, n, iLo, o + 1);
	row(k, n + 1, nHi, o, iHi);
}

int main() {
#ifdef DEBUG
	freopen("in.txt", "r", stdin);
	freopen("out.txt", "w", stdout);
#endif
	cin.tie(0)->sync_with_stdio(0);
	cin.exceptions(cin.failbit);

	cin >> n >> k;
	{
		vector<vi> U(n, vi(n + 1));
		for (auto& UU : U) {
			for (int i = 0; i < n; i++) {
				cin >> UU[i + 1];
				UU[i + 1] += UU[i];
			}
		}
		C.resize(n + 1, vi(n + 1));
		for (int i = 0; i < n + 1; i++)
			for (int j = i + 1; j < n; j++)
				C[i][j + 1] = C[i][j] + U[j][j] - U[j][i];//Cost of [i, j + 1) = Cost of [i, j) + Cost of j w/ [i, j)
	}

	D.resize(k, vi(n));
	for (int i = 1; i <= k; i++)
		row(i, 1, n + 1, 0, n);
	
	cout << f(k, n);
}
// test: g++ -DDEBUG -g -O2 -std=gnu++17 -static <file> && ./a.out