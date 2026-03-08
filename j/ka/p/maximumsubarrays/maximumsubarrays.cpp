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
    int n, k;
    cin >> n >> k;
    vpi64 DP(k + 1, { LLONG_MIN / 2, LLONG_MIN / 2 });
    DP[0] = { 0, 0 };
    while (n--)
    {
        int x;
        cin >> x;
        for (int i = k; i >= 1; --i)
        {
            i64 s = max(DP[i].second, DP[i - 1].first) + x;
            i64 a = max(DP[i].first, s);
            DP[i] = { a, s };
        }
    }
    cout << DP[k].first;
}
