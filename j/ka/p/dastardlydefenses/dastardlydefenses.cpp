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
struct point
{
    double x, y;
};
TYPEDEFS(pnt, point);
constexpr pnt operator-(pnt a, pnt b) noexcept
{
    return { a.x - b.x, a.y - b.y };
}
constexpr pnt operator*(pnt a, double b) noexcept
{
    return { a.x * b, a.y * b };
}
constexpr double operator*(pnt a, pnt b) noexcept
{
    return a.x * b.x + a.y * b.y;
}
constexpr double operator^(pnt a, pnt b) noexcept
{
    return a.x * b.y - a.y * b.x;
}
}

int main()
{
    int n;
    pnt c;
    double rc;
    cin >> n >> rc;
    double r2 = rc * rc;
    vector<pair<pnt, double>> C;
    C.reserve(n + 1);
    C.resize(n);
    string ln;
    for (auto &[c, r] : C)
    {
        getline(cin >> c.x >> c.y, ln);
        r = ln.empty() ? 0 : stod(ln);
    }
    C.push_back(C[0]);
    cin >> c.x >> c.y;
    for (int i = 0; i < n; ++i)
    {
        auto [a, ra] = C[i];
        pnt d = a - c;
        if (d * d < ra * ra)
        {
            cout << "no";
            return 0;
        }
    }
    for (int i = 0; i < n; ++i)
    {
        auto [a, ra] = C[i];
        auto [b, rb] = C[i + 1];
        auto ds = b - a;
        double len = sqrt(ds * ds);
        pnt u = ds * (1 / len);
        double d2 = (c - b) ^ ds * (1 / len);
        d2 = d2 * d2;
        if (d2 > r2)
            continue;
        double s = u * a + ra, e = u * b - rb;
        double r = sqrt(r2 - d2), mid = u * c, lo = mid - r, hi = mid + r;
        if (lo < e && hi > s)
        {
            cout << "yes";
            return 0;
        }
    }
    cout << "no";
}
