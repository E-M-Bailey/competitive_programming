#include <bits/stdc++.h>

using namespace std;

int main() {
    int n;
    cin >> n;
    vector<int64_t> A(n);
    for (int i = 1; i < n; i++)
        cin >> A[i];

    int64_t needed = 1;
    long double ans = 0;
    for (int i = 1; i < n; i++) {
        ans += needed * pow(2, -(0.25l + i * 0.5l));
        needed = 2 * needed - A[i];
        if (needed <= 0)
            break;
    }
    if (needed > 0)
        cout << "impossible";
    else
        cout << fixed << setprecision(6) << ans;
}
