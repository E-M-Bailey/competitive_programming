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

	int tc = 1;
	cin >> tc;
	while (tc--)
		go();
}

vector<long long> solve(int n, string const &s)
{
	vector<long long> ans(n);

	deque<pair<int, long long>> SL, PR;
	long long					ll = 0, rr = 0;
	for (int i = 0; i < n; i++)
		if (s[i] == '<')
		{
			long long ps = PR.empty() ? 0 : PR.back().second;
			PR.emplace_back(i, ps + i);
		}

	for (int i = 0; i < n; i++)
	{
		if (s[i] == '<')
		{
			PR.pop_front();
			rr -= i;
			if (size(SL) <= size(PR))
			{
				int j = (int)size(SL) - 1;

				long long ss = j < 0 ? 0 : SL[size(SL) - 1 - j].second + ll;
				long long ps = j < 0 ? 0 : PR[j].second + rr;

				ans[i] = 2 * ps + i - 2 * ss + 1;
			}
			else
			{
				int j = (int)size(PR) - 1;

				long long ss = SL[size(SL) - 2 - j].second + ll;
				long long ps = j < 0 ? 0 : PR[j].second + rr;

				ans[i] = 2 * ps + i + n - 2 * ss;
			}
		}

		if (s[i] == '>')
		{
			SL.emplace_back(i, -ll);
			ll += i;
		}
	}
	return ans;
}

void go()
{
	int n;
	cin >> n;
	string s;
	cin >> s;

	auto ans1 = solve(n, s);
	reverse(begin(s), end(s));
	for (auto &c : s)
		c = c == '<' ? '>' : '<';
	auto ans2 = solve(n, s);
	reverse(begin(ans2), end(ans2));
	for (int i = 0; i < n; i++)
		cout << ans1[i] + ans2[i] << ' ';
	cout << '\n';
}
