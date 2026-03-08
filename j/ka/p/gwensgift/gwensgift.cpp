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
    int n;
    i64 k;
    cin >> n >> k;
    --k;    
    vector<int> R(n - 1);
    for (int i = 1; i < n; ++i)
        R[n - i - 1] = exchange(k, k / i) % i;
    vb S(n, true);
    S[0] = false;
    for (int r : R)
    {
        int i;
        for (i = 1;; ++i)
            if (S[i] && r-- == 0)
                break;
        rotate(begin(S), begin(S) + i, end(S));
        S[0] = false;
        cout << i << ' ';
    }
}
