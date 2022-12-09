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

vector<pii> D{ pii(0, 1), pii(1, 0), pii(0, -1), pii(-1, 0) };

int X, Y;
vector<vector<bool>> G;

struct state {
	int x, y, t = 0, s = 1;
	state(int x, int y) : x(x), y(y) {}
	void adv() {
		if (s == 0) {
			t++;
			s = t / 2;
		} else s--;
		auto [dx, dy] = D[t % 4];
		x += dx;
		y += dy;
	}
	bool get() {
		if (x < 0 || x >= X || y < 0 || y >= Y)
			return false;
		return G[x][y];
	}
};

vector<state> S;
vi T;

void rec(int* A, int n, int& s, int& M, int d = 0) {
	if (n == 0) return;
	if (n == 1) {
		s += max(0, d - 1);
		M = max(M, max(0, d - 1));
		T[*A] = max(0, d - 1);
		return;
	}
	int* B = partition(A, A + n, [](int i) {return S[i].get();});
	for (int i = 0; i < n; i++)
		S[A[i]].adv();
	int m = B - A;
	rec(A, m, s, M, d + 1);
	rec(B, n - m, s, M, d + 1);
}

int main() {
#ifdef DEBUG
	freopen("in.txt", "r", stdin);
	freopen("out.txt", "w", stdout);
#endif
	cin.tie(0)->sync_with_stdio(0);

	cin >> X >> Y;
	G.assign(X, vector<bool>(Y));
	for (int y = Y - 1; y >= 0; y--)
		for (int x = 0; x < X; x++) {
			char c;
			cin >> c;
			G[x][y] = c == 'X';
		}

	S.reserve(X * Y);
	for (int x = 0; x < X; x++)
		for (int y = 0; y < Y; y++)
			S.emplace_back(x, y);
	vi A(X * Y);
	iota(all(A), 0);
	T.resize(X * Y);
	int s = 0, M = 0;
	rec(A.data(), X * Y, s, M);
	cout << fixed << setprecision(10) << (long double)s / (X * Y) << endl << M << endl;
	for (int y = 0; y < Y; y++)
		for (int x = 0; x < X; x++)
			if (T[x * Y + y] == M)
				cout << '(' << x + 1 << ',' << y + 1 << ") ";
}
// test: g++ -DDEBUG -g -O2 -std=gnu++17 -static <file> && ./a.out