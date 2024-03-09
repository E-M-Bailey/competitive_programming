#include <bits/stdc++.h>

using namespace std;

int main()
{
	int t, c;
	cin >> t >> c;
	unordered_set<int> T;
	while (t--)
	{
		int x;
		cin >> x;
		T.insert(x);
	}
	string S;
	cin >> S;
	vector<int> P(c);
	for (int i = 0; i < c - 1; i++)
		P[i + 1] = P[i] + (S[i] == 'L' ? -1 : S[i] == 'F' ? 0 : 1);

	unordered_map<int, int> F;
	for (int i = 0; i < c; i++)
		if (S[i] == 'F' && T.find(P[i]) != T.end())
			++F[P[i]];

	int ans = (int)F.size();

	unordered_set<int> X[5], Y[5];
	for (int i = c; i-- > 0;)
	{
		//cerr << i << ' ' << P[i] << ' ' << S[i] << endl;

		int p = P[i];
		auto fit = F.find(P[i]);
		bool tgt = fit == F.end() && T.find(p) != T.end();
		bool add = S[i] == 'F' && fit != F.end() && --fit->second == 0;

		//for (auto [pf, ff] : F)
		//	cerr << pf << '_' << ff << ' ';
		//cerr << endl << ' ' << tgt << ' ' << add << endl;
		//for (int d = 0; d < 5; d++)
		//{
		//	for (int x : X[d])
		//		cerr << ' ' << x;
		//	cerr << " :";
		//	for (int y : Y[d])
		//		cerr << ' ' << y;
		//	cerr << endl;
		//}
		//cerr << ans << endl;

		if (add)
			F.erase(fit);

		if (S[i] == 'L')
		{
			//cerr << "  L " << (int)(F.size() + tgt + Y[3].size()) << ' ' << (int)(F.size() + Y[4].size()) << endl;
			// F
			ans = max(ans, (int)(F.size() + (tgt && Y[3].find(p) == Y[3].end()) + Y[3].size()));
			// R
			ans = max(ans, (int)(F.size() + Y[4].size()));
		}
		else if (S[i] == 'F')
		{
			//cerr << "  F " << (int)(F.size() + Y[1].size()) << ' ' << (int)(F.size() + Y[3].size()) << endl;
			// L
			ans = max(ans, (int)(F.size() + Y[1].size()));
			// R
			ans = max(ans, (int)(F.size() + Y[3].size()));
		}
		else // R
		{
			//cerr << "  R " << (int)(F.size() + Y[0].size()) << ' ' <<
			// L
			ans = max(ans, (int)(F.size() + Y[0].size()));
			// T
			ans = max(ans, (int)(F.size() + (tgt && Y[1].find(p) == Y[1].end()) + Y[1].size()));
		}

		//cerr << endl;

		for (int d = 0; d < 5; d++)
		{
			auto it = add ? X[d].find(p) : X[d].end();
			if (it != X[d].end())
				Y[d].insert(X[d].extract(it));
			int p2 = p + d - 2;
			if (S[i] == 'F' && T.find(p2) != T.end())
				(F.find(p2) == F.end() ? Y : X)[d].insert(p2);
		}
	}

	//for (int d = 0; d < 5; d++)
	//{
	//	for (int x : X[d])
	//		cerr << ' ' << x;
	//	cerr << " :";
	//	for (int y : Y[d])
	//		cerr << ' ' << y;
	//	cerr << endl;
	//}

	cout << ans;
}