#include <bits/stdc++.h>
using namespace std;



int main()
{
	int n, q;
	cin >> n >> q;

	vector<int> ICC;
	vector<pair<pair<int, int>, int>> I(n);
	for (auto& [xy, h] : I)
	{
		auto& [x, y] = xy;
		cin >> x >> y >> h;
		ICC.push_back(x);
	}
	vector<pair<pair<int, int>, pair<int, int>>> QQ(q);
	for (auto& [p1, p2] : QQ)
	{
		cin >> p1.first >> p1.second >> p2.first >> p2.second;
		ICC.push_back(p1.first);
		ICC.push_back(p2.first);
	}
	sort(ICC.begin(), ICC.end());
	ICC.resize(unique(ICC.begin(), ICC.end()) - ICC.begin());
	int m = ICC.size();
	unordered_map<int, int> CC;
	CC.reserve(m);
	for (int i = 0; i < m; i++)
		CC.emplace(ICC[i], i);

	vector<vector<pair<int, int>>> T(2 * m);
	for (auto [xy, h] : I)
	{
		auto [x, y] = xy;
		T[CC[x] + m].emplace_back(y, h);
	}

	for (int i = m; i < 2 * m; i++)
		sort(T[i].begin(), T[i].end());

	for (int i = m - 1; i > 0; i--)
	{
		T[i].resize(T[i * 2].size() + T[i * 2 + 1].size());
		merge(T[i * 2].begin(), T[i * 2].end(), T[i * 2 + 1].begin(), T[i * 2 + 1].end(), T[i].begin());
	}

	//for (int i = 0; i < 2 * m; i++) {
	//	cerr << i << ':';
	//	for (auto [y, h] : T[i])
	//		cerr << ' ' << y << '_' << h;
	//	cerr << endl;
	//}

	using cit = vector<pair<int, int>>::const_iterator;
	const auto qry = [&](int i, int l, int r) -> pair<cit, cit>
	{
		//cerr << "query " << i << ' ' << l << ' ' << r;
		auto it1 = lower_bound(T[i].cbegin(), T[i].cend(), make_pair(l, INT_MIN));
		auto it2 = upper_bound(T[i].cbegin(), T[i].cend(), make_pair(r, INT_MAX));
		//cerr << ' ' << it1 - T[i].cbegin() << ' ' << it2 - T[i].cbegin() << endl;
		return make_pair(it1, it2);
	};

	vector<pair<cit, cit>> Q;
	vector<int> H;
	for (auto [p1, p2] : QQ)
	{
		Q.clear();
		H.clear();
		int x1 = CC[p1.first], x2 = CC[p2.first] + 1;
		int y1 = p1.second, y2 = p2.second;
		for (x1 += m, x2 += m; x1 < x2; x1 /= 2, x2 /= 2)
		{
			if (x1 % 2) Q.push_back(qry(x1++, y1, y2));
			if (x2 % 2) Q.push_back(qry(--x2, y1, y2));
		}
		int s = 0;
		for (auto [a, b] : Q)
			s += b - a;
		//cerr << s << " trees:" << endl;
		//for (auto [a, b] : Q)
		//{
		//	for (auto it = a; it != b; ++it)
		//		cerr << ' ' << it->second;
		//	cerr << endl;
		//}
		//cerr << endl;
		if (s > 50)
		{
			cout << "1\n";
			continue;
		}
		for (auto [a, b] : Q)
			for (auto it = a; it != b; ++it)
				H.push_back(it->second);
		sort(H.begin(), H.end());
		bool fnd = false;
		//cerr << s << endl;
		//for (int h : H)
		//	cerr << h << ' ';
		//cerr << endl;
		for (int i = 2; i < H.size(); i++)
			fnd |= H[i - 2] + H[i - 1] > H[i];
		cout << (fnd ? "1\n" : "0\n");
	}
	//cerr << endl;
}