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
    while (n--)
    {
        int a, b, c, d, x, y, z, w;
        cin >> a >> b >> c >> d >> x >> y >> z >> w;
        const auto getx = [m = double(c - a) / (d - b), a, b](int y)
        {
            return m * (y - b) + a;
        };
        const auto gety = [m = double(d - b) / (c - a), a, b](int x)
        {
            return m * (x - a) + b;
        };
        const auto getps = [=](int x, int y)
        {
            vpf64 P{ { a, b }, { c, d } };
            if (min(a, c) <= x && x <= max(a, c))
                P.emplace_back(x, gety(x));
            if (min(b, d) <= y && y <= max(b, d))
                P.emplace_back(getx(y), y);
            return P;
        };
        const auto sq = [](double x)
        {
            return x * x;
        };
        double r = abs(z - x) + abs(w - y);
        for (auto [x1, y1] : getps(x, y))
            for (auto [x2, y2] : getps(z, w))
                r = min(r, abs(x1 - x) + abs(y1 - y) + sqrt(sq(x2 - x1) + sq(y2 - y1)) + abs(z - x2) + abs(w - y2));
        cout << fixed << setprecision(8) << r << '\n';
    }
}
