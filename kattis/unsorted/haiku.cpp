#include <bits/stdc++.h>
using namespace std;
int main(int argc, char* argv[]) {
    if (argc > 1) {
        freopen(argv[1], "r", stdin);
        freopen(argv[2], "w", stdout);
    }
    int n;
    cin >> n;
    unordered_set<string> S;
    while (n--) {
        string s;
        cin >> s;
        S.insert(move(s));
    }
    n = S.size();
    const auto eval = [&](const string& L) {
        int m = L.size();
        vector<int> DP(m + 1);
        DP[0] = 1;
        for (int i = 0; i < m; i++) {
            int dp = DP[i];
            if (L[i] == ' ') {
                DP[i + 1] = dp;
                continue;
            }
            dp = dp << 1;
            for (const string& s : S) {
                int j = s.size() + i;
                if (j <= m && L.substr(i, s.size()) == s)
                    DP[j] |= dp;
            }
        }
        //for (int d : DP)
        //    cerr << d << ' ';
        //cerr << endl;
        return DP[m];
    };
    string L1, L2, L3;
    getline(cin, L1);
    getline(cin, L1);
    getline(cin, L2);
    getline(cin, L3);
    int e1 = eval(L1), e2 = eval(L2), e3 = eval(L3);
    //cerr << e1 << ' ' << e2 << ' ' << e3 << endl;
    bool ans = (e1 & 0x20) && (e2 & 0x80) && (e3 & 0x20);
    cout << (ans ? "haiku" : "come back next year");
}
