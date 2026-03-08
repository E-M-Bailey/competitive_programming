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
    int T;
    cin >> T;
    vi32 W;
    while (T--)
    {
        int n, w, m;
        cin >> n >> w >> m;
        W.resize(w + 2);
        for (int i = 0; i < w; ++i)
        {
            cin >> W[i];
            --W[i];
        }
        W[w] = n;
        W[w + 1] = n * 2;
        int lo = 1, hi = (n + m - 1) / m;
        while (lo < hi)
        {
            int l = (lo + hi) / 2, c = 0, e = 0, i = 0;
            while (e < n && c++ < m)
            {
                e = max(e + l, W[i]);
                while (W[i] < e)
                    ++i;
            }
            if (c <= m)
                hi = l;
            else
                lo = l + 1;
        }
        cout << lo << '\n';
    }
}
