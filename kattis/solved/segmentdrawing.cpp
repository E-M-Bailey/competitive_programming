#include <bits/stdc++.h>

using namespace std;

constexpr bool ccw(int x1, int y1, int x2, int y2, int x3, int y3) noexcept
{
	return int64_t(x3 - x2) * (y2 - y1) < int64_t(x2 - x1) * (y3 - y2);
}

struct hull
{
	struct edge
	{
		int			   x, y;
		mutable int	   dx, dy;
		constexpr void fix(int x2, int y2) const noexcept
		{
			dx = x2 - x;
			dy = y2 - y;
		}
		constexpr friend bool ccw(edge a, edge b) noexcept
		{
			return int64_t(b.dx) * a.dy < int64_t(a.dx) * b.dy;
		}
	};

	struct cmp
	{
		typedef void is_transparent;

		constexpr bool operator()(edge l, edge r) const noexcept
		{
			return l.y < r.y;
		}
		constexpr bool operator()(edge e, int y) const noexcept
		{
			return e.y < y;
		}
		constexpr bool operator()(edge e, pair<int, int> pt) const noexcept // tangent query
		{
			auto [x, y] = pt;
			return int64_t(x - e.x) * e.dy < int64_t(y - e.y) * e.dx;
		}
	};

	set<edge, cmp> S{};

	void add(int x, int y)
	{
		auto nxt = S.lower_bound(y);
		if (nxt != end(S) && nxt->y == y)
		{
			if (nxt->x >= x)
				return;
			nxt = S.erase(nxt);
		}

		if (nxt != begin(S) && nxt != end(S) && !ccw(prev(nxt)->x, prev(nxt)->y, x, y, nxt->x, nxt->y))
			return;

		int	 dx = nxt == end(S) ? -1 : nxt->x - x;
		int	 dy = nxt == end(S) ? 0 : nxt->y - y;
		auto it = S.insert(nxt, {x, y, dx, dy});
		if (it != begin(S))
		{
			prev(it)->fix(x, y);
			for (;;)
			{
				auto prv = prev(it);
				if (prv == begin(S))
					break;
				auto prv2 = prev(prv);
				if (ccw(*prv2, *prv))
					break;
				S.erase(prv);
				prv = prv2;
				prv->fix(x, y);
			}
		}
		if (nxt != end(S))
			while (!ccw(*it, *nxt))
			{
				nxt = S.erase(nxt);
				if (nxt == end(S))
				{
					it->dx = -1;
					it->dy = 0;
					break;
				}
				it->fix(nxt->dx, nxt->dy);
			}
	}

	double query(int x, int y)
	{
		auto it = S.lower_bound(pair{x, y});
		if (it == end(S))
			return -numeric_limits<double>::infinity();
		else
			return x + double(it->x - x) * y / (y - it->y);
	}
};

void solve(int n, int k, vector<pair<int, int>> const &A, vector<int> const &Y, vector<double> &L)
{
	vector<vector<hull>> T;
	T.emplace_back(k);
	while (size(T.back()) > 1)
		T.emplace_back((size(T.back()) + 1) / 2);
	int m = (int)size(T);

	for (int i = 0; i < n; i++)
	{
		auto [x, j] = A[i];
		int y		= Y[j];
		for (int l = 0, pos = j; pos; l++, pos /= 2)
			L[i] = max(L[i], T[l][pos - 1].query(x, y));
		for (int l = 0, pos = j; l < m; l++, pos /= 2)
			T[l][pos].add(x, y);
	}
}

int main()
{
	int n;
	cin >> n;
	vector<int>			   Y(n);
	vector<pair<int, int>> A(n);
	vector<double>		   L(n), R(n);
	for (int i = 0; i < n; i++)
	{
		auto &[x, y] = A[i];
		cin >> x >> y >> L[i] >> R[i];
		R[i] = R[i];
		Y[i] = y;
	}
	sort(begin(Y), end(Y));
	Y.erase(unique(begin(Y), end(Y)), end(Y));
	for (auto &[x, j] : A)
		j = int(lower_bound(begin(Y), end(Y), j) - begin(Y));
	int k = (int)size(Y);

	solve(n, k, A, Y, L);
	
	for (auto &[x, y] : A)
		x = -x;
	for (auto &r : R)
		r = -r;
	reverse(begin(A), end(A));
	reverse(begin(R), end(R));
	solve(n, k, A, Y, R);
	reverse(begin(R), end(R));
	reverse(begin(A), end(A));
	for (auto &r : R)
		r = -r;
	for (auto &[x, y] : A)
		x = -x;

	double ans = 0;

	for (int i = 0; i < n; i++)
	{
		double l = L[i], r = R[i], x = A[i].first, y = Y[A[i].second];
		if (l > r + 1e-9)
		{
			cout << -1;
			return 0;
		}
		ans += hypot(clamp(x, l, r) - x, y);
	}
	cout << fixed << setprecision(8) << ans;
}
