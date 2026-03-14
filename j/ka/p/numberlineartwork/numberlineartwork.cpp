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
    int n, m, i;
    str s;
    lstr L;
    vector<lstr::const_iterator> I;
    cin >> n >> m;
    I.reserve(n);
    while (n--)
    {
        L.emplace_back();
        I.push_back(prev(L.end()));
        cin >> L.back();
    }
    while (m--)
    {
        cin >> i >> s;
        if (s == "R")
            ++I[i];
        else if (s == "L")
            --I[i];
        else
            I[i] = L.insert(I[i], std::move(s));
    }
    for (const str& s : L)
        cout << s << ' ';
}
