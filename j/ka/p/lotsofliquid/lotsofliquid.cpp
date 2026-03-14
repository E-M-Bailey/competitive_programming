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
    int n;
    cin >> n;
    double s = 0, d;
    while (n--)
    {
        cin >> d;
        s += d * d * d;
    }
    cout << fixed << setprecision(8) << cbrt(s);
}
