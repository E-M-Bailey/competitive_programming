#include <bits/stdc++.h>
using namespace std;
vector<int> submasks(int a) {
	vector<int> ans(1 << __builtin_popcount(a));
	int n = 1;
	while (a) {
		int i = __builtin_ctz(a);
		int m = 1 << i;
		copy(ans.begin(), ans.begin() + n, ans.begin() + n);
		for (int i = 0; i < n; i++)
			ans[i] |= m;
		n *= 2;
		a -= m;
	}
	return ans;
}
int main() {
	string line;
	int tc = 0;
	while (cin >> line) {
		cout << "Case " << ++tc << ": ";
		vector<string> input;
		while (line[0] != '0') {
			input.push_back(line);
			cin >> line;
		}
		vector<int> KICC, RICC;
		for (string ln : input)
			for (char c : ln)
				(c >= 'a' ? RICC : KICC).push_back((c | 32) - 'a');
		sort(KICC.begin(), KICC.end());
		KICC.resize(unique(KICC.begin(), KICC.end()) - KICC.begin());
		sort(RICC.begin(), RICC.end());
		RICC.resize(unique(RICC.begin(), RICC.end()) - RICC.begin());
		array<int, 26> KCC, RCC;
		int n = KICC.size(), m = RICC.size();
		fill(KCC.begin(), KCC.end(), -1);
		for (int i = 0; i < n; i++)
			KCC[KICC[i]] = i;
		fill(RCC.begin(), RCC.end(), -1);
		for (int i = 0; i < m; i++)
			RCC[RICC[i]] = i;
		int ak = 0, zk = 0;
		for (int i = 0; i < n; i++)
			(KICC[i] < 13 ? ak : zk) |= 1 << i;
		if (ak == 0 || zk == 0) {
			cout << 0 << ' ' << n + m - 1 - input.size() << endl;
			continue;
		}
		if (m < 2) {
			cout << "impossible" << endl;
			continue;
		}
		vector<int> RR(m), RK(m), KR(n);
		for (string ln : input) {
			char a = ln[0], b = ln[1];
			if (a > b)
				swap(a, b);
			int i = (a | 32) - 'a', j = (b | 32) - 'a';
			if (a >= 'a') {
				RR[i] |= 1 << j;
				RR[j] |= 1 << i;
			} else {
				KR[i] |= 1 << j;
				RK[j] |= 1 << i;
			}
		}
		int azr = 0, ar = 0, zr = 0, er = 0;
		for (int i = 0; i < m; i++) {
            bool a = RK[i] & ak, z = RK[i] & zk;
            a ? z ? azr : ar : z ? zr : er |= 1 << i;
		}
		int bestK = INT_MAX, bestR = INT_MAX;
		const auto cmp = [=, &bestK, &bestR](int ca, int cz, int ce) {
		    int mk;
			int Q = 0;
			mk = ce;
			while (mk) {
                int i = __builtin_ctz(mk);
                int mi = 1 << i;
                if (RR[i] & ca)
			}

			int fk = 0;
			int s = input.size();
			if (!ca || !cz)
				return;
            mk = ca;
			while (mk) {
				int i = __builtin_ctz(mk);
				fk |= zk & RK[i];
				mk -= 1 << i;
			}
			mk = cz;
			while (mk) {
				int i = __builtin_ctz(mk);
				fk |= ak & RK[i];
				mk -= 1 << i;
			}
			int curK = 2 * __builtin_popcount(fk);
			if (curK > bestK)
				return;
			if (curK < bestK)
				bestR = INT_MAX;
			bestK = curK;
			int delR = 0;
			mk = ca;

			while (mk) {
				int i = __builtin_ctz(mk);
				int amt = __builtin_popcount(RR[i] & cz);
				delR += amt;
				s -= amt;
				mk -= 1 << i;
			}
			bestR = min(bestR, delR + n + m - 2 - s);
		};
		for (int sm : submasks(azr)) {

		}
		if (bestK == INT_MAX)
			cout << "impossible" << endl;
		else
			cout << bestK * 2 << ' ' << bestR << endl;
	}
}
