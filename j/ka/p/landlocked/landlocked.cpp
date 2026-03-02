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
constexpr api32<4> DIR{ pi32{ -1, 0 }, pi32{ 0, -1 }, pi32{ 0, 1 }, pi32{ 1, 0 } };
}

int main()
{
    cin.tie(0)->sync_with_stdio(0);
    int n, m;
    cin >> n >> m;
    vstr G(n);
    for (str &GG : G)
        cin >> GG;
    vvi32 D(n, vi32(m, INT_MAX / 2));
    vpi32 A, B;
    vi32 S;
    for (int i = 0; i < n; ++i)
        for (int j = 0; j < m; ++j)
            if (G[i][j] == 'W')
            {
                A.emplace_back(i, j);
                D[i][j] = 0;
            }
    ai32<26> R;
    R.fill(INT_MAX / 2);
    int d = 0;
    while (!A.empty())
    {
        for (int idx = 0; idx < sz(A); ++idx)
        {
            auto [i, j] = A[idx];
            char g = G[i][j];
            for (int i2 = max(i - 1, 0); i2 < min(i + 2, n); ++i2)
                for (int j2 = max(j - 1, 0); j2 < min(j + 2, m); ++j2)
                {
                    int &d2 = D[i2][j2];
                    char g2 = G[i2][j2];
                    bool b = g2 != g;
                    if (d2 <= d + b)
                        continue;
                    int &r = R[g2 - 'A'];
                    d2 = d + b;
                    r = min(r, d2);
                    (b ? B : A).emplace_back(i2, j2);
                }
        }
        for (int idx = 0; idx < sz(B); ++idx)
        {
            auto [i, j] = B[idx];
            if (D[i][j] == d)
            {
                swap(B[idx], B.back());
                B.pop_back();
            }
        }
        ++d;
        A.clear();
        swap(A, B);
    }
    for (char c = 'A'; c <= 'Z'; ++c)
        if (R[c - 'A'] < INT_MAX / 2)
            cout << c << ' ' << R[c - 'A'] - 1 << '\n';
}
