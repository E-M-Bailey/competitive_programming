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
    int n;
    cin >> n;
    vi32 D(n);
    vvi32 DP(n);
    for (int i = 0; i < n; ++i)
        DP[i].assign(i, INT_MAX / 2);
    for (int &d : D)
        cin >> d;
    for (int &d : D)
        cin >> d;
    DP[1][0] = D[0];
    for (int i = 2; i < n; ++i)
    {
        for (int &d : D)
            cin >> d;
        for (int j = 0; j < i - 1; ++j)
        {
            DP[i][i - 1] = min(DP[i][i - 1], DP[i - 1][j] + D[j]);
            DP[i][j] = min(DP[i][j], DP[i - 1][j] + D[i - 1]);
        }
    }
    cout << rng::min(DP[n - 1]);
}
