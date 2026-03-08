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
constexpr ai32<13> INV{ 0, 1, 7, 9, 10, 8, 11, 2, 5, 3, 4, 6, 12 };
}

int main()
{
    int n, q, x0, y0;
    cin >> n >> q >> x0 >> y0;
    vi32 S(2'000'001);
    while (n--)
    {
        int l, t, r, b;
        cin >> l >> t >> r >> b;
        tie(l, r) = pi32{ minmax(l, r) };
        tie(t, b) = pi32{ minmax(t, b) };
        int dx1 = r < x0 ? x0 - r : l > x0 ? l - x0 : 0;
        int dy1 = b < y0 ? y0 - b : t > y0 ? t - y0 : 0;
        int dx2 = max(abs(x0 - l), abs(r - x0));
        int dy2 = max(abs(y0 - t), abs(b - y0));
        ++S[dx1 + dy1];
        --S[dx2 + dy2 + 1];
    }
    for (int i = 0; i < 2'000'000; ++i)
        S[i + 1] += S[i];
    while (q--)
    {
        int d;
        cin >> d;
        cout << S[d] << '\n';
    }
}
