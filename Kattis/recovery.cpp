#include <bits/stdc++.h>
using namespace std;
int main() {
    string rStr, cStr;
    cin >> rStr >> cStr;
    vector<bool> R, C;
    for (char r : rStr)
        R.push_back(r == '1');
    for (char c : cStr)
        C.push_back(c == '1');
    vector<bool> R2 = R, C2 = C;
    bool p = 0;
    for (bool r : R)
        p ^= r;
    for (bool c : C)
        p ^= c;
    if (p) {
        cout << -1;
        return 0;
    }
    if (C.size() % 2)
        for (int i = 0; i < R.size(); i++)
            R2[i] = !R2[i];
    if (R.size() % 2)
        for (int i = 0; i < C.size(); i++)
            C2[i] = !C2[i];
    vector<int> RR, CC;
    for (int i = 0; i < R.size(); i++)
        if (R2[i])
            RR.push_back(i);
    //reverse(RR.begin(), RR.end());
    for (int i = 0; i < C.size(); i++)
        if (C2[i])
            CC.push_back(i);
    //reverse(CC.begin(), CC.end());
    vector<pair<int, int>> Z;
    while (!CC.empty() && !RR.empty()) {
        int cc = CC.back(), rr = RR.back();
        CC.pop_back();
        RR.pop_back();
        Z.emplace_back(rr, cc);
    }
    while (!CC.empty()) {
        int cc = CC.back();
        CC.pop_back();
        Z.emplace_back(0, cc);
    }
    while (!RR.empty()) {
        int rr = RR.back();
        RR.pop_back();
        Z.emplace_back(rr, 0);
    }
    //for (auto [a, b] : Z)
    //    cerr << a << ' ' << b << endl;
    vector<vector<bool>> G(R.size(), vector<bool>(C.size(), true));
    for (auto [r, c] : Z)
        G[r][c] = false;
    for (int i = 0; i < G.size(); i++) {
        const vector<bool>& GG = G[i];
        if (i) cout << endl;
        for (bool g : GG)
            cout << g;
    }
}
