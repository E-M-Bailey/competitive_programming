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
}

int main()
{
    cin.tie(0)->sync_with_stdio(0);
    int n, m, h, w;
    while (cin >> n >> m >> h >> w)
    {
        vvi32 P(n + 1, vi32(m + 1));
        str s;
        for (int i = 0; i < n; ++i)
        {
            cin >> s;
            for (int j = 0; j < m; ++j)
                P[i + 1][j + 1] = P[i + 1][j] + P[i][j + 1] - P[i][j] + (s[j] == 'X');
        }
        int r = INT_MAX;
        for (int y = 1 - h; y <= 0; ++y)
            for (int x = 1 - w; x <= 0; ++x)
            {
                int k = 0;
                for (int i = y; i < n; i += h)
                {
                    int t = max(i, 0), b = min(i + h, n);
                    for (int j = x; j < m; j += w)
                    {
                        int l = max(j, 0), r = min(j + w, m);
                        k += P[b][r] - P[b][l] - P[t][r] + P[t][l] > 0;
                    }
                }
                r = min(r, k);
            }
        cout << r << '\n';
    }
}
