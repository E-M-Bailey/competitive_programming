#include <bits/stdc++.h>

using namespace std;

int main()
{
	int n;
	string s;
	array<int, 1440> P;
	while (cin >> n, n)
	{
		fill(begin(P), end(P), -8);
		for (int i = 0; i < n; i++)
		{
			int p;
			cin >> p >> s;
			auto sz = size(s);
			s[sz - 3] = s[sz - 2];
			s[sz - 2] = s[sz - 1];
			s.pop_back();
			P[p] += stoi(s);
		}
		array<int, 1441> S;
		S[0] = 0;
		partial_sum(begin(P), end(P), 1 + begin(S));
		int bestL = 0, bestR = 0, bestS = 0;
		for (int l = 0; l < 1440; l++) for (int r = l + 1; r <= 1440; r++)
		{
			int s = S[r] - S[l];
			if (make_tuple(s, -(r - l), -l) > make_tuple(bestS, -(bestR - bestL), -bestL))
				tie(bestL, bestR, bestS) = make_tuple(l, r, s);
		}
		if (bestS == 0)
		{
			cout << "no profit\n";
			continue;
		}
		cout << bestS / 100 << '.' << bestS % 100 / 10 << bestS % 10 << ' ' << bestL << ' ' << bestR - 1 << endl;
	}
}