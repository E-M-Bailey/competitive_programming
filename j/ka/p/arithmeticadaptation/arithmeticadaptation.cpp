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
    int s;
    cin >> s;
    bool n = s < 0;
    s = n ? -s : s;
    int a = s <= 1 ? -1 : 1, b = s - a;
    cout << (n ? -a : a) << ' ' << (n ? -b : b);
}
