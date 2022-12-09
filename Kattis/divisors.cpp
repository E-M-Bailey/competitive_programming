#include <bits/stdc++.h>
using namespace std;

int main() {
    vector<int> LP(432);
    for (int i = 2; i <= 431; i++) {
        if (LP[i]) continue;
        for (int j = i; j <= 431; j += i)
            if (!LP[j])
                LP[j] = i;
    }
    
    const auto pf = [&](int x) {
        vector<int> ans;
        while (x > 1) {
            ans.push_back(LP[x]);
            x /= LP[x];
        }
        return ans;
    };
    
    unordered_map<int, int> F;
    int n, k;
    while (cin >> n >> k) {
        F.clear();
        while (k > 0) {
            for (int p : pf(n))
                F[p]++;
            for (int p : pf(k))
                F[p]--;
            n--;
            k--;
        }
        int64_t ans = 1;
        for (auto [f, c] : F)
            ans *= (c + 1);
        cout << ans << endl;
    }
}