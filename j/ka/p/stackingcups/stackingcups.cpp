#include "template.hpp"

namespace
{
using namespace std;
namespace rng = ranges;
using namespace abbrev;
}

int main()
{
    cin.tie(0)->sync_with_stdio(0);
    i64 n, h;
    cin >> n >> h;
    if (h < 2 * n - 1 || h > n * n || h == n * n - 2)
    {
        cout << "impossible";
        return 0;
    }
    vi32 A(n);
    int l = 0, r = n;
    for (i64 i = n; i;)
    {
        if (h - 1 <= (i - 1) * (i - 1) && h - 1 != (i - 1) * (i - 1) - 2)
        {
            --h;
            A[l++] = 2 * i-- - 1;
        }
        else
        {
            h -= 2 * i - 1;
            i64 j = i - 1;
            while (h < 2 * j - 1 || h > j * j || h == j * j - 2)
                --j;
            for (int k = 1; k <= i - j; ++k)
                A[--r] = 2 * (j + k) - 1;
            i = j;
        }
    }
    for (int a : A)
        cout << a << ' ';
}
