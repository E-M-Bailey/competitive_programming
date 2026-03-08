#include "template.hpp"

using namespace std;
namespace rng = ranges;
using namespace abbrev;

namespace
{
template<typename C>
constexpr int sz(C const &c)
{
    return static_cast<int>(size(c));
}

// Source: KACTL
bool find(int j, vvi32 &g, vi32 &b2a, vb &vis)
{
	if (b2a[j] == -1)
        return 1;
	vis[j] = true;
    int di = b2a[j];
	for (int e : g[di])
		if (!vis[e] && find(e, g, b2a, vis))
        {
			b2a[e] = di;
			return 1;
		}
	return 0;
}
// Source: KACTL
int dfs_matching(vvi32 &g, vi32 &b2a)
{
	vb vis;
	for (int i = 0; i < sz(g); ++i)
    {
		vis.assign(sz(b2a), false);
		for (int j : g[i])
			if (find(j, g, b2a, vis))
            {
				b2a[j] = i;
				break;
			}
    }
	return sz(b2a) - (int)rng::count(b2a, -1);
}
}

int main()
{
    cin.tie(0)->sync_with_stdio(0);
    int b, g, k;
    cin >> b >> g;
    unordered_map<str, int> B;
    vvi32 G(g);
    str s;
    for (int i = 0; i < b + g; ++i)
    {
        cin >> s >> k;
        while (k--)
        {
            cin >> s;
            if (i < b)
                B.try_emplace(std::move(s), i);
            else
                G[i - b].push_back(B.find(s)->second);
        }
    }
    vi32 b2g(b, -1);
    cout << dfs_matching(G, b2g);
}
