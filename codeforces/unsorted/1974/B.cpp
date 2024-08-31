#include <bits/stdc++.h>

using namespace std;

void go();

int main()
{
	cin.tie(0)->sync_with_stdio(0);
	int tc = 1;
	cin >> tc;
	while (tc--)
		go();
}

void go()
{
	int n;
	string s;
	cin >> n >> s;
	string t = s;
	sort(begin(t), end(t));
	t.erase(unique(begin(t), end(t)), end(t));
	int m = (int)size(t);
	for (char &c : s)
	{
		int i = int(lower_bound(begin(t), end(t), c) - begin(t));
		c = t[m - 1 - i];
	}
	cout << s << '\n';
}
