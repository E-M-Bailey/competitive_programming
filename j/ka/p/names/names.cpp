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
    str s;
    cin >> s;
    int r = INT_MAX, n = sz(s);
    for (int l = n; l < 2 * n; ++l)
    {
        int k = 0;
        for (int i = 0, j = l - 1; i < j; ++i, --j)
            k += j >= n || s[i] != s[j];
        r = min(r, k);
    }
    cout << r;
}
