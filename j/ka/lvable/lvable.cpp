#include <bits/stdc++.h>

using namespace std;
using namespace std::literals;

typedef long long ll;
typedef pair<int, int> pii;
typedef pair<ll, ll> pll;
typedef vector<int> vi;
typedef vector<ll> vll;

#define sz(C) (static_cast<int>(size(C)))
#define rep(i, a, b) for (int i = (a); i < (b); i++)
#define rrep(i, a, b) for (int i = (b); i --> (a);)

int main()
{
	cin.tie(0)->sync_with_stdio(0);
	string s;
	cin.ignore(SSIZE_MAX, '\n');
	cin >> s;
	cout << (s.contains("lv") ? 0 : s.contains('l') || s.contains('v') ? 1 : 2);
}
