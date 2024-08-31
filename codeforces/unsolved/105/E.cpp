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
	// cin >> tc;
	while (tc--)
		go();
}

typedef tuple<array<int, 3>, bitset<6>, array<int, 3>> ent;

vector<array<int, 3>> E{{0, 0, 0},
						{2, 0, 0},
						{3, 0, 0},
						{0, 1, 0},
						{0, 3, 0},
						{0, 0, 1},
						{0, 0, 2},
						{2, 3, 0},
						{3, 0, 2},
						{3, 1, 0},
						{0, 3, 1},
						{2, 0, 1},
						{0, 1, 2}};

int F[4][4][4];

int enc(ent const &e)
{
	auto [p, u, pa] = e;
	return (p[0] << 24) | (p[1] << 17) | (p[2] << 10) | ((int)u.to_ulong() << 4) | F[pa[0] + 1][pa[1] + 1][pa[2] + 1];
}
ent dec(int x)
{
	return ent{{(x & 0x7f000000) >> 24, (x & 0x00fe0000) >> 17, (x & 0x0001fc00) >> 10},
			   bitset<6>{unsigned((x & 0x000003f0) >> 4)},
			   E[(x & 0x0000000f) >> 0]};
}

void go()
{
	auto S = new bitset<70 * 128 * 128 * 64 * 16>{};

	for (int i = 0; i < 13; i++)
		F[E[i][0]--][E[i][1]--][E[i][2]--] = i;

	int ans = 0;
	// set<ent>   S;
	queue<int> Q;

	array<int, 3> P, M, T;
	for (int i = 0; i < 3; i++)
	{
		cin >> P[i] >> M[i] >> T[i];
		P[i]--;
	}
	int st = enc(ent{P, 0, {-1, -1, -1}});
	Q.push(st);
	(*S)[st] = true;

	array<int, 70> occ;
	fill(begin(occ), end(occ), -1);
	while (!Q.empty())
	{
		int v			= Q.front();
		auto [p, u, pa] = dec(v);
		Q.pop();

		array<int, 3> ch{-1, -1, -1};
		for (int i = 0; i < 3; i++)
			if (pa[i] >= 0)
				ch[pa[i]] = i;

		ans = max(ans, *max_element(begin(p), end(p)));
		for (int i = 0; i < 3; i++)
			if (pa[i] < 0)
				occ[p[i]] = i;

		ent w{p, u, pa};
		auto &[pp, uu, paa] = w;

		for (int i = 0; i < 3; i++)
		{
			if (pa[i] >= 0)
				continue;
			if (!u[i] && ch[i] < 0)
			{
				for (int q = max(0, p[i] - M[i]); q <= p[i] + M[i]; q++)
				{
					if (occ[q] >= 0)
						continue;
					for (int j = i; j >= 0; j = ch[j])
						pp[j] = (int)q;
					uu[i] = true;
					int e = enc(w);
					if (!(*S)[e])
					{
						(*S)[e] = true;
						Q.push(e);
					}
					pp = p;
					uu = u;
				}
			}
			if (!u[i + 3] && ch[i] < 0)
			{
				for (int q : {p[i] - 1, p[i] + 1})
				{
					if (q < 0 || q >= 70 || occ[q] < 0)
						continue;
					for (int j = occ[q]; j >= 0; j = ch[j])
						pp[j] = p[i];
					paa[occ[q]] = (int)i;
					int e		= enc(w);
					if (!(*S)[e])
					{
						(*S)[e] = true;
						Q.push(e);
					}
					pp	= p;
					paa = pa;
				}
			}
			if (!u[i + 3] && ch[i] >= 0)
			{
				for (int q = max(0, p[i] - T[i]); q <= p[i] + T[i]; q++)
				{
					if (occ[q] >= 0)
						continue;
					for (int j = ch[i]; j >= 0; j = ch[j])
						pp[j] = (int)q;
					uu[i + 3]  = true;
					paa[ch[i]] = -1;
					int e	   = enc(w);
					if (!(*S)[e])
					{
						(*S)[e] = true;
						Q.push(e);
					}
					pp	= p;
					uu	= u;
					paa = pa;
				}
			}
		}

		for (int i = 0; i < 3; i++)
			occ[p[i]] = -1;
	}

	cout << ans + 1;
	// intentionally leak S
}
