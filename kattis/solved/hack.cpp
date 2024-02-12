#include <bits/stdc++.h>

using namespace std;

vector<string> path(int k)
{
	if (k == 0)
		return {""};
	auto		   rec = path(k - 1);
	vector<string> ans;
	ans.reserve(10 * size(rec));
	for (char c : {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9'})
	{
		for (string const &s : rec)
			ans.push_back(s + c);
		reverse(begin(rec), end(rec));
	}
	return ans;
}

vector<string> cycle(int k)
{
	vector<string> rec = path(k - 1);
	rec.erase(begin(rec));
	vector<string> ans;
	ans.reserve(10 * size(rec));
	for (char c : {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9'})
	{
		for (string const &s : rec)
			ans.push_back(s + c);
		reverse(begin(rec), end(rec));
	}
	for (char c : {'9', '8', '7', '6', '5', '4', '3', '2', '1', '0'})
		ans.push_back(string(k - 1, '0') + c);
	return ans;
}

int main()
{
	cin.tie(0)->sync_with_stdio(0);
	string N;
	while (cin >> N, N != "-1")
	{
		vector<string> ans;
		int			   n = stoi(N), k = (int)size(N);
		if (k == 1)
		{
			if (n <= 4)
			{
				while (n > 0)
					ans.push_back(to_string(n--));
				while (n <= 9)
					ans.push_back(to_string(n++));
			}
			else
			{
				while (n < 9)
					ans.push_back(to_string(n++));
				while (n >= 0)
					ans.push_back(to_string(n--));
			}
		}
		else
		{
			ans = cycle(k);
			rotate(begin(ans), find(begin(ans), end(ans), N), end(ans));
		}
		ans.erase(begin(ans));
		cout << size(ans) << '\n';
		for (auto const &x : ans)
			cout << x << ' ';
		cout << '\n';
	}
}
