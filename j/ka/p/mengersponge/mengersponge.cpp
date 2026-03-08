#include "template.hpp"

namespace
{
using namespace std;
using namespace abbrev;


}

int main()
{
    int l;
    cin >> l;
    api32<3> X;
    for (auto &[n, d] : X)
        cin >> n >> d;
    while (l--)
    {
        int c = 0;
        for (auto &[n, d] : X)
        {
            n *= 3;
            bool l = n <= d, r = n >= 2 * d;
            c += !l && !r;
            n -= (!l + r) * d;
        }
        if (c >= 2)
        {
            cout << '0';
            return 0;
        }
    }
    cout << '1';
}
