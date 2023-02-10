#include <bits/stdc++.h>
using namespace std;
int main() {
    int n, r, k;
    cin >> n >> r >> k;
    int st, a, b;
    if (k <= r) {
        st = r;
        a = 2 * k;
        b = 2 * (r - k);
    }
    else {
        st = 2 * k - r;
        a = 2 * r;
        b = 2 * (k - r);
    }
    a = 2;
    b = 2;
    int lim = 20000;//n + max(a, b) + 1;
    vector<bool> KP(lim, false);
    KP[st] = true;
    for (int i = st; i < lim; i++) {
        if (!KP[i]) continue;
        int j = i + a;
        if (j < lim)
            KP[j] = true;
        j = i + b;
        if (j < lim)
            KP[j] = true;
    }
    //cerr << a << ' ' << b << endl;
    //for (int i = 0; i < lim; i++)
    //    if (KP[i])
    //        cerr << i << endl;
    //    cerr << KP[i];
    //cerr << endl;
    for (int i = n; i < lim; i++) {
        if (KP[i]) {
            cout << i + r;
            return 0;
        }
    }
}
