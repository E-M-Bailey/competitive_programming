#include <bits/stdc++.h>

using namespace std;

typedef pair<int, int> pii;
typedef vector<int>	   vi;

#define sz(C)		 (int(size(C)))
#define rep(i, a, b) for (int i = (a); i < (b); i++)

// from KACTL
vi					num, st;
vector<vector<pii>> ed;
int					Time;
vector<int>			dep;
template<class F>
int dfs(int at, int par, F &f, int d = 0)
{
	dep[at] = d;
	int me = num[at] = ++Time, e, y, top = me;
	for (auto pa : ed[at])
		if (pa.second != par)
		{
			tie(y, e) = pa;
			if (num[y])
			{
				top = min(top, num[y]);
				if (num[y] < me)
					st.push_back(e);
			}
			else
			{
				int si = sz(st);
				int up = dfs(y, e, f, d + 1);
				top	   = min(top, up);
				if (up == me)
				{
					st.push_back(e);
					f(vi(st.begin() + si, st.end()));
					st.resize(si);
				}
				else if (up < me)
					st.push_back(e);
				else
				{ /* e is a bridge */
					f(vi{e});
				}
			}
		}
	return top;
}

template<class F>
void bicomps(F f)
{
	num.assign(sz(ed), 0);
	rep(i, 0, sz(ed)) if (!num[i]) dfs(i, -1, f);
}

long long ans = 0;
int		  n;

void dfs1_bcc(
	int p, int b, vector<vector<int>> const &BCC, vector<vector<int>> const &VER, vector<int> &BS, vector<int> &VS);
void dfs1_ver(
	int p, int v, vector<vector<int>> const &BCC, vector<vector<int>> const &VER, vector<int> &BS, vector<int> &VS)
{
	VS[v] = 1;
	for (int b : VER[v])
	{
		if (b == p)
			continue;
		dfs1_bcc(v, b, BCC, VER, BS, VS);
		VS[v] += BS[b];
	}
}
void dfs1_bcc(
	int p, int b, vector<vector<int>> const &BCC, vector<vector<int>> const &VER, vector<int> &BS, vector<int> &VS)
{
	for (int v : BCC[b])
	{
		if (v == p)
			continue;
		dfs1_ver(b, v, BCC, VER, BS, VS);
		BS[b] += VS[v];
	}
}

long long dis(int l, int i, int j)
{
	int d = abs(i - j);
	return min(d, l - d);
}

void dfs2_bcc(
	int p, int b, vector<vector<int>> const &BCC, vector<vector<int>> const &VER, vector<int> &BS, vector<int> &VS);
void dfs2_ver(
	int p, int v, vector<vector<int>> const &BCC, vector<vector<int>> const &VER, vector<int> &BS, vector<int> &VS)
{
	for (int b : VER[v])
	{
		if (b == p)
			continue;
		dfs2_bcc(v, b, BCC, VER, BS, VS);
	}
}
void dfs2_bcc(
	int p, int b, vector<vector<int>> const &BCC, vector<vector<int>> const &VER, vector<int> &BS, vector<int> &VS)
{
	int tmp = 0;
	for (int v : BCC[b])
	{
		if (v == p)
		{
			tmp	  = VS[v];
			VS[v] = n - BS[b];
			continue;
		}
		dfs2_ver(b, v, BCC, VER, BS, VS);
	}

	int mx = 0, l = (int)size(BCC[b]);
	for (int v : BCC[b])
		mx = max(mx, VS[v]);
	if (n <= 2 * mx)
	{
		int i = 0;
		while (VS[BCC[b][i]] != mx)
			i++;
		for (int j = 0; j < l; j++)
			ans += VS[BCC[b][j]] * dis(l, i, j);
	}
	else
	{
		vector<int> I;
		I.reserve(n);
		for (int i = 0; i < l; i++)
			for (int c = 0; c < VS[BCC[b][i]]; c++)
				I.push_back(i);

		for (int i = 0; i < n / 2; i++)
			ans += dis(l, I[i], I[i + n / 2]);
	}

	for (int v : BCC[b])
	{
		if (v == p)
		{
			VS[v] = tmp;
			break;
		}
	}
}

int main()
{
	cin.tie(0)->sync_with_stdio(0);
	int t;
	cin >> t;
	while (t--)
	{
		int m;
		cin >> n >> m;
		ans = 0;
		vector<pii> E;
		ed.assign(n, {});
		num.clear();
		st.clear();
		Time = 0;
		dep.assign(n, 0);
		while (m--)
		{
			int a, b;
			cin >> a >> b;
			a--;
			b--;
			ed[a].emplace_back(b, (int)size(E));
			ed[b].emplace_back(a, (int)size(E));
			E.emplace_back(a, b);
		}
		vector<vector<int>> BCC;
		vector<vector<int>> VER(n);
		bicomps(
			[&](vi const &B)
			{
				BCC.emplace_back();
				for (int e : B)
				{
					BCC.back().push_back(E[e].first);
					BCC.back().push_back(E[e].second);
				}

				sort(begin(BCC.back()),
					 end(BCC.back()),
					 [&](int a, int b)
					 {
						 return dep[a] < dep[b];
					 });
				BCC.back().erase(unique(begin(BCC.back()), end(BCC.back())), end(BCC.back()));
				for (int v : BCC.back())
					VER[v].push_back(sz(BCC) - 1);
			});
		int k = (int)size(BCC);

		vector<int> VS(n), BS(k);
		dfs1_ver(-1, 0, BCC, VER, BS, VS);
		dfs2_ver(-1, 0, BCC, VER, BS, VS);
		cout << ans << '\n';
	}
}
