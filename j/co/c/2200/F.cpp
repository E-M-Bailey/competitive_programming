#include <bits/extc++.h>

using namespace std;
namespace rng = ranges;

static constexpr int sz(const auto& C) noexcept
{
	return static_cast<int>(size(C));
}

using ll = long long;

static vector<ll> calc(const vector<pair<int, int>> XY, int dk)
{
	int n = sz(XY);
	priority_queue<int, vector<int>, greater<>> X;
	vector<ll> S(n + 2);
	ll s = 0;
	for (int k = n + 1, i = 0; k > 0; --k)
	{
		while (i < n && XY[i].second >= k + dk)
		{
			X.push(XY[i].first);
			s += XY[i].first;
			++i;
		}
		while (sz(X) > k)
		{
			s -= X.top();
			X.pop();
		}
		S[k] = s;
	}
	s = 0;
	for (int i = 1; i <= n + 1; ++i)
		s = S[i] = max(s, S[i]);
	return S;
}

int main()
{
	cin.tie(0)->sync_with_stdio(0);
	int T;
	cin >> T;
	while (T--)
	{
		int n, m;
		cin >> n >> m;
		vector<pair<int, int>> XY(n);
		for (auto &[x, y] : XY)
		{
			cin >> x >> y;
			++y;
		}
		rng::sort(XY, greater{}, &pair<int, int>::second);
		auto const S0 = calc(XY, 0), S1 = calc(XY, 1);

		while (m--)
		{
			int x, y;
			cin >> x >> y;
			cout << max(S0.back(), S1[y] + x) << ' ';
		}
		cout << '\n';
	}
}
