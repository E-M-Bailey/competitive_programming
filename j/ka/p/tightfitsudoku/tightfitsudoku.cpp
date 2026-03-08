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

void solve(aapc<6, 6> B)
{
    const auto mask = [&B](int i, int j)
    {
        int m = 0x1ff;
        for (int k = 0; k < 6; ++k)
        {
            if (B[i][k].first >= '1')
                m &= ~(1 << (B[i][k].first - '1'));
            if (B[i][k].second >= '1')
                m &= ~(1 << (B[i][k].second - '1'));
            if (B[k][j].first >= '1')
                m &= ~(1 << (B[k][j].first - '1'));
            if (B[k][j].second >= '1')
                m &= ~(1 << (B[k][j].second - '1'));
            if (B[i / 2 * 2 + k / 3][j / 3 * 3 + k % 3].first >= '1')
                m &= ~(1 << (B[i / 2 * 2 + k / 3][j / 3 * 3 + k % 3].first - '1'));
            if (B[i / 2 * 2 + k / 3][j / 3 * 3 + k % 3].second >= '1')
                m &= ~(1 << (B[i / 2 * 2 + k / 3][j / 3 * 3 + k % 3].second - '1'));
        }
        return m;
    };
    for (int i = 0; i < 6; ++i)
        for (int j = 0; j < 6; ++j)
        {
            if (B[i][j].first == '-')
            {
                char ub = B[i][j].second == '\0' ? '9' + 1 : B[i][j].second == '-' ? '9' : B[i][j].second;
                for (int m = mask(i, j); B[i][j].first = countr_zero<u32>(m) + '1', m; m &= m - 1)
                    if (B[i][j].first < ub)
                        solve(B);
                return;
            }
            if (B[i][j].second == '-')
            {
                char lb = B[i][j].first == '-' ? '0' : B[i][j].first;
                for (int m = mask(i, j); B[i][j].second = countr_zero<u32>(m) + '1', m; m &= m - 1)
                    if (B[i][j].second > lb)
                        solve(B);
                return;
            }
        }
    for (int i = 0; i < 6; ++i)
    {
        for (int j = 0; j < 6; ++j)
        {
            cout << B[i][j].first;
            if (B[i][j].second)
                cout << '/' << B[i][j].second;
            cout << ' ';
        }
        cout << '\n';
    }
    exit(0);
}

int main()
{
    aapc<6, 6> B{};
    str s;
    for (int i = 0; i < 6; ++i)
        for (int j = 0; j < 6; ++j)
        {
            cin >> s;
            B[i][j].first = s[0];
            if (sz(s) == 3)
                B[i][j].second = s[2];
        }
    solve(B);
}
