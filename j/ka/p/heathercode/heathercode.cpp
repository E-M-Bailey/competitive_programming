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
    int a = n / 1'000'000, b = n / 100'000, c = n / 10'000, d = n / 1'000, e = n / 100, f = n / 10, g = n;
    tie(a, b, c, d, e, f, g) = tuple{ a, b - a, c - b, d - c, e - d, f - e, g - f };
    cout << a % 10 << b % 10 << c % 10 << d % 10 << e % 10 << f % 10 << g % 10;
}
