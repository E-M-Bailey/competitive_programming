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
    int n, k;
    cin >> n;
    au64<64> M{};
    u64 T;
    cin >> T;
    while (n--)
    {
        u64 N;
        cin >> N >> k;
        for (int i = 0; i < 64; ++i)
        {
            u64 b = 1ull << i;
            if ((b & N) == 0)
                continue;
            if (M[i] == 0)
            {
                M[i] = N;
                break;
            }
            N ^= M[i];
        }
    }
    for (int i = 0; i < 64; ++i)
        if (T & (1ull << i))
            T ^= M[i];
    cout << (T ? "impossible" : "possible");
}
