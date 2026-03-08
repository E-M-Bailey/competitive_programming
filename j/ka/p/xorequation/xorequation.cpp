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
int ps(pair<str, vi32> const &P)
{
    return sz(P.second);
}
bool incr(int &n, vi32 &I, vi32 const &P)
{
    for (int i = 0; i < sz(I); ++i)
    {
        if (++I[i] < 10) [[likely]]
        {
            n += P[i];
            return true;
        }
        I[i] = 0;
        n -= 9 * P[i];
    }
    return false;
}
}

int main()
{
    array<pair<str, vi32>, 3> S;
    cin >> S[0].first >> S[1].first >> S[1].first >> S[2].first >> S[2].first;
    for (auto &[s, P] : S)
        for (int i = sz(s), p = 1; i--; p *= 10)
            if (s[i] == '?')
                P.push_back(p);
    rng::sort(S, {}, ps);
    auto &[s0, P0] = S[0];
    auto &[s1, P1] = S[1];
    for (char &c : s0)
        if (c == '?')
            c = '0';
    for (char &c : s1)
        if (c == '?')
            c = '0';
    auto const &s2 = S[2].first;
    vi32 I0(sz(P0)), I1(sz(P1));
    int n = stoi(s0), m = stoi(s1), k = 0;
    do
    {
        if (sz(to_string(n)) != sz(s0))
            continue;
        do
        {
            if (sz(to_string(m)) != sz(s1))
                continue;
            str s = to_string(n ^ m);
            bool c = sz(s) == sz(s2);
            for (int i = 0; c && i < sz(s); ++i)
                c = s2[i] == s[i] || s2[i] == '?';
            k += c;
        }
        while (incr(m, I1, P1));
    }
    while (incr(n, I0, P0));
    cout << k;  
}
