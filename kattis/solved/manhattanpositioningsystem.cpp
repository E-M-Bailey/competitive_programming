#include <bits/stdc++.h>

using namespace std;

enum class tp
{
	MT,
	PT,
	PSEG,
	NSEG,
};

constexpr int NIL = INT_MIN;

struct pset
{
	tp	 t;
	int	 a, b, c;
	bool in(int x) const
	{
		switch (t)
		{
		case tp::MT:
			return false;
		case tp::PT:
			return x == a;
		case tp::PSEG:
		case tp::NSEG:
		default:
			return a <= x && x <= b;
		}
	}
	int operator()(int x) const
	{
		if (!in(x))
			return NIL;
		switch (t)
		{
		case tp::PT:
			return b;
		case tp::PSEG:
			return c + x;
		case tp::NSEG:
		default:
			return c - x;
		}
	}
	constexpr explicit pset(tp t = tp::MT, int a = 0, int b = 0, int c = 0) : t(t), a(a), b(b), c(c)
	{
		if (t == tp::PSEG || t == tp::NSEG)
		{
			if (a > b)
				this->t = tp::MT;
			else if (a == b)
			{
				this->b = (*this)(a);
				this->t = tp::PT;
			}
		}
	}
};
constexpr pset MT(tp::MT);

vector<pset> beacon(int x, int y, int d)
{
	if (d == 0)
		return {pset(tp::PT, x, y)};
	else if (d == 1)
		return {
			pset(tp::PT, x - 1, y),
			pset(tp::PT, x, y + 1),
			pset(tp::PT, x, y - 1),
			pset(tp::PT, x + 1, y),
		};
	else
		return {
			// (x - d, y) -> (x - 1, y + d - 1)
			pset(tp::PSEG, x - d, x - 1, y - x + d),
			// (x - d + 1, y - 1) -> (x, y - d)
			pset(tp::NSEG, x - d + 1, x, y + x - d),
			// (x, y + d) -> (x + d - 1, y + 1)
			pset(tp::NSEG, x, x + d - 1, y + x + d),
			// (x + 1, y - d + 1) -> (x + d, y)
			pset(tp::PSEG, x + 1, x + d, y - x - d),
		};
}

pset isect(pset a, pset b)
{
	if (a.t == tp::MT || b.t == tp::MT)
		exit(-1);
	switch (a.t)
	{
	case tp::MT:
		return MT;
	case tp::PT:
		return b(a.a) == a.b ? a : MT;
	case tp::PSEG:
		switch (b.t)
		{
		case tp::MT:
			return MT;
		case tp::PT:
			return isect(b, a);
		case tp::PSEG:
			return a.c == b.c ? pset(tp::PSEG, max(a.a, b.a), min(a.b, b.b), a.c) : MT;
		case tp::NSEG:
		default:
		{
			int x2 = b.c - a.c;
			int x  = x2 / 2;
			return x2 % 2 == 0 && a.in(x) && b.in(x) ? pset(tp::PT, x, a(x)) : MT;
		}
		}
	case tp::NSEG:
	default:
		switch (b.t)
		{
		case tp::MT:
			return MT;
		case tp::PT:
		case tp::PSEG:
			return isect(b, a);
		case tp::NSEG:
		default:
			return a.c == b.c ? pset(tp::NSEG, max(a.a, b.a), min(a.b, b.b), a.c) : MT;
		}
	}
}

void isect(const vector<pset> &A, const vector<pset> &B, vector<pset> &C)
{
	C.clear();
	for (pset a : A)
		for (pset b : B)
		{
			pset c = isect(a, b);
			if (c.t == tp::MT)
				continue;
			C.push_back(c);
		}
}

int main()
{
	cin.tie(0)->sync_with_stdio(0);
	int n;
	cin >> n;
	int x, y, d;
	cin >> x >> y >> d;
	vector<pset> S = beacon(x, y, d), S2;
	for (int i = 1; i < n; i++)
	{
		cin >> x >> y >> d;
		swap(S, S2);
		isect(S2, beacon(x, y, d), S);
	}
	if (S.empty())
		cout << "impossible";
	else if (S.size() > 1 || S[0].t != tp::PT)
		cout << "uncertain";
	else
		cout << S[0].a << ' ' << S[0].b;
}
