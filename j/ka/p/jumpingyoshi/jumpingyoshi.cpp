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
    cin.tie(0)->sync_with_stdio(0);
    int n;
    cin >> n;
    vi32 A(n);
    unordered_map<int, int> I;
    for (int i = 0; i < n; ++i)
    {
        int &a = A[i];
        cin >> a;
        I.try_emplace(i + a, sz(I));
        if (a != 0)
            I.try_emplace(i - a, sz(I));
    }
    int m = sz(I), N = n + 2 * m;
    vvi32 G(N);
    for (int i = 0; i < n; ++i)
    {
        int a = A[i];
        int x = I[i + a], y = a == 0 ? x : I[i - a];
        G[i].push_back(x + n);
        G[i].push_back(y + n + m);
        G[y + n].push_back(i);
        G[x + n + m].push_back(i);
    }
    vi32 S{ 0 };
    vb V(N, false);
    V[0] = true;
    int r = 0;
    while (!S.empty())
    {
        int u = S.back();
        if (u < n)
            r = max(r, u);
        S.pop_back();
        for (int v : G[u])
            if (!V[v])
            {
                V[v] = true;
                S.push_back(v);
            }
    }
    cout << r;
}
