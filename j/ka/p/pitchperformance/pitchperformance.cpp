#include "template.hpp"

namespace
{
using namespace std;
namespace rng = ranges;
using namespace abbrev;
}

int main()
{
    constexpr double T = 1 / 3.0;
    cin.tie(0)->sync_with_stdio(0);
    int n, m, px = 0, pc = 0, pb = 0, pa = 0;
    cin >> n;
    vector<pair<int, ai32<3>>> D(n);
    for (auto &[x, P] : D)
    {
        auto &[c, b, a] = P;
        x = px;
        cin >> px >> c;
        c = exchange(pc, c) - c;
    }
    cin >> m;
    D.resize(n + m + 1);
    px = pc = 0;
    for (int i = n; i < n + m; ++i)
    {
        auto &[x, P] = D[i];
        auto &[c, b, a] = P;
        x = px;
        cin >> px >> a >> b >> c;
        a -= exchange(pa, a);
        b -= exchange(pb, b);
        c -= exchange(pc, c);
    }
    D.back().first = px;
    rng::inplace_merge(D, begin(D) + n, {}, &pair<int, ai32<3>>::first);
    px = pc = pb = pa = 0;
    double A = 0;
    for (auto [x, P] : D)
    {
        double c = pc;
        double b = pb;
        double a = pa;
        if (a != 0)
        {
            double d = sqrt(max(b * b - 4 * a * c, 0.)), e = -0.5 / a;
            double x0 = max<double>(min<double>((b + d) * e, x), px);
            double x1 = max<double>(min<double>((b - d) * e, x), px);
            if (x0 > x1)
                swap(x0, x1);
            double p = (((T * a * px + 0.5 * b) * px + c) * px);
            double q = (((T * a * x0 + 0.5 * b) * x0 + c) * x0);
            double r = (((T * a * x1 + 0.5 * b) * x1 + c) * x1);
            double s = (((T * a * x + 0.5 * b) * x + c) * x);
            A += abs(q - p) + abs(r - q) + abs(s - r);
        }
        else if (b != 0)
        {
            double x0 = max<double>(min<double>(-c / b, x), px);
            double p = (0.5 * b * px + c) * px;
            double q = (0.5 * b * x0 + c) * x0;
            double r = (0.5 * b * x + c) * x;
            A += abs(q - p) + abs(r - q);
        }
        else
            A += abs((x - px) * c);
        px = x;
        auto [cc, bb, aa] = P;
        pc += cc;
        pb += bb;
        pa += aa;
    }
    cout << fixed << setprecision(8) << A;
}
