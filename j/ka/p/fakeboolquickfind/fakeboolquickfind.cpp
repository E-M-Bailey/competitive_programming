#include "template.hpp"

namespace
{
using namespace std;
namespace rng = ranges;
namespace vws = views;
using namespace abbrev;
template<typename C>
[[nodiscard]] constexpr int sz(C const &c) noexcept
{
    return static_cast<int>(size(c));
}
}

int main()
{
    cin.tie(0)->sync_with_stdio(0);
    int n, m, u, v, w, i = 0, j = 0;
    cin >> n >> m;
    vvi32 G(n);
    while (m--)
    {
        cin >> u >> v;
        G[u].push_back(v);
        G[v].push_back(u);
    }
    vi32 R(n, -1), Q(n);
    for (u = 0; u < n; ++u)
    {
        if (R[u] < 0)
        {
            R[u] = u;
            Q[j++] = u;
            while (i < j)
            {
                v = Q[i++];
                for (int w : G[v])
                    if (R[w] < 0)
                    {
                        R[w] = u;
                        Q[j++] = w;
                    }
            }
        }
        cout << R[u] << ' ';
    }
}
