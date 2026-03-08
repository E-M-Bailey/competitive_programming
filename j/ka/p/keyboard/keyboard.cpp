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
    static constexpr int A = 'Z' + 1;
    cin.tie(0)->sync_with_stdio(0);
    int n, m;
    cin >> n >> m;
    int N = n * m;
    avi32<A> I;
    str s, t;
    s.reserve(N);
    t.reserve(10001);
    for (int i = 0; i < n; ++i)
    {
        cin >> t;
        s += t;
    }
    for (int i = 0; i < N; ++i)
        I[s[i]].push_back(i);
    I[0] = { 0 };
    vector<ai32<4>> G(N, { -1, -1, -1, -1 });
    for (int i = 0; i < n; ++i)
        for (int j = 0; j < m; ++j)
        {
            int idx = i * m + j;
            int mask = 0;
            for (int d = 1; (mask |= ((i - d < 0) << 0) | ((j - d < 0) << 1) | ((j + d >= m) << 2) | ((i + d >= n) << 3)) != 0xf; ++d)
            {
                if ((mask & 0x1) == 0 && s[idx] != s[idx - d * m])
                {
                    G[idx][0] = idx - d * m;
                    mask |= 0x1;
                }
                if ((mask & 0x2) == 0 && s[idx] != s[idx - d])
                {
                    G[idx][1] = idx - d;
                    mask |= 0x2;
                }
                if ((mask & 0x4) == 0 && s[idx] != s[idx + d])
                {
                    G[idx][2] = idx + d;
                    mask |= 0x4;
                }
                if ((mask & 0x8) == 0 && s[idx] != s[idx + d * m])
                {
                    G[idx][3] = idx + d * m;
                    mask |= 0x8;
                }
            }
        }
    cin >> t;
    t += '*';
    int K = sz(t), M = N * K;
    vector<ai32<5>> H(M);
    for (int i = 0; i < K; ++i)
    {
        char c = t[i];
        for (int j = 0; j < N; ++j)
        {
            int idx = i * N + j;
            ai32<4> &GG = G[j];
            ai32<5> &HH = H[idx];
            for (int k = 0; k < 4; ++k)
                HH[k] = GG[k] < 0 ? -1 : i * N + GG[k];
            HH[4] = i == K - 1 || s[j] != c ? -1 : idx + N;
        }
    }
    
    queue<int> Q;
    vi32 D(M, INT_MAX / 2);
    D[0] = 1;
    Q.push(0);
    for (int d = 2; !Q.empty(); ++d)
    {
        for (int s = sz(Q); s--;)
        {
            int j = Q.front();
            Q.pop();
            for (int k : H[j])
                if (k >= 0 && D[k] == INT_MAX / 2)
                {
                    D[k] = d;
                    Q.push(k);
                }
        }
    }
    int r = INT_MAX / 2;
    for (int i : I['*'])
        r = min(r, D[M - N + i]);
    cout << r << '\n';
}
