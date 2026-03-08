#include "template.hpp"

namespace
{
using namespace std;
namespace rng = ranges;
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
    str s;
    cin >> s;
    s.insert(begin(s), '0');
    int k = -1, i = sz(s) - 1;
    while (k < 0 || s[i] == '9')
        k += exchange(s[i--], '0') - '0';
    ++s[i];
    i = sz(s) - 1;
    while (k > 0)
        s[i--] += min(9, exchange(k, k - 9));
    if (s[0] == '0')
        s.erase(begin(s));
    cout << s;
}
