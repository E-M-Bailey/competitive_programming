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
constexpr api32<4> DIR{ pi32{ -1, 0 }, pi32{ 0, -1 }, pi32{ 0, 1 }, pi32{ 1, 0 } };
}

int main()
{
    cin.tie(0)->sync_with_stdio(0);
    int n, m;
    cin >> n >> m;
    vvi32 G(n);
    while (m--)
    {
        int u, v;
        cin >> u >> v;
        G[u].push_back(v);
        G[v].push_back(u);
    }
    vpi32 D;
    vi32 A, B;
    int r = INT_MAX;
    for (int i = 0; i < n; ++i)
    {
        D.assign(n, { INT_MAX, -1 });
        D[i].first = 0;
        A.assign(1, i);
        bool found = false;
        while (!A.empty())
        {
            for (int u : A)
            {
                auto &[du, pu] = D[u];
                for (int v : G[u])
                {
                    if (v == pu)
                        continue;
                    auto &[dv, pv] = D[v];
                    if (dv == INT_MAX)
                    {
                        dv = du + 1;
                        pv = u;
                        B.push_back(v);
                    }
                    else
                    {
                        found = true;
                        r = min(r, du + dv + 1);
                    }
                }
            }
            swap(A, B);
            B.clear();
            if (found)
                A.clear();
        }
    }
    if (r == INT_MAX)
        cout << "impossible";
    else
        cout << r;
}
