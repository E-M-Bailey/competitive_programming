#include <bits/stdc++.h>

using namespace std;

void go();

int main()
{
	cin.tie(0)->sync_with_stdio(0);
	int tc = 1;
	cin >> tc;
	while (tc--)
		go();
}

void go()
{
	int n, k, q;
	cin >> n >> k >> q;

	vector<pair<int, int>> A(k + 1);
	for (int i = 1; i <= k; i++)
		cin >> A[i].first;
	for (int i = 1; i <= k; i++)
		cin >> A[i].second;

	while (q--)
	{
		long long d;
		cin >> d;
		auto r = lower_bound(begin(A), end(A), pair{(int)d, 0});
		if (r->first == d)
		{
			cout << r->second << ' ';
			continue;
		}
		auto l = prev(r);
		cout << (r->second * (d - l->first) + l->second * (r->first - d)) / (r->first - l->first) << ' ';
	}
	cout << '\n';
}
