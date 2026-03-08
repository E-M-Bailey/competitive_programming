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
    int n, m;
    cin >> n >> m;
    vvpi32 G(n);
    while (m--)
    {
        int u, v, w;
        cin >> u >> v >> w;
        G[--u].emplace_back(--v, w);
        G[v].emplace_back(u, w);
    }
    ai32<7> B, S;
    for (int &b : B)
    {
        cin >> b;
        --b;
    }
    aai32<7, 7> DB{};
    priority_queue<pi32, vpi32, greater<>> Q;
    vb V;
    vi32 D;
    for (int i = 7; i--;)
    {
        V.assign(n, false);
        D.assign(n, INT_MAX);
        D[B[i]] = 0;
        Q.emplace(0, B[i]);
        while (!Q.empty())
        {
            auto [d, u] = Q.top();
            Q.pop();
            if (V[u])
                continue;
            V[u] = true;
            for (auto [v, w] : G[u])
                if (!V[v] && d + w < D[v])
                {
                    D[v] = d + w;
                    Q.emplace(d + w, v);
                }
        }
        S[i] = D[0];
        for (int j = i + 1; j < 7; ++j)
            DB[i][j] = DB[j][i] = D[B[j]];
    }
    if (rng::find(S, INT_MAX) != end(S))
    {
        cout << "-1";
        return 0;
    }
    ai64<7 << 7> DP;
    DP.fill(LLONG_MAX);
    for (int i = 0; i < 7; ++i)
        DP[(i << 7) | (1 << i)] = S[i];
    for (int mask = 0; mask < 128; ++mask)
        for (int i = 0; i < 7; ++i)
            if (mask & (1 << i))
                for (int j = 0; j < 7; ++j)
                    if ((mask ^ (1 << i)) & (1 << j))
                        DP[(i << 7) | mask] = min(DP[(i << 7) | mask], DP[(j << 7) | (mask ^ (1 << i))] + DB[j][i]);
    i64 r = LLONG_MAX;
    for (int i = 0; i < 7; ++i)
        r = min(r, DP[(i << 7) | 127]);
    cout << r;
}
