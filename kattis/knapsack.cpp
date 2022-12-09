#include <bits/stdc++.h>
using namespace std;

/*
    vector<int> Vs, Ws;
    vector<vector<int>> DP;
    int val(int m, int w) {
        if (m == 0) return 0;
        if (DP[m][w] >= 0) return DP[m][w];
        if (Ws[m-1] > w) return DP[m][w] = val(m - 1, w);
        DP[m][w] = max(val(m - 1, w),
                       Vs[m - 1] + val(m - 1, w - Ws[m - 1]));
        return DP[m][w];
    }*/

/*int kp(int n, int W) {
    DP.assign(n + 1, vector<int>(W + 1, -1));
    int ans = 0;
    for (int w = 0; w <= W; w++)
        ans = max(ans, val(n, w));
    return ans;
}*/
/*vector<int> Vs, Ws;
int kp(int n, int W) {
    vector<vector<int>> DP(n + 1, vector<int>(W + 1, -1));
    for (int w = 0; w <= W; w++)
        DP[0][w] = 0;
    for (int m = 1; m <= n)
}*/
    /*vector<int> Vs, Ws;
    int val(int m, int w) {
        if (m == 0) return 0;
        if (Ws[m - 1] > w) return val(m - 1, w);
        return max(val(m - 1, w),
                   Vs[m - 1] + val(m - 1, w - Ws[m - 1]));
    }*/

    vector<int> Vs, Ws;
    int val(int n, int W) {
        vector<int> DP(W + 1, 0);
        for (int m = 1; m <= n; m++)
            for (int w = W; w >= Ws[m - 1]; w--)
                DP[w] = max(DP[w],
                            Vs[m - 1] + DP[w - Ws[m - 1]]);
        return DP[W];
    }
int main() {
    int W, n;
    while (cin >> W >> n) {
        Vs.resize(n);
        Ws.resize(n);
        for (int i = 0; i < n; i++)
            cin >> Vs[i] >> Ws[i];
        //DP.assign(n + 1, vector<int>(W + 1, -1));
        cout << val(n, W) << endl;
    }
}
