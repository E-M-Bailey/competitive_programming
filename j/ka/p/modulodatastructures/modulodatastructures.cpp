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
    int n, q, m;
    cin >> n >> q;
    m = int(sqrt(n) + 1);
    vi32 A(n);
    vvi32 O(m);
    for (int i = 0; i < m; ++i)
        O[i].resize(i);
    while (q--)
    {
        int t, a, b, c;
        cin >> t;
        if (t == 1)
        {
            cin >> a >> b >> c;
            a = (a == 0 ? b : a) - 1;
            if (b < m)
                O[b][a] += c;
            else
                for (int i = a; i < n; i += b)
                    A[i] += c;
        }
        else
        {
            cin >> b;
            a = A[--b];
            for (int i = 1; i < m; ++i)
                a += O[i][b % i];
            cout << a << '\n';
        }
    }
}
