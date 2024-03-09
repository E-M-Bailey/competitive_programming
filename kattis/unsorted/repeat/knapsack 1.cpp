#include <bits/stdc++.h>
using namespace std;

#pragma GCC optimize("O3,unroll-loops")
#pragma GCC target("avx2,bmi,bmi2,lzcnt,popcnt")

int C, n;
int W[2000], ans[2000];
int DP[2001][2001];

int main()
{
    while (cin >> C >> n)
    {
        fill_n(DP[0], C + 1, 0);
        for (int i = 0; i < n; ++i)
        {
            int v, w;
            cin >> v >> w;
            W[i] = w;
            copy_n(DP[i], min(w, C + 1), DP[i + 1]);
            for (int j = w; j <= C; ++j)
                DP[i + 1][j] = max(DP[i][j], DP[i][j - w] + v);
        }
        int j = max_element(DP[n], DP[n] + C + 1) - DP[n];
        int k = 0;
        while (n--)
            if (DP[n + 1][j] > DP[n][j])
            {
                ans[k++] = n;
                j -= W[n];
            }
        cout << k << '\n';
        while (k--)
            cout << ans[k] << ' ';
        cout << '\n';
    }
}