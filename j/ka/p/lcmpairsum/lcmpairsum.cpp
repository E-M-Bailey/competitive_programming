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
constexpr i64 M = 1'000'000'007;
constexpr i64 mpow(i64 a, i64 b)
{
    if ((a %= M) < 0)
        a += M;
    if ((b %= M - 1) < 0)
        b += M - 1;
    i64 r = 1;
    for (; b; b /= 2, a = a * a % M)
        if (b % 2)
            r = r * a % M;
    return r;
}
}

int main()
{
    cin.tie(0)->sync_with_stdio(0);
    int T;
    cin >> T;
    for (int i = 1; i <= T; ++i)
    {
        int k;
        cin >> k;
        i64 r = 1, n = 1;
        while (k--)
        {
            i64 p, a;
            cin >> p >> a;
            i64 pp = mpow(p, a);
            i64 x = (pp - 1) * (mpow(p - 1, -1)) % M;
            i64 y = pp * (a + 1) % M;
            n = n * pp % M;
            r = r * (x + y) % M;
        }
        cout << "Case " << i << ": " << (r + n >= M ? r + n - M : r + n) << '\n';
    }
}
