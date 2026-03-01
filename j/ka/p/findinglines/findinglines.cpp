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
    int n, p;
    cin >> n >> p;
    if (n <= 2)
    {
        cout << "possible";
        return 0;
    }
    p = (p * n + 99) / 100;
    vpi32 P(n);
    for (auto &[x, y] : P)
        cin >> x >> y;
    for (int i = 0; i < 1024; ++i)
    {
        int a = unif(0, n - 1), b = unif(0, n - 2);
        b += (b >= a);
        i64 dx = P[b].first - P[a].first, dy = P[b].second - P[a].second;
        int k = 0;
        for (int j = 0; j < n; ++j)
        {
            i64 dx2 = P[j].first - P[a].first, dy2 = P[j].second - P[a].second;
            k += dx * dy2 == dx2 * dy;
        }
        if (k >= p)
        {
            cout << "possible";
            return 0;
        }
    }
    cout << "impossible";
}
