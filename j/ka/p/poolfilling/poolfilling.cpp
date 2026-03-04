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
    double best = 1;
    vf64 P(n);
    for (auto &p : P)
        cin >> p;
    rng::sort(P);
    double s = accumulate(begin(P), end(P), 0.0);
    while (!P.empty())
    {
        double p = P.back();
        P.pop_back();
        best = (min(p, best) + best) / 2;
    }
    cout << fixed << setprecision(7) << s + 1 - best;
}
