#include <bits/stdc++.h>

using namespace std;

#define sz(C)		 (int(size(C)))
#define all(C)		 begin(C), end(C)
#define rep(i, a, b) for (int i = (a); i < (b); i++)

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

template<class T>
struct RMQ
{
	vector<vector<T>> jmp;
	RMQ(const vector<T> &V) : jmp(1, V)
	{
		for (int pw = 1, k = 1; pw * 2 <= sz(V); pw *= 2, ++k)
		{
			jmp.emplace_back(sz(V) - pw * 2 + 1);
			rep(j, 0, sz(jmp[k])) jmp[k][j] = max(jmp[k - 1][j], jmp[k - 1][j + pw]);
		}
	}
	T query(int a, int b)
	{
		assert(a < b); // or return inf if a == b
		int dep = 31 - __builtin_clz(b - a);
		return max(jmp[dep][a], jmp[dep][b - (1 << dep)]);
	}
};

void go()
{
	string s;
	cin >> s;
	int			n = (int)size(s);
	vector<int> A(n + 1);
	for (int i = 0; i < n; i++)
		A[i + 1] = A[i] + (s[i] == '(' ? 1 : -1);
	RMQ<int> R(A);
	int		 m = R.query(0, n + 1) + 1;

	vector<vector<int>> I(m);
	for (int i = 0; i < n; i++)
		I[A[i]].push_back(i);

	long long ans = 0;
	for (int d = 0; d < m; d++)
	{
		int run = 0;
		for (int k = 1; k < (int)size(I[d]); k++)
		{
			int i = I[d][k - 1], j = I[d][k];
			if (R.query(i, j) <= 2 * d)
				run++;
			else
				run = 0;
			ans += run;
		}
	}
	cout << ans << '\n';
}
