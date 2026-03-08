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
unordered_map<str, int> CC;
vstr D;
int id()
{
    static str s;
    cin >> s;
    auto [it, ins] = CC.try_emplace(s, sz(CC));
    if (ins)
        D.push_back(s);
    return it->second;
}
struct maxima
{
    int a, x = -1;
    friend bool operator==(maxima l, maxima r)
    {
        return l.a == r.a && l.x == r.x;
    }
    friend maxima operator|(maxima l, maxima r)
    {
        if (r.x == -1 || l.x == r.x)
            return l;
        if (l.x == -1)
            return r;
        if (l.a < r.a)
            return r;
        if (l.a > r.a)
            return l;
        return { l.a, -2 };
    }
};
}

int main()
{
    int n;
    cin >> n;
    vector<maxima> A(n);
    vi32 Q;
    vector<vector<pair<int, maxima>>> P(n);
    for (int i = 0; i < n; ++i)
    {
        int v = id(), p = id();
        cin >> A[v].a;
        A[v].x = v;
        if (p != v)
            P[v].emplace_back(p, maxima{});
        if (A[v].a >= 0)
            Q.push_back(v);
    }
    vi32 C(n);
    for (int v = 0; v < n; ++v)
        if (!P[v].empty())
            ++C[P[v][0].first];
    vi32 S = Q;
    while (!S.empty())
    {
        int u = S.back();
        S.pop_back();
        if (P[u].empty())
            continue;
        int v = P[u][0].first;
        A[v] = A[v] | A[u];
        if (--C[v] == 0)
            S.push_back(v);
    }
    for (int v = 0; v < n; ++v)
        if (!P[v].empty())
            P[v][0].second = A[P[v][0].first];

    int k;
    for (k = 1; 1 << k < n; ++k)
        for (int u = 0; u < n; ++u)
        {
            if (sz(P[u]) < k)
                continue;
            auto [v, a] = P[u][k - 1];
            if (sz(P[v]) < k)
                continue;
            auto [w, b] = P[v][k - 1];
            P[u].emplace_back(w, a | b);
        }
    for (int u : Q)
    {
        int v = u;
        for (int j = k; j--;)
            if (sz(P[v]) > j && P[v][j].second == A[u])
                v = P[v][j].first;
        cout << D[v] << '\n';
    }
}
