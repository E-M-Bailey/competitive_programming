#include "template.hpp"

namespace
{
using namespace std;
using namespace abbrev;
}

int main()
{
    cin.tie(0)->sync_with_stdio(0);
    int l1 = 1, h1 = 500, l2 = 1, h2 = 500;
    str s;
    while (l1 < h1 || l2 < h2)
    {
        int m1 = (l1 + h1 + 1) / 2, m2 = (l2 + h2 + 1) / 2;
        cout << "ASK " << min(m1, m2) << ' ' << (m1 == m2 ? 500 : max(m1, m2) - 1) << endl;
        cin >> s;
        if ((s[0] == 'y') ^ (m1 > m2))
            l1 = m1;
        else
            h1 = m1 - 1;
        cin >> s;
        if ((s[0] == 'y') ^ (m1 < m2))
            l2 = m2;
        else
            h2 = m2 - 1;
    }
    cout << "GUESS " << l1 << ' ' << l2;
}
