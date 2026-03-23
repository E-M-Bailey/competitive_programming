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
    int t, n;
    cin >> t;
    while (t--)
    {
        cin >> n;
        ++n;
        int s = (int)sqrtl(n);
        while (s * s > n)
            --s;
        while ((s + 1) * (s + 1) <= n)
            ++s;
        cout << (s - 1) / 2 << '\n';
    }
}
