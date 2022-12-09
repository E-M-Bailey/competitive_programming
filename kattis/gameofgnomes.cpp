#include <bits/stdc++.h>
using namespace std;
typedef int64_t i64;
// includes n
i64 tri(i64 n) {
    return n * (n + 1) / 2;
}
i64 hitK(i64 n, i64 k, i64 amt) {
    return n * amt - k * tri(amt - 1);
}
i64 spread(i64 n, i64 m, i64 k) {
    i64 lo = n / m, hi = lo + 1;
    i64 hc = n % m, lc = m - hc;
    return hi * tri(hc) + lo * (lc * hc + tri(lc));
}
int main() {
    i64 n, m, k;
    cin >> n >> m >> k;
    i64 extra = 0;
    if (n > (k - 1) * m) {
        i64 amt = (n - (k - 1) * (m - 1)) / k;
        //cerr << amt << endl;
        extra = hitK(n, k, amt);
        n -= amt * k;
    }
    i64 ans = 0;
    for (i64 i = 0; i * k <= n; i++) {
        ans = max(ans, hitK(n, k, i) + spread(n - k * i, m, k));
    }
    cout << ans + extra;
    //cerr << extra << ' ' << n << endl;

}
