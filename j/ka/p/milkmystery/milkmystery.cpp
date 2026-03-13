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
    cin.tie(0)->sync_with_stdio(0);
    int n, k, s = 0, r = 0, a;
    queue<int> Q;
    cin >> n >> k;
    while (n--)
    {
        cin >> a;
        s += a;
        Q.push(a);
        if (sz(Q) > k)
        {
            s -= Q.front();
            Q.pop();
        }
        if (sz(Q) == k)
            r = max(r, s);
    }
    cout << r;
}
