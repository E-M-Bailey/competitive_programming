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
    int n;
    cin >> n;
    int a = n % 10, b = n / 10;
    static constexpr auto A = array{ "zero", "one", "two", "three", "four", "five", "six", "seven", "eight", "nine" };
    static constexpr auto A1 = array{ "ten", "eleven", "twelve", "thirteen", "fourteen", "fifteen", "sixteen", "seventeen", "eighteen", "nineteen" };
    static constexpr auto B = array{ "", "ten", "twenty", "thirty", "forty", "fifty", "sixty", "seventy", "eighty", "ninety" };
    if (b == 0)
        cout << A[a];
    else if (b == 1)
        cout << A1[a];
    else if (a == 0)
        cout << B[b];
    else
        cout << B[b] << '-' << A[a];
}
