#include <bits/stdc++.h>

using namespace std;

void go();

int main(int argc, char const *argv[])
{
	if (argc > 1)
	{
		ignore = freopen(argv[1], "r", stdin);
		ignore = freopen(argv[2], "w", stdout);
	}

	cin.tie(0)->sync_with_stdio(0);
	int t = 1;
	cin >> t;
	while (t--)
	{
		go();
	}
}

bool match(char x, char y)
{
	return x == '?' || y == '?' || x == y;
}

void go()
{
	string s;
	cin >> s;
	int n = (int)size(s);

	deque<bool> B;

	int ans = 0;
	for (int l = 1; l * 2 <= n; l++)
	{
		B.resize(l);
		B[0] = false;
		for (int i = 0; i < l - 1; i++)
			B[i + 1] = match(s[i], s[i + l]);

		int cnt = accumulate(begin(B), end(B), 0);
		for (int i = l - 1; i + l < n; i++)
		{
			cnt -= B.front();
			B.pop_front();
			B.push_back(match(s[i], s[i + l]));
			cnt += B.back();
			if (cnt == l)
			{
				ans = l;
				break;
			}
		}
	}
	cout << ans * 2 << '\n';
}
