#include <bits/stdc++.h>

using namespace std;

int digit[127]{};

int parse(string::const_iterator first, string::const_iterator last)
{
	if (first == last)
		return -1;
	int base = 10;

	auto pfirst = first, plast = last;

	if (*prev(last) == '#')
	{
		--last;
		--plast;
		pfirst = last;
		while (pfirst != first && digit[(int)*prev(pfirst)] >= 0)
			--pfirst;
		if (first == pfirst || *prev(pfirst) != '#')
			return -1;

		base = parse(first, prev(pfirst));
		if (base < 2 || base > 16)
			return -1;
	}

	if (pfirst == plast)
		return -1;
	int ans = 0;
	for (; pfirst != plast; ++pfirst)
	{
		int cur = digit[(int)*pfirst];
		if (cur < 0 || cur >= base)
			return -1;
		ans = min(17, ans * base + cur);
	}
	return ans;
}

int main()
{
	fill(begin(digit), end(digit), -1);
	for (int i = 0; i < 10; i++)
		digit[i + '0'] = i;
	for (int i = 10; i < 16; i++)
		digit[i - 10 + 'a'] = i;

	cin.tie(0)->sync_with_stdio(0);

	string s;
	int n;
	cin >> n;
	getline(cin, s);
	while (n--)
	{
		getline(cin, s);
		cout << (parse(s.begin(), s.end()) >= 0 ? "yes\n" : "no\n");
	}
}
