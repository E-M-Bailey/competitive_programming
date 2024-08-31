#include <bits/stdc++.h>

using namespace std;

#define sz(C)  (int(size(C)))
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

void go()
{
	int	   n, k;
	string s;
	cin >> n >> k >> s;

	vector<pair<bool, int>> R;
	for (int i = 0; i < n; i++)
	{
		bool c = s[i] == '1';
		if (R.empty() || R.back().first != c)
			R.emplace_back(c, 0);
		R.back().second++;
	}

	int			m = (int)size(R);
	vector<int> I;
	for (int i = 0; i < m; i++)
		if (R[i].second != k)
			I.push_back(i);

	if (I.empty())
	{
		cout << n << '\n';
		return;
	}
	if (size(I) == 1)
	{
		R.emplace_back(!R.back().first, 0);
		I.push_back(m++);
	}
	if (size(I) == 2 && R[I[0]].second > k)
	{
		R.insert(begin(R) + I[0], R[I[0]]);
		R[I[0]].second -= k;
		R[I[0] + 1].second = k;
		I[1]++;
		m++;
	}
	if (I.size() != 2 || R[I[0]].first != R[I[1]].first || R[I[0]].second + R[I[1]].second != k || I.back() != m - 1)
	{
		cout << "-1\n";
		return;
	}
	cout << I[0] * k + R[I[0]].second << '\n';
}
