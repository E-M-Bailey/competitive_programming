#include <bits/stdc++.h>

using namespace std;

constexpr int MAXN = 1e5 + 10;

int main() {
    int n,m,k,t;
    cin >> n >> m >> k >> t;
    vector<int> s(n);
    for (int i = 0; i<n; i++) {
        cin >> s[i];
    }

    vector<int> d(m);
    for (int i = 0; i<m; i++) {
        cin >> d[i];
    }

    vector<vector<bool>> dp(MAXN, vector<bool>(m + 1, false));
    dp[0][0] = true;
    for (int j = 1; j<=m; j++) {
        for (int i = 0; i < MAXN; i++) {
            dp[i][j] = dp[i][j-1];
            if (i >= d[j-1]) {
                dp[i][j] = dp[i][j] || dp[i-d[j-1]][j-1];
            }
        }
    }

    vector<int> pref(MAXN);
    pref[0] = int(dp[0][m]);
    for (int i = 1; i<MAXN; i++) {
        pref[i] = pref[i-1] + dp[i][m];
    }

    vector<int> poss;
    for(int i = 1; i <= 100000; i++) if(dp[i][m]) poss.push_back(i);

    for(int i = 0; i < n; i++){
        s[i] = t/s[i];
        if(poss[0] > s[i]) s[i] = 0;
        else{
            int b = 0;
            int e = poss.size();
            while(e-b > 1){
                int mid = (b+e)/2;
                if(poss[mid] <= s[i]) b = mid;
                else e = mid;
            }
            s[i] = poss[b];
        }
        //cout << s[i] << endl;
    }

    int mx = 0;
    for(int i = 0; i < n; i++){
        mx = max(mx, s[i]);
    }
    int P = 0;
    for(int i = 0; i < n; i++){
        if(s[i] == mx) P++;
    }
    cout << max(P, k) << endl;



    /*vector<int> pos(n);
    iota(pos.begin(), pos.end(), 0);
    sort(pos.begin(), pos.end(), [&](auto x, auto y) { return s[x] < s[y]; });

    while (int(pos.size()) >= k) {
        pos.pop_back();
    }

    sort(pos.begin(), pos.end());
    pos.push_back(n-1);
    pos.insert(pos.begin(),-1);

    int ret = 0;

    for (int i = 0; i<int(pos.size())-1; i++) {
        int lbound = pos[i] + 1, rbound = pos[i+1];

        vector<int> possible;
        unordered_map<int, int> cnt;

        for (int j = lbound; j <= rbound; j++) {
            possible.push_back(t / s[j]);
            cnt[possible.back()]++;
        }
        sort(possible.begin(), possible.end());
        possible.erase(unique(possible.begin(), possible.end()), possible.end());
        reverse(possible.begin(), possible.end());

        if (possible.size() == 1) {
            ret++;
            continue;
        }
        int total = 0;
        for (int i = 0; i<int(possible.size())-1; i++) {
            total += cnt[possible[i]];
            int lb = possible[i], rb = possible[i+1];
            if (lb < rb) {
                continue;
            }
            int ok = pref[lb] - pref[rb];
            if (ok) {
                ret += total;
                break;
            }
        }

    }

    cout << ret << '\n';*/


}
