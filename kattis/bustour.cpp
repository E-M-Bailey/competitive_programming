#include <bits/stdc++.h>
using namespace std;

int n, m;
vector<vector<int64_t>> G;
constexpr int64_t MAX = numeric_limits<int64_t>::max();

int64_t f(int s, int t, int S, vector<vector<int64_t>>& DP) {
	int64_t& dp = DP[s][S];
	if (dp < MAX)
		return dp;
	if (S == 0)
		return dp = G[s][t];
	for (int i = 0; i < n; i++) {
		int mask = 1 << i;
		if (mask & ~S)
			continue;
		dp = min(dp, f(i, t, S ^ mask, DP) + G[s][i]);
	}
	return dp;
}

/*vector<vector<int>> distances(int dest) {
    int mask = 1 << n;
    DP.assign(n, vector<int>(mask, INT_MAX));
    for (int i = 0; i < n; i++)

    //for (int i = 0; i < n; i++)
        //for (int j = 0; j < mask; j++)
            //f()

    return move(DP);
}*/

int main(int argc, char* argv[]) {
	//cerr << MAX;
	if (argc > 1) {
		freopen(argv[1], "r", stdin);
		freopen(argv[2], "w", stdout);
	}
	int tc = 0;
	while (cin >> n >> m) {
		G.assign(n, vector<int64_t>(n, INT_MAX));
		for (int i = 0; i < m; i++) {
			int u, v, t;
			cin >> u >> v >> t;
			G[u][v] = t;
			G[v][u] = t;
		}
		for (int i = 0; i < n; i++)
			G[i][i] = 0;
		for (int k = 0; k < n; k++)
			for (int i = 0; i < n; i++)
				for (int j = 0; j < n; j++)
					G[i][j] = min(G[i][j], G[i][k] + G[k][j]);
		/*for (int i = 0; i < n; i++) {
		    for (int j = 0; j < n; j++)
		        cerr << G[i][j] << ' ';
		    cerr << endl;
		}*/
		int N = 1 << n;
		vector<vector<int64_t>> DPa(n, vector(N, MAX));
		vector<vector<int64_t>> DPb(n, vector(N, MAX));
		int64_t ans = MAX;
		int hmask = N / 2 - 2;
		for (int mask = 0; mask < N / 2; mask += 2) {
			if (__builtin_popcount(mask) != n / 2 - 1)
				continue;
			/*else if (n % 2) {
				for (int a = 1; a < n - 1; a++) {
					int cur = 1 << a;
					if (cur & mask )
						continue;
					int ma = mask, mb = hmask ^ mask ^ cur;
					int64_t A = f(a, 0, ma, DPa);
					int64_t D = f(a, n - 1, mb, DPb);
					int64_t C = f(a, n - 1, ma, DPb);
					int64_t B = f(a, 0, mb, DPa);
					int64_t cans = A + B + C + D;
					if (cans < ans) {
						cerr << a << ' ' << A << ' ' << B << ' ' << C << ' ' << D << '=' << cans << endl;
						cerr << hex << cur << ' ' << mask << ' ' << ma << ' ' << mb << dec << endl;
					}
					ans = min(ans, cans);
				}
			}*/
			for (int a = 1; a < n - 1; a++) {
				for (int b = 1; b < n - 1; b++) {
					int curA = 1 << a, curB = 1 << b;
					if ((curA | curB) & mask)
						continue;
					int maa = hmask ^ mask ^ curA, mab = hmask ^ mask ^ curB, mb = mask;
					int64_t A = f(a, 0, maa, DPa);
					int64_t D = f(a, n - 1, mb, DPb);
					int64_t C = f(b, n - 1, mab, DPb);
					int64_t B = f(b, 0, mb, DPa);
					int64_t cans = A + B + C + D;
					/*if (cans < ans) {
						cerr << a << ' ' << A << ' ' << B << ' ' << C << ' ' << D << '=' << cans << endl;
						cerr << hex << cur << ' ' << mask << ' ' << ma << ' ' << mb << dec << endl;
					}*/
					ans = min(ans, cans);
				}
			}
		}
		cout << "Case " << ++tc << ": " << ans << endl;
	}

}
