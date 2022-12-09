#include <bits/stdc++.h>

using namespace std;
using ll = long long;
constexpr int iinf = 1e9 + 23;

int _main() {
    int n; cin >> n;
    vector<tuple<int, int, int>> rides(n);
    for (int i = 0; i<n; i++) {
        cin >> get<0>(rides[i]) >> get<1>(rides[i]) >> get<2>(rides[i]);
    }


    int q; cin >> q;
    vector<int> queries(q);
    for (int i = 0; i<q; i++) {
        cin >> queries[i];
    }


    vector<ll> dp(25001, 0);
    for(int i = 0; i < n; i++){
        auto [a, b, d] = rides[i];
        if(b == 0){
            for(int t = d; t <= 25000; t++){
                dp[t] = max(dp[t], a+dp[t-d]);
            }
        }
        else{
            int k = 1;
            int A = a - (k-1)*(k-1)*b;
            while(A > 0){
                for(int t = 25000; t >= d; t--){
                    dp[t] = max(dp[t], A+dp[t-d]);
                }
                k++;
                A = a - (k-1)*(k-1)*b;
            }
        }
    }
    for(int i = 1; i <= 25000; i++) dp[i] = max(dp[i], dp[i-1]);

    for(int i = 0; i < q; i++){
        cout << dp[queries[i]] << endl;
    }
    /*
    int max_time = *max_element(queries.begin(), queries.end());

    vector<vector<ll>> pref(n, vector<ll>(max_time + 1, 0));
    vector<vector<ll>> dp(max_time + 1, vector<ll>(n + 1, -iinf));

    for (int i = 0; i<n; i++) {
        for (int j = 1; j<=max_time; j++) {
            pref[i][j] = pref[i][j-1] + max(get<0>(rides[i]) - (j - 1) * (j-1) * get<1>(rides[i]), 0);
        }
    }

    for (int i = 0; i<=max_time; i++) {
        dp[i][0] = 0;
    }

    for (int i = 1; i<=n; i++) {
        dp[0][i] = 0;
    }

    for (int i = 1; i<=max_time; i++) {
        for (int j = 1; j<=n; j++) {
            dp[i][j] = max(dp[i][j], dp[i][j-1]);
            if (get<1>(rides[j-1]) == 0) {
                if (i - get<2>(rides[j-1]) >= 0) dp[i][j] = max(dp[i][j], dp[i - get<2>(rides[j-1])][j] + pref[j-1][1]);
                continue;
            }
            for (int k = 1; k<=max_time; k++) {
                if (pref[j-1][k] <= 0) break;
                auto rem = i - get<2>(rides[j-1]) * k;
                if (rem >= 0) dp[i][j] = max(dp[i][j], dp[rem][j - 1] + pref[j-1][k]);
            }
        }
    }


    for (auto x : queries) {
        cout << dp[x][n] << '\n';
    }
*/



    return 0;
}
