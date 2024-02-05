#include <bits/stdc++.h>

using namespace std;

int main()
{
	cin.tie(0);
	ios_base::sync_with_stdio(0);

	unordered_map<string, int> defs;
	vector<string>			   names(2001);
	string					   cmd, token;
	int						   val;
	while (cin >> cmd)
	{
		if (cmd[0] == 'd')
		{
			cin >> token >> val;
			auto [it, ins] = defs.emplace(token, val);
			if (!ins)
			{
				names[it->second + 1000].clear();
				it->second = val;
			}
			names[val + 1000] = move(token);
		}
		else if (cmd[1] == 'l')
		{
			while (!defs.empty())
			{
				auto it = defs.begin();
				names[it->second + 1000].clear();
				defs.erase(it);
			}
		}
		else
		{
			bool un = false;
			val		= 1000;
			for (char op = '+'; op != '='; cin >> op, cout << op << ' ')
			{
				cin >> token;
				cout << token << ' ';
				auto it = defs.find(token);
				if (it == defs.end())
					un = true;
				else if (op == '+')
					val += it->second;
				else
					val -= it->second;
			}
			un |= val < 0 || val > 2000 || names[val].empty();
			cout << (un ? "unknown" : names[val]) << '\n';
		}
	}
}
