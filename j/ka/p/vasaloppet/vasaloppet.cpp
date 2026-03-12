#include "template.hpp"

namespace
{
using namespace std;
namespace rng = ranges;
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
    int n, t, s;
    cin >> n >> t >> s;
    vpi32 C(n);
    for (auto &[l, r] : C)
        cin >> l >> r;
    int k = 0, b = 0;
    for (int i = 0, j = 0; i < n; ++i)
    {
        int e = C[i].first + s;
        while (j < n && C[j].second <= e)
        {
            k += C[j].second - C[j].first;
            ++j;
        }
        b = max(b, j < n && C[j].first < e ? k + e - C[j].first : k);
        k -= C[i].second - C[i].first;
    }
    cout << s - b;
}
