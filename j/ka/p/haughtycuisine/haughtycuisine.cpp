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
    str s;
    cin >> n >> n;
    cout << n;
    while (n--)
    {
        cin >> s;
        cout << '\n' << s;
    }
}
