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
int cnt(str const &s)
{
    int k = 0;
    char p = s.back();
    for (char c : s)
        k += c != exchange(p, c);
    return k;
}
}

int main()
{
    int n;
    str s, t;
    cin >> n >> s >> t;
    int a = cnt(s), b = cnt(t);
    cout << (b <= a && ((1 < b && b < n) || s == t) ? "yes" : "no");
}
