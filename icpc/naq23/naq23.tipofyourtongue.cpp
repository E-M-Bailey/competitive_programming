#include <bits/stdc++.h>

using namespace std;

int main()
{
	cin.tie(0)->sync_with_stdio(0);
	int n, q;
	cin >> n >> q;
	vector<string> dict(n);
	for (auto &str : dict)
		cin >> str;
	while ((dict.size() & (dict.size() - 1)))
		dict.push_back("$");
	n = (int)dict.size();
	sort(begin(dict), end(dict));

	vector<vector<string>> mst;
	mst.push_back(dict);
	for (string &s : mst.back())
		reverse(begin(s), end(s));
	for (int p2 = 2; p2 <= n; p2 *= 2)
	{
		mst.push_back(mst.back());
		for (int st = 0; st < n; st += p2)
			inplace_merge(mst.back().begin() + st, mst.back().begin() + st + p2 / 2, mst.back().begin() + st + p2);
	}

	auto const cnt_seg = [&](int i, string const &suf)
	{
		int l = i, r = i + 1;
		int lvl = 0;
		while (l < n)
		{
			l *= 2, r *= 2;
			lvl++;
		}
		l -= n;
		r -= n;
		
		int ls = lower_bound(begin(mst[lvl]) + l, begin(mst[lvl]) + r, suf) - (begin(mst[lvl]) + l);
		int rs = lower_bound(begin(mst[lvl]) + l, begin(mst[lvl]) + r, suf + char('z' + 1)) - (begin(mst[lvl]) + l);
		return rs - ls;
	};

	auto const cnt = [&](int l, int r, string const &suf)
	{
		int ans = 0;
		for (l += n, r += n; l < r; l /= 2, r /= 2)
		{
			if (l % 2)
				ans += cnt_seg(l++, suf);
			if (r % 2)
				ans += cnt_seg(--r, suf);
		}
		return ans;
	};

	while (q--)
	{
		string cmd, pre, suf;
		cin >> cmd >> pre >> suf;
		reverse(begin(suf), end(suf));
		int lp = lower_bound(begin(dict), end(dict), pre) - begin(dict);
		int rp = lower_bound(begin(dict), end(dict), pre + char('z' + 1)) - begin(dict);
		if (cmd == "AND")
			cout << cnt(lp, rp, suf) << '\n';
		else if (cmd == "OR")
			cout << cnt(0, lp, suf) + cnt(rp, n, suf) + (rp - lp) << '\n';
		else
			cout << rp - lp - cnt(lp, rp, suf) + cnt(0, lp, suf) + cnt(rp, n, suf) << '\n';
	}
}