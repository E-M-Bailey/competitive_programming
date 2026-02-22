#include <bits/extc++.h>

using namespace std;
using namespace chrono;

using ll = long long;

namespace {

mt19937_64 randy{ uint64_t(duration_cast<nanoseconds>(high_resolution_clock::now().time_since_epoch()).count()) };
uniform_int_distribution<ll> distr{LLONG_MIN, LLONG_MAX};

struct node
{
	int k;
	ll s;
	int lk = 0;
	ll ls = 0;
	int l = -1, r = -1;
	ll p = distr(randy), k2 = distr(randy);
};
struct treaps
{
	vector<node> N;
	void push(int i)
	{
		node &cn = N[i];
		if (cn.l >= 0)
		{
			node &ch = N[cn.l];
			ch.lk += cn.lk;
			ch.ls += cn.ls;
		}
		if (cn.r >= 0)
		{
			node &ch = N[cn.r];
			ch.lk += cn.lk;
			ch.ls += cn.ls;
		}
		cn.k += exchange(cn.lk, 0);
		cn.s += exchange(cn.ls, 0);
	}
	void push_all(int i)
	{
		push(i);
		node &nd = N[i];
		if (nd.l >= 0)
			push_all(nd.l);
		if (nd.r >= 0)
			push_all(nd.r);
	}
	pair<int, int> split(int i, int k, ll k2 = LLONG_MIN)
	{
		node &cn = N[i];
		push(i);
		if (tie(cn.k, cn.k2) < tie(k, k2))
		{
			auto [l, r] = cn.r < 0 ? pair{-1, -1} : split(cn.r, k, k2);
			cn.r = l;
			return {i, r};
		}
		else
		{
			auto [l, r] = cn.l < 0 ? pair{-1, -1} : split(cn.l, k, k2);
			cn.l = r;
			return {l, i};
		}
	}
	int onion(int i, int j)
	{
		push(i);
		push(j);
		if (N[i].p < N[j].p)
			swap(i, j);
		node &nd = N[i];
		auto [l, r] = split(j, nd.k, nd.k2);
		if (l >= 0)
			nd.l = nd.l < 0 ? l : onion(nd.l, l);
		if (r >= 0)
			nd.r = nd.r < 0 ? r : onion(nd.r, r);
		return i;
	}
	int shift(int i, int dk, int ds)
	{
		auto [l, r] = split(i, dk);
		if (r < 0)
			return l;
		N[r].lk -= dk;
		N[r].ls += ds;
		return l < 0 ? r : onion(l, r);
	}
};

}
int main()
{
	int n, k;
	cin >> n >> k;

	vector<int> S(n), K(n);
	for (int &s : S)
		cin >> s;
	for (int &kk : K)
		cin >> kk;
	treaps T;
	T.N.reserve(n);
	int root = -1;
	for (int i = 0; i < n; ++i)
	{
		T.N.push_back({k, 0});
		root = T.shift(i == 0 ? 0 : T.onion(root, i), K[i], S[i]);
	}
	T.push_all(root);
	for (int i = 0; i < n; ++i)
		cout << T.N[i].s << ' ';
}
