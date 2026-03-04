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
    int n;
    cin >> n;
    vi32 A(n);
    for (int &a : A)
        cin >> a;
    vvi64 DP(n, vi64(n, LLONG_MIN / 2));
    rng::fill(DP[0], A[0]);
    for (int i = 0; i < n; ++i)
    {
        for (int j = 1; j <= i; ++j)
            DP[i][j] = DP[i - j][j] + A[i];
        for (int j = n - 1; j--;)
            DP[i][j] = max(DP[i][j + 1], DP[i][j]);
    }
    cout << DP[n - 1][0];
}
