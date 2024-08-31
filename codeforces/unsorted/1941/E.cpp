#include <bits/stdc++.h>

using namespace std;

#define ALL(C) begin(C), end(C)

void go();

int main(int argc, char const *argv[])
{
	cin.tie(0)->sync_with_stdio(0);
	if (argc > 1)
	{
		ignore = freopen(argv[1], "r", stdin);
		ignore = freopen(argv[2], "w", stdout);
	}
	int t;
	cin >> t;
	while (t--)
		go();
}

void go()
{
	int n, m, k, d;
	cin >> n >> m >> k >> d;
	vector<int64_t> A(n);
	for (int64_t &a : A)
	{
		cin >> a;
		deque<pair<int64_t, int>> D{{1, 0}};

		for (int i = 1; i < m; i++)
		{
			cin >> a;
			a += 1 + D.front().first;
			while (!D.empty() && D.back().first >= a)
				D.pop_back();
			D.emplace_back(a, i);
			while (D.front().second < i - d)
				D.pop_front();
		}
	}

	int64_t ans = INT64_MAX;
	for (int i = k; i <= n; i++)
		ans = min(ans, accumulate(begin(A) + i - k, begin(A) + i, (int64_t)0));

	cout << ans << '\n';
}
