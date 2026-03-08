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
int solve(vi32 const &A)
{
    vi32 L;
    for (int a : A)
    {
        auto it = rng::lower_bound(L, a);
        if (it == end(L))
            L.push_back(a);
        else
            *it = a;
    }
    return sz(L);
}
}

int main()
{
    int n;
    cin >> n;
    vi32 A(n);
    for (int &a : A)
        cin >> a;
    int r = solve(A);
    rng::reverse(A);
    cout << max(r, solve(A));
}
