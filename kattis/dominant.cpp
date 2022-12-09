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

struct entry {
	string s;
	array<uint8_t, 26> a;
	entry(string&& s) : s(s), a{} {
		for (char c : this->s)
			a[c - 'a']++;
	}
	friend bool operator<(const entry& l, const entry& r) {
		return sz(l.s) < sz(r.s);
	}
};

int main() {
#ifdef DEBUG
	freopen("in.txt", "r", stdin);
	freopen("out.txt", "w", stdout);
#endif
	cin.tie(0)->sync_with_stdio(0);
	vector<entry> S;
	string s;
	while (cin >> s && !s.empty())
		S.emplace_back(move(s));
	int n = sz(S);
	sort(all(S));
	vi I(12, n);
	fill(I.begin(), I.begin() + S[0].s.size(), -1);
	for (int i = n - 1; i >= 0; i--)
		I[S[i].s.size()] = i;
	for (int i = 10; i >= 0; i--)
		I[i] = min(I[i], I[i + 1]);
	//for (entry e : S)
	//	cerr << e.s.size() << ' ';
	//	cerr << endl;
	//for (int i : I)
	//	cerr << i << ' ';
	vector<bool> D(n, true);
	for (int i = 0; i < n; i++) {
		int lim = I[S[i].s.size() + 1];
		bool dd = true;
		for (int j = n - 1; dd && j >= lim; j--) {
			dd = false;
			for (int k = 0; k < 26; k++)
				if (S[i].a[k] > S[j].a[k]) {
					//if (i == 2)
					//	cerr << j << ' ' << char(k + 'a') << endl;
					dd = true;
					break;
				}
		}
		D[i] = dd;
	}
	//for (bool d : D)
	//	cerr << d << ' ';
	vector<string> ans;
	for (int i = 0; i < n; i++)
		if (D[i])
			ans.push_back(move(S[i].s));
	sort(all(ans));
	for (const string& a : ans)
		cout << a << endl;
}
// test: g++ -DDEBUG -g -O2 -std=gnu++17 -static <file> && ./a.out