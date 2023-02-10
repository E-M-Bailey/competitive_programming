#include <bits/stdc++.h>
using namespace std;
const long double PI = 4 * atanl(1);
int main(int argc, char* argv[]) {
    if (argc > 1) {
        freopen(argv[1], "r", stdin);
        freopen(argv[2], "w", stdout);
    }
    cout << fixed << setprecision(2);
    int n;
    vector<long double> P, Q, I;
    int tc = 0;
    long double xlo, xhi, inc;
    while (cin >> n) {
        P.resize(n + 1);
        for (auto& p : P)
            cin >> p;
        cin >> xlo >> xhi >> inc;
        Q.resize(2 * n + 1);
        for (int i = 0; i < 2 * n + 1; i++) {
            Q[i] = 0;
            for (int j = max(0, i - n); j <= min(i, n); j++)
                Q[i] += P[j] * P[i - j];
            Q[i] *= PI;
        }
        //for (long double q : Q)
        //    cerr << q << ' ';
        //cerr << endl;
        I.resize(2 * n + 2);
        I[0] = 0;
        for (int i = 1; i < 2 * n + 2; i++)
            I[i] = Q[i - 1] / i;
        const auto eval = [&](long double x) {
            long double ans = I.back();
            for (int i = 2 * n; i>= 0; i--)
                ans = ans * x + I[i];
            return ans;
        };
        I[0] = -eval(xlo);
        long double V = eval(xhi);
        cout << "Case " << ++tc << ": " << V << endl;
        int num = V > inc * 8 ? 8 : int(V / inc);
        if (num == 0) {
            cout << "insufficient volume" << endl;
            continue;
        }
        const auto findX = [&](long double v) {
            long double lo = xlo, hi = xhi;
            while (hi - lo > 1e-8) {
                long double mid = (hi + lo) / 2;
                if (eval(mid) < v)
                    lo = mid;
                else
                    hi = mid;
            }
            return (hi + lo) / 2;
        };
        for (int i = 1; i <= num; i++)
            cout << findX(inc * i) - xlo << ' ';
        cout << endl;
    }
}
