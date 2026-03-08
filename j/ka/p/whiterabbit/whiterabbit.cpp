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
constexpr ai32<13> INV{ 0, 1, 7, 9, 10, 8, 11, 2, 5, 3, 4, 6, 12 };
}

int main()
{
    int n, s, t, m;
    cin >> n >> s >> t >> m;
    --s;
    --t;
    int k = 0;
    vi32 I(n * n, -1);
    vpi32 E;
    vvi32 T(m);
    vi32 B(m);
    for (int i = 0; i < m; ++i)
    {
        auto &TT = T[i];
        int p, u, v;
        cin >> B[i] >> p >> u;
        --u;
        while (--p)
        {
            cin >> v;
            --v;
            pi32 uv = minmax(u, v);
            int &j = I[uv.first * n + uv.second];
            if (j < 0)
            {
                j = k++;
                E.push_back(uv);
            }
            TT.resize(max(sz(TT), j + 1));
            if (++TT[j] == 13)
                TT[j] = 0;
            u = v;
        }
    }
    for (auto &TT : T)
        TT.resize(k);
    for (int i = 0; i < k; ++i)
    {
        auto &TT = T[i];
        for (int j = i;; ++j)
            if (T[j][i] != 0)
            {
                if (i != j)
                {
                    swap(T[j], TT);
                    swap(B[j], B[i]);
                }
                break;
            }
        int a = TT[i], b = INV[a];
        TT[i] = 1;
        for (int j = i + 1; j < k; ++j)
            TT[j] = TT[j] * b % 13;
        B[i] = B[i] * b % 13;
        for (int j = i + 1; j < m; ++j)
            if (int c = T[j][i]; c != 0)
            {
                T[j][i] = 0;
                for (int l = i + 1; l < k; ++l)
                    T[j][l] = (T[j][l] + 169 - c * T[i][l]) % 13;
                B[j] = (B[j] + 169 - c * B[i]) % 13;
            }
    }
    for (int i = k; i--;)
    {
        auto &TT = T[i];
        for (int j = 0; j < i; ++j)
            if (int c = T[j][i]; c != 0)
            {
                T[j][i] = 0;
                B[j] = (B[j] + 169 - c * B[i]) % 13;
            }
    }
    vvpi32 G(n);
    for (int i = 0; i < k; ++i)
    {
        auto [u, v] = E[i];
        int d = B[i];
        G[u].emplace_back(v, d);
        G[v].emplace_back(u, d);
    }
    priority_queue<pi32, vpi32, greater<>> Q;
    vi32 D(n, INT_MAX / 2);
    vb V(n, false);
    D[s] = 0;
    Q.emplace(0, s);
    while (!V[t])
    {
        auto [dsu, u] = Q.top();
        Q.pop();
        if (V[u])
            continue;
        V[u] = true;
        for (auto [v, duv] : G[u])
        {
            int dsv = dsu + duv;
            if (D[v] > dsv)
            {
                D[v] = dsv;
                Q.emplace(dsv, v);
            }
        }
    }
    cout << D[t];
}
