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

constexpr double eps = 1e-8;

int shoelace(vpi32 const &P)
{
    int n = sz(P);
    int a = 0;
    for (int i = 0; i < n; ++i)
    {
        auto [x0, y0] = P[i];
        auto [x1, y1] = P[i == n - 1 ? 0 : i + 1];
        a += x0 * y1 - x1 * y0;
    }
    return a;
}
template<double Z>
double balance(vpi32 const &P, int c)
{
    int n = sz(P);
    double b = 0;
    for (int i = 0; i < n; ++i)
    {
        auto [x0, y0] = P[i];
        auto [x1, y1] = P[i == n - 1 ? 0 : i + 1];
        if (x0 == x1)
            continue;
        x0 -= c;
        x1 -= c;
        i64 dx = x1 - x0, dy = y1 - y0, c3 = 2 * dy, c2 = 3 * (x1 * y0 - x0 * y1);
        b += ((c3 * x1 + c2) * x1 * x1 - (c3 * x0 + c2) * x0 * x0) / (6.0 * dx);
    }
    return P[0].first == c && abs(b) < eps ? 0 : b / (P[0].first == c ? Z : P[0].first - c);
}
}

int main()
{
    cin.tie(0)->sync_with_stdio(0);
    int n;
    cin >> n;
    vpi32 P(n);
    int l = INT_MAX, r = INT_MIN;
    for (auto &[x, y] : P)
    {
        cin >> x >> y;
        if (y == 0)
        {
            l = min(l, x);
            r = max(r, x);
        }
    }
    if (shoelace(P) < 0)
        reverse(begin(P) + 1, end(P));
    auto bl = balance<0.>(P, l), br = balance<-0.>(P, r);
    int x0 = P[0].first;
    auto [lo, hi] = minmax(bl, br);
    if (hi == INFINITY)
        cout << "unstable";
    else if (l <= x0 && x0 <= r)
        cout << static_cast<i64>(max(hi, 0.) + eps) << " .. inf";
    else if (hi >= 0)
        cout << static_cast<i64>(max(lo, 0.) + eps) << " .. " << static_cast<i64>(ceil(hi - eps));
    else
        cout << "unstable";
}
