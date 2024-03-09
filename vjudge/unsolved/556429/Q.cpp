#include <bits/stdc++.h>

using namespace std;

int n;
vector<int> P;

int solve()
{
	vector<bool> D(n);
	for (int i = 0; i < n; i++)
	{
		int d = (P[i] + n - i) % n;
		D[d] = true;
	}

	deque<int> R, L;
	for (int d = 0; d <= n / 2; d++)
		if (D[d])
			R.push_back(d);
	for (int d = n / 2 + 1; d < n; d++)
		if (D[d])
			L.push_back(n - d);

	int dr = 0, dl = 0;
	int ans = INT_MAX;
	for (int i = 0; i < n; i++)
	{
		int cr = R.empty() ? 0 : R.back() + dr;
		int cl = L.empty() ? 0 : L.front() + dl;
		ans = min(ans, max(cr, cl));
		dr++;
		dl--;
		if (!R.empty() && R.back() + dr == n / 2 + 1)
		{
			L.push_front((n + 1) / 2 - 1 - dl);
			R.pop_back();
		}
		if (!L.empty() && L.back() + dl == 0)
		{
			R.push_front(-dr);
			L.pop_back();
		}
	}
	return ans;
}

int main(int argc, char const *argv[])
{
	if (argc > 2)
	{
		ignore = freopen(argv[1], "r", stdin);
		ignore = freopen(argv[2], "w", stdout);
	}

	cin >> n;
	P.resize(n);
	for (int &p : P)
	{
		cin >> p;
		p--;
	}

	int ans = solve();
	reverse(begin(P), end(P));
	ans = min(ans, solve());
	cout << ans;
}