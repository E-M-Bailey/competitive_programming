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
bool find(int j, vvi32& g, vi32& btoa, vi32& vis)
{
	if (btoa[j] == -1)
        return 1;
	vis[j] = 1;
    int di = btoa[j];
	for (int e : g[di])
		if (!vis[e] && find(e, g, btoa, vis))
        {
			btoa[e] = di;
			return 1;
		}
	return 0;
}
// Source: KACTL
int dfsMatching(vvi32& g, vi32& btoa)
{
	vi32 vis;
	for (int i = 0; i < sz(g); ++i)
    {
		vis.assign(sz(btoa), 0);
		for (int j : g[i])
			if (find(j, g, btoa, vis))
            {
				btoa[j] = i;
				break;
			}
    }
	return sz(btoa) - (int)rng::count(btoa, -1);
}
}

int main()
{
    cin.tie(0)->sync_with_stdio(0);
    for (int T = 1, m, n; cin >> m, m; ++T)
    {
        cout << "Scenario " << T << '\n';
        vpf64 R(m);
        for (auto &[x, y] : R)
            cin >> x >> y;
        cin >> n;
        vpf64 H(n);
        for (auto &[x, y] : H)
            cin >> x >> y;
        for (int s : { 5, 10, 20 })
        {
            double d = s * 10;
            vvi32 g(m);
            for (int i = 0; i < m; ++i)
                for (int j = 0; j < n; ++j)
                    if (hypot(H[j].first - R[i].first, H[j].second - R[i].second) < d)
                        g[i].push_back(j);
            vi32 btoa(n, -1);
            cout << "In " << s << " seconds " << dfsMatching(g, btoa) << " robot(s) can escape\n";
        }
        cout << '\n';
    }
}
