#include <bits/stdc++.h>
using namespace std;
//typedef __int128 lll;

vector<int64_t> F(27);
vector<string> FW(27);

/*string subfw(int n, lll lo, lll hi) {
	lo = max((lll)0, lo);
	hi = min((lll)F[n], hi);
	if (lo >= hi)
		return "";
	if (n <= 25)
		return FW[n].substr((int)lo, (int)(hi - lo));
	return subfw(n - 1, lo, hi) + subfw(n - 2, lo - F[n - 1], hi - F[n - 1]);
}*/
int64_t ct(const string& S, const string& P) {
    if (P.size() >= S.size())
        return P == S;
    const auto pi = [&](const string& s) {
        vector<int> p(s.size());
        for (int i = 1; i < s.size(); i++) {
            int g = p[i - 1];
            while (g && s[i] != s[g]) g = p[g - 1];
            p[i] = g + (s[i] == s[g]);
        }
        return p;
    };
    vector<int> p = pi(P + '$' + S);
    int ans = 0;
    for (int i = p.size() - S.size(); i < p.size(); i++)
        if (p[i] == P.size()) ans++;
    return ans;
}

int main(int argc, char* argv[]) {
	if (argc > 1) {
		freopen(argv[1], "r", stdin);
		freopen(argv[2], "w", stdout);
	}
	int tc = 0;
	F[0] = F[1] = 1;
	for (int i = 2; i <= 26; i++)
		F[i] = F[i - 1] + F[i - 2];
	FW[0] = "0";
	FW[1] = "1";
	for (int i = 2; i <= 26; i++)
		FW[i] = FW[i - 1] + FW[i - 2];
	int n;
	string P;
	while (cin >> n >> P) {
		int m = P.size();
		vector<int64_t> DP(n + 1);
		for (int i = 0; i <= min(n, 26); i++)
            DP[i] = ct(FW[i], P);
        int64_t ec = ct(FW[25].substr(F[25] - m + 1) + FW[25].substr(0, m - 1), P);
        int64_t oc = ct(FW[26].substr(F[26] - m + 1) + FW[25].substr(0, m - 1), P);
        for (int i = 27; i <= n; i++)
            //cerr << DP[i - 1] << ' ' << DP[i - 2] << ' ' << (n % 2 ? oc << ec) << endl;
            DP[i] = DP[i - 1] + DP[i - 2] + (i % 2 ? oc : ec);
        cout << "Case " << ++tc << ": " << DP[n] << endl;
	}
}
