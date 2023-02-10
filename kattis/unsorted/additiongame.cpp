#include <bits/stdc++.h>

using namespace std;
using ll = long long;

int main() {
    int n; cin >> n;
    vector<int> a(n);
    for (int i = 0; i<n; i++) {
        cin >> a[i];
    }

    int total = accumulate(a.begin(), a.end(), 0);
    if (total % n != 0) {
        cout << "impossible" << '\n';
        return 0;
    }

    unordered_set<int> rpi, rsigma;
    for (int i = 1; i<=n; i++) {
        rpi.insert(i);
        rsigma.insert(i);
    }
    vector<int> pi(n), sigma(n);

    for (int i = 0; i<n; i++) {
        bool found = false;
        for (int j = 1; j<=n; j++) {
            if (rpi.find(j) == rpi.end()) continue;
            int k = ((a[i] % n) - j + 100 * n) % n;
            if (k == 0) k = n;
            if (rsigma.find(k) != rsigma.end()) {
                pi[i] = j;
                sigma[i] = k;
                found = true;
                rpi.erase(j);
                rsigma.erase(k);
                break;
            }
        }
        if (!found) {
            cout << "impossible" << '\n';
            return 0;
        }
    }

    for (int i = 0; i<n; i++) {
        cout << pi[i] << " ";
    }
    cout << '\n';
    for (int i = 0; i<n; i++) {
        cout << sigma[i] << " ";
    }
    cout << '\n';
}
