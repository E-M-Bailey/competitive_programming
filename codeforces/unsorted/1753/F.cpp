#include <bits/stdc++.h>

using namespace std;

int main()
{
	cin.tie(0)->sync_with_stdio(0);
	int n, m, k, t;
	cin >> n >> m >> k >> t;
	bool sw = n > m;
	if (sw)
		swap(n, m);

	vector<vector<vector<int>>> P(n, vector<vector<int>>(m));
	for (int i = 0; i < k; i++)
	{
		int x, y, w;
		cin >> x >> y >> w;
		if (sw)
			swap(x, y);
		x--;
		y--;
		P[x][y].push_back(w);
	}

	int			t2 = (t + 1023) / 1024;
	vector<int> EP, EN;
	vector<int> P1(t), N1(t);
	vector<int> P2(t2), N2(t2);

	auto const add = [&](int w)
	{
		if (abs(w) > t)
			return;
		(w > 0 ? EP : EN).push_back(abs(w) - 1);
		if ((w > 0 ? P1 : N1)[abs(w) - 1]++ == 0)
			(w > 0 ? P2 : N2)[(abs(w) - 1) / 1024]++;
	};
	auto const del = [&](int w)
	{
		if (abs(w) > t)
			return;
		if ((w > 0 ? P1 : N1)[abs(w) - 1]-- == 1)
			(w > 0 ? P2 : N2)[(abs(w) - 1) / 1024]--;
	};
	auto const enough = [&]()
	{
		int ep = 0, en = 0;

		while (ep < t2 && P2[ep] == 1024)
			ep++;
		while (en < t2 && N2[en] == 1024)
			en++;

		ep *= 1024;
		en *= 1024;
		while (ep < t && P1[ep])
			ep++;
		while (en < t && N1[en])
			en++;
		return ep + en + 1 >= t;
	};

	// map<int, int> fr, iv;

	// auto const add = [&](int w)
	// {
	// 	if (++fr[w] == 1)
	// 	{
	// 		auto it = iv.upper_bound(w);
	// 		it		= it == begin(iv) ? end(iv) : prev(it);
	// 		if (it == end(iv) || it->second < w)
	// 			it = iv.emplace(w, w + 1).first;
	// 		else if (it->second == w)
	// 			it->second = w + 1;
	// 		auto jt = next(it);
	// 		if (jt != end(iv) && it->second == jt->first)
	// 		{
	// 			it->second = jt->second;
	// 			iv.erase(jt);
	// 		}
	// 	}
	// };
	// auto const del = [&](int w)
	// {
	// 	if (--fr[w] == 0)
	// 	{
	// 		auto it = prev(iv.upper_bound(w));
	// 		if (it->first == w)
	// 		{
	// 			if (it->second == w + 1)
	// 				iv.erase(it);
	// 			else
	// 			{
	// 				iv.emplace(w + 1, it->second);
	// 				iv.erase(it);
	// 			}
	// 		}
	// 		else
	// 		{
	// 			if (it->second == w + 1)
	// 				it->second--;
	// 			else
	// 			{
	// 				iv.emplace(it->first, w);
	// 				iv.emplace(w + 1, it->second);
	// 				iv.erase(it);
	// 			}
	// 		}
	// 	}
	// };
	// auto const enough = [&]()
	// {
	// 	int	 ans = 1;
	// 	auto it	 = iv.upper_bound(0);
	// 	if (it != end(iv) && it->first == 1)
	// 		ans += it->second - it->first;
	// 	it = it == begin(iv) ? end(iv) : prev(it);
	// 	if (it != end(iv) && it->second == 0)
	// 		ans += it->second - it->first;
	// 	return ans >= t;
	// };

	long long ans = 0;
	for (int i = 0; i < n + m - 1; i++)
	{
		int d  = i - (n - 1);
		int st = i < n - 1 ? n - 1 - i : 0;
		int ed = i < m - 1 ? n : n + m - 1 - i;

		for (int j : EP)
			P1[j] = P2[j / 1024] = 0;
		EP.clear();
		for (int j : EN)
			N1[j] = N2[j / 1024] = 0;
		EN.clear();

		for (int l = st, r = st; r <= ed;)
		{
			if (enough() && l < r)
			{
				ans += ed - r + 1;
				for (int x = l; x < r; x++)
					for (auto w : P[x][l + d])
						del(w);
				for (int x = l + 1; x < r; x++)
					for (auto w : P[l][x + d])
						del(w);
				l++;
			}
			else if (r < ed)
			{
				for (int x = l; x <= r; x++)
					for (auto w : P[x][r + d])
						add(w);
				for (int x = l; x < r; x++)
					for (auto w : P[r][x + d])
						add(w);
				r++;
			}
			else
				break;
		}
	}
	cout << ans;
}
