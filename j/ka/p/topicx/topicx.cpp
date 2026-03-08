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
int dfs(int u, vi32 &DP, vb &V, vvi32 const &G, vi32 const &M)
{
    if (DP[u] >= 0)
        return DP[u];
    V[u] = true;
    for (int v : G[u])
    {
        if (V[v])
            return DP[u] = INT_MAX / 2;
        DP[u] = max(DP[u], dfs(v, DP, V, G, M));
    }
    V[u] = false;
    return DP[u] += M[u];
}
int id(int n, str const &bad)
{
    static str s;
    static unordered_map<str, int> T;
    cin >> s;
    return s == bad ? n : T.try_emplace(s, sz(T)).first->second;
}
}

int main()
{
    int n;
    cin >> n;
    unordered_map<str, int> T;
    vvi32 G(n);
    vi32 M(n);
    str bad;
    int s = id(n, bad);
    cin >> bad;
    for (int i = 0; i < n; ++i)
    {
        int k, u = id(n, bad);
        cin >> M[u] >> k;
        G[u].resize(k);
        for (int &v : G[u])
            v = id(n, bad);
    }
    vi32 DP(n + 1, -1);
    DP[n] = 0;
    vb V(n);
    int t = dfs(s, DP, V, G, M);
    if (t >= INT_MAX / 2)
        cout << "SAFE";
    else
        cout << t;
}
