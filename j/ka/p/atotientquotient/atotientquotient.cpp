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
    vi32 P;
    vb C(10001);
    for (int i = 2; i <= 10000; ++i)
        if (!C[i])
        {
            P.push_back(i);
            for (int j = 2 * i; j <= 10000; j += i)
                C[j] = true;
        }
    cin.tie(0)->sync_with_stdio(0);
    u64 a, b, m = 1, n = 1;
    cin >> a >> b;
    for (u64 p : P | vws::reverse)
    {
        int f = 0;
        while (a % p == 0)
        {
            ++f;
            a /= p;
        }
        while (b % p == 0)
        {
            --f;
            b /= p;
        }
        if (f == 0)
            continue;
        u64 &x = f > 0 ? m : n, &y = f > 0 ? n : m;
        for (int i = 0; i < abs(f) / 2 + 1; ++i)
            x *= p;
        if (f % 2 == 0)
            y *= p;
        else
        {
            u64 &c = f > 0 ? a : b;
            u64 &d = f > 0 ? b : a;
            u64 g = gcd(c, p - 1);
            c /= g;
            d *= (p - 1) / g;
        }
    }
    cout << m << ' ' << n;
}
