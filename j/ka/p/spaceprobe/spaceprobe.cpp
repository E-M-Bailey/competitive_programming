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
    i64 s, t;
    cin >> n >> k >> s >> t;
    vi64 M(n);
    for (i64 &m : M)
        cin >> m;
    vpi64 I;
    I.reserve(n * k);
    while (k--)
    {
        i64 b, e;
        cin >> b >> e;
        for (i64 m : M)
        {
            i64 l = b - m, r = e - m;
            l = max(l, s);
            r = min(r, t);
            if (l >= r)
                continue;
            I.emplace_back(l, r);
        }
    }
    I.emplace_back(t, t);
    rng::sort(I, {}, &pi64::first);

    i64 c = 0, e = s;
    for (auto [l, r] : I)
    {
        if (l > e)
            c += l - e;
        e = max(r, e);
    }
    c += t - e;
    cout << fixed << setprecision(8) << (double)c / (t - s);
}
