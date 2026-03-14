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
    vstr DP;
    cin >> n;
    DP.resize(n + 1);
    for (int i = 0; i <= n; ++i)
    {
        DP[i] = '{';
        char const *delim = "";
        for (int j = 0; j < i; ++j)
            DP[i] += exchange(delim, ",") + DP[j];
        DP[i] += '}';
    }
    cout << DP[n];
}
