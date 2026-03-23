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
    i64 n;
    cin >> n;
    i64 m = (i64)sqrtl(8 * n - 7);
    while (m * m > 8 * n - 7)
        --m;
    while ((m + 1) * (m + 1) <= 8 * n - 7)
        ++m;
    m = (m + 1) / 2;
    n -= m * (m - 1) / 2 + 1;
    cout << m;
    if (n)
    {
        i64 g = gcd(n, m);
        cout << ' ' << n / g << '/' << m / g;
    }
}
