#include "template.hpp"

using namespace std;
using namespace abbrev;

int main()
{
	int n, m;
	cin >> n >> m;
	vstr G(n);
	for (str &g : G)
		cin >> g;
	str s(max(n, m), 'z'), t;
	for (int i = 0; i < n; ++i)
	{
		for (int j = 0; j < m; ++j)
		{
			if (G[i][j] == '#')
				continue;
			t.push_back(G[i][j]);
			if (j + 1 == m || G[i][j + 1] == '#')
			{
				if (t.size() >= 2)
					s = min(s, t);
				t.clear();
			}
		}
	}
	for (int j = 0; j < m; ++j)
	{
		for (int i = 0; i < n; ++i)
		{
			if (G[i][j] == '#')
				continue;
			t.push_back(G[i][j]);
			if (i + 1 == n || G[i + 1][j] == '#')
			{
				if (t.size() >= 2)
					s = min(s, t);
				t.clear();
			}
		}
	}
	cout << s;
}
