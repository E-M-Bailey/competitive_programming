#include <bits/stdc++.h>

using namespace std;

#define ALL(C) begin(C), end(C)

void go();

int main(int argc, char const *argv[])
{
	if (argc > 1)
	{
		ignore = freopen(argv[1], "r", stdin);
		ignore = freopen(argv[2], "w", stdout);
	}

	int tc = 1;
	cin >> tc;
	while (tc--)
		go();
}

void go()
{
	string s;
	cin >> s;
	int n = (int)size(s);

	vector<int> ans;

	vector<int> re, ro;

	string t(1, s[0]);

	vector<pair<int, int>> R;
	{
		int st = 0;
		for (int i = 1; i < n; i++)
			if (s[i] != s[st])
			{
				if (i - st > 1)
					(size(R) % 2 ? ro : re).push_back((int)size(R));
				R.emplace_back(st, i);
				st = i;
				t += s[i];
			}
		if (n - st > 1)
			(size(R) % 2 ? ro : re).push_back((int)size(R));
		R.emplace_back(st, n);
	}
	int m = (int)size(t);

	if (m == 1)
	{
		cout << "NO\n";
		return;
	}

	int o = -1;
	for (int i = 0; i < m - 2; i += 2)
		if (t[i] != t[i + 2])
			o = i;

	int p = -1;
	for (int i = 0; i < m - 4; i += 2)
		if (t[i + 1] != t[i + 3])
			p = i;

	if (R.front().second - R.front().first != R.back().second - R.back().first || s.front() != s.back())
		ans.push_back(0);
	else if (m % 2 == 0)
	{
		for (int i = 0; i < m; i += 2)
			ans.push_back(R[i].first);
	}
	else if (!ro.empty())
	{
		int e	= ro.front();
		int pos = R[e].first;
		R[e].first++;
		R.insert(begin(R) + e, {pos, pos + 1});
		for (int i = 0; i <= m; i += 2)
			ans.push_back(R[i].first);
	}
	else if (!re.empty() && (size(re) >= 3 || re.front() != 0 || re.back() != m - 1))
	{
		int e = re.front() != 0 ? re.front() : re.back() != m - 1 ? re.back() : re[1];
		int a = R[e - 2].second - R[e - 2].first;
		int b = R[e + 2].second - R[e + 2].first;
		int c = R[e].second - R[e].first;
		int l = 0;
		while (l == a || c - l == b)
			l++;

		int pos = R[e].first;
		R[e].first += l;
		R.insert(begin(R) + e, {pos, pos + l});
		for (int i = 0; i <= e - 2; i += 2)
			ans.push_back(R[i].first);
		ans.push_back(R[e + 1].first);
		for (int i = e + 4; i <= m; i += 2)
			ans.push_back(R[i].first);
	}
	else if (o >= 0)
	{
		for (int i = 0; i <= o; i += 2)
			ans.push_back(R[i].first);
		for (int i = o + 3; i < m; i += 2)
			ans.push_back(R[i].first);
	}
	else if (p >= 0)
	{
		for (int i = 0; i <= p; i += 2)
			ans.push_back(R[i].first);
		for (int i = p + 5; i < m; i += 2)
			ans.push_back(R[i].first);
	}
	else if (m > 3 && R.front().second - R.front().first > 1)
	{
		ans.push_back(0);
		ans.push_back(R[2].first);
	}

	if (ans.empty())
		cout << "NO\n";
	else
	{
		cout << "YES\n";
		int k = (int)size(ans);
		cout << k << '\n';
		ans.push_back(n);
		for (int i = 0; i < k; i++)
			cout << s.substr(ans[i], ans[i + 1] - ans[i]) << ' ';
		cout << '\n';
	}
}
