#include <bits/stdc++.h>

using namespace std;

char const A = 'z' + 1;

string after(string const &s, string const &t)
{
	int	   i = 0, j = 0, bj = -1, bk = -1;
	string u;
	while (i < s.size() && j < t.size())
	{
		if (s[i] == t[j])
		{
			if (!u.empty() && u.back() == 'a' && t[j] == 'a')
			{
				bj = j + 1;
				bk = u.size() - 1;
			}
			u.push_back(t[j]);
			i++;
			j++;
		}
		else if (j + 1 < t.size() && s[i] == A && t[j] == 'a' && t[j + 1] == 'a')
		{
			if (!u.empty() && u.back() == 'a')
			{
				bj = j + 1;
				bk = u.size() - 1;
			}
			u.push_back(A);
			i++;
			j += 2;
		}
		else
			break;
	}
	if (j < t.size() && !u.empty() && u.back() == 'a' && t[j] == 'a')
	{
		bj = j + 1;
		bk = u.size() - 1;
	}
	if (i == s.size() || (j < t.size() && s[i] < t[j]))
		u += t.substr(j);
	else if (j + 1 < t.size() && t[j] == 'a' && t[j + 1] == 'a')
		u += A + t.substr(j + 2);
	else if (j == t.size() || s[i] > t[j])
	{
		if (bj >= 0)
			u = u.substr(0, bk) + A + t.substr(bj);
		else
			u.clear();
	}
	return u;
}

int main()
{
	int n;
	cin >> n;
	vector<string> T(n);
	for (string &t : T)
	{
		cin >> t;
	}
	string s;
	for (string const &t : T)
	{
		s = after(s, t);
		if (s.empty())
		{
			cout << "no";
			return 0;
		}
	}
	cout << "yes";
}
