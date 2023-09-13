#include <bits/stdc++.h>

using namespace std;

unordered_map<string, int> ID;
vector<int> T;
int id()
{
	string s;
	cin >> s;
	bool inv = s[0] == '!';
	if (inv)
		s.erase(begin(s));
	int i = ID.try_emplace(move(s), (int)ID.size()).first->second;
	T.resize(ID.size(), -1);
	return inv ? ~i : i;
}

int main()
{
	cin.tie(0)->sync_with_stdio(0);

	vector<int> S;

	int n;
	cin >> n;

	for (int i = 0; i < n; i++)
	{
		char c;
		cin >> c;
		if (c == 'E')
		{
			int x = id();
			T[x] = (int)S.size();
			S.push_back(x);
		}
		else if (c == 'D')
		{
			int r;
			cin >> r;
			while (r--)
			{
				T[S.back()] = -1;
				S.pop_back();
			}
		}
		else
		{
			int k;
			cin >> k;

			int lo = 0, hi = (int)S.size() + 1;
			for (int j = 0; j < k; j++)
			{
				int x = id();
				if (x >= 0)
					hi = min(hi, T[x] < 0 ? -1 : (int)S.size() - T[x]);
				else
					lo = max(lo, T[~x] < 0 ? -1 : (int)S.size() - T[~x]);
			}
			if (lo >= hi)
				cout << "Plot Error\n";
			else if (lo == 0)
				cout << "Yes\n";
			else
				cout << lo << " Just A Dream\n";
		}
	}
}