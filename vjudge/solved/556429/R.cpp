#include <bits/stdc++.h>

using namespace std;

int main(int argc, char const *argv[])
{
	if (argc > 2)
	{
		ignore = freopen(argv[1], "r", stdin);
		ignore = freopen(argv[2], "w", stdout);
	}

	int n;
	cin >> n;
	vector<string> S(n);
	for (string &s : S)
		cin >> s;

	int i;
	const auto cmp =
		[
			&i,
			M = *max_element(begin(S), end(S), [&](string const &l, string const &r) { return l.size() < r.size(); })
		](string const &l, string const &r)
	{
		char a = (int)l.size() < i ? (char)CHAR_MIN : l[i] == M[i] ? (char)CHAR_MAX : l[i];
		char b = (int)r.size() < i ? (char)CHAR_MIN : r[i] == M[i] ? (char)CHAR_MAX : r[i];
		return a < b;
	};
	for (i = 19; i >= 0; i--)
		stable_sort(begin(S), end(S), cmp);

	vector<char> ans;
	string cur;
	for (string const &s : S)
	{
		size_t len = 0;
		while (len < cur.size() && len < s.size() && cur[len] == s[len])
			len++;
		while (cur.size() > len)
		{
			ans.push_back('-');
			cur.pop_back();
		}
		while (cur.size() < s.size())
		{
			char c = s[cur.size()];
			cur.push_back(c);
			ans.push_back(c);
		}
		ans.push_back('P');
	}
	cout << ans.size();
	for (char c : ans)
		cout << '\n' << c;
}