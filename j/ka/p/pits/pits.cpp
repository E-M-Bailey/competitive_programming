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
    int n;
    cin >> n;
    vi32 A(n);
    int p = 0;
    for (int &a : A)
    {
        cin >> a;
        p = a = a == 0 ? p + 1 : min(a, p + 1);
    }
    double r = 0;
    for (int i = n; i--;)
    {
        p = min(p + 1, A[i]);
        r += 1.0 / p;
    }
    cout << fixed << setprecision(8) << r;
}
