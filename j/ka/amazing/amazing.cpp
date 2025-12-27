#include <bits/stdc++.h>

using namespace std;

string const		 NAME[4]{"right", "down", "left", "up"};
pair<int, int> const DIR[4]{{0, 1}, {1, 0}, {0, -1}, {-1, 0}};

int ci = 0, cj = 0;

unordered_map<int, unordered_set<int>> V;

bool vis(int d)
{
	auto [di, dj] = DIR[d];
	int	 i2		  = ci + di;
	int	 j2		  = cj + dj;
	auto it		  = V.find(i2);
	return it != V.end() && it->second.find(j2) != it->second.end();
}

bool move(int d)
{
	static string res;
	cout << NAME[d] << '\n' << flush;
	cin >> res;
	if (res == "wall")
		return false;
	else if (res == "ok")
	{
		auto [di, dj] = DIR[d];
		ci += di;
		cj += dj;
		return true;
	}
	else
		exit(0);
}

void dfs()
{
	V[ci].insert(cj);
	for (int d = 0; d < 4; d++)
		if (!vis(d) && move(d))
		{
			dfs();
			move(d ^ 2);
		}
}

int main()
{
	cin.tie(0)->sync_with_stdio(0);
	dfs();
	cout << "no way out";
}
