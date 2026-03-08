#include "template.hpp"

namespace
{
using namespace std;
namespace rng = ranges;
using namespace abbrev;
template<typename C>
[[nodiscard]] constexpr int sz(C const &c) noexcept
{
    return static_cast<int>(size(c));
}
}

int main()
{
    cin.tie(0)->sync_with_stdio(0);
    aac<25, 81> G;
    str s;
    int n;
    getline(cin >> n, s);
    for (auto &GG : G)
        GG.fill(' ');
    for (int i = 0; i < n; ++i)
    {
        getline(cin, s);
        memcpy(G[i].data(), s.data(), sz(s));
    }
    int i = 0, j = 0, di = 0, dj = 1;
    vi32 S;
    auto const peek = [&]()
    {
        return S.empty() ? 0 : S.back();
    };
    auto const pop = [&]()
    {
        if (S.empty())
            return 0;
        int b = S.back();
        S.pop_back();
        return b;
    };
    auto const push = [&](int x, int k = 1)
    {
        if ((x != 0 || !S.empty()) && k > 0)
            S.insert(S.end(), k, x);
    };
    const auto get = [&](int i, int j) -> char &
    {
        if ((i %= 25) < 0)
            i += 25;
        if ((j %= 80) < 0)
            j += 80;
        return G[i][j];
    };
    s.clear();
    for (;;)
    {
        int a, b;
        char g = get(i, j);
        switch (g)
        {
        case '0':
        case '1':
        case '2':
        case '3':
        case '4':
        case '5':
        case '6':
        case '7':
        case '8':
        case '9':
            push(g - '0');
            break;
        case '+':
        case '-':
        case '*':
        case '/':
        case '%':
        case '`':
        case 'g':
            a = pop();
            [[fallthrough]];
        case '!':
            b = pop();
            push(
                g == '+' ? b + a :
                g == '-' ? b - a :
                g == '*' ? b * a :
                g == '/' ? b / a :
                g == '%' ? b % a :
                g == '`' ? b > a :
                g == 'g' ? get(a, b) :
                !b);
            break;
        case ':':
        case '$':
            push(pop(), g == ':' ? 2 : 0);
            break;
        case '\\':
            a = pop();
            b = pop();
            push(a);
            push(b);
            break;
        case '_':
        case '|':
            g = "<>^v"[2 * (g == '|') + !pop()];
            [[fallthrough]];
        case '<':
        case '>':
        case '^':
        case 'v':
            di = g == '^' ? -1 : g == 'v' ? 1 : 0;
            dj = g == '<' ? -1 : g == '>' ? 1 : 0;
            break;
        case 'p':
            a = pop();
            b = pop();
            get(a, b) = pop();
            break;
        case '.':
        case ',':
            a = pop();
            s += g == ',' ? str{ (char)a } : to_string(a) + ' ';
            break;
        case '"':
            while ((g = get(i += di, j += dj)) != '"')
                push(g);
            break;
        case '#':
            i += di;
            j += dj;
            break;
        case '@':
            cout << s;
            return 0;
        case ' ':
            break;
        default:
            return -1;
        }
        i += di;
        j += dj;
    }
}
