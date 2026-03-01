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
    vvi32 D(500000);
    for (int d = 1; d < 1000000; d += 2)
        for (int i = d / 2; i < 500000; i += d)
            D[i].push_back(d);
    for (int n; cin >> n, n;)
    {
        int z = countr_zero<u32>(n), k = 0;
        auto &DD = D[n >> (z + 1)];
        int m = sz(DD);
        i64 d;
        for (int i = 0; i < m && (d = DD[i], (d + 3) * d / 2 <= n); ++i)
            ++k;
        for (int i = 0; i < m && (d = DD[i] << (z + 1), (d + 3) * d / 2 <= n); ++i)
            ++k;
        cout << k << '\n';
    }
}
