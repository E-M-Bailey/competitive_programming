#include <bits/stdc++.h>

using namespace std;
namespace rng = ranges;

using floa_t = double;
static constexpr floa_t LEN = 1e8l;

static inline floa_t eval(int n, vector<pair<floa_t, floa_t>> const &ST)
{
	floa_t best = numeric_limits<floa_t>::infinity();
	floa_t ts = 0, tt = 0;
	for (int l = 0, r = 0; l < n; ts -= ST[l].first, tt -= ST[l].second, ++l)
	{
		while (r < n && ts < 0.999999e8l)
		{
			ts += ST[r].first;
			tt += ST[r++].second;
		}
		if (ts < 0.999999e8l)
			break;

		auto const [ds, dt] = ST[r - 1];
		best = min(best, tt + dt * (1e8 - ts) / ds);
	}
	return best;
}

int main()
{
	cin.tie(0)->sync_with_stdio(0);
	int n;
	cin >> n;
	vector<pair<floa_t, floa_t>> ST;
	ST.reserve(n);
	{
		int64_t px = 0, py = 0, pt = 0;
		for (int i = 0; i < n; ++i)
		{
			floa_t x, y, t;
			cin >> x >> y >> t;
			x = round(x * 1e6l);
			y = round(y * 1e6l);
			t = round(t * 1e6l);
			const floa_t ds = hypot(x - exchange(px, x), y - exchange(py, y));
			ST.emplace_back(ds, t - exchange(pt, t));
		}
	}

	floa_t const fwd = eval(n, ST);
	rng::reverse(ST);
	floa_t const bwd = eval(n, ST);
	cout << fixed << setprecision(8) << min(fwd, bwd) * 1e-6l;
}
