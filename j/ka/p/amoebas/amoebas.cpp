#include "template.hpp"

using namespace std;
using namespace abbrev;

int main()
{
	int n, m;
	cin >> n >> m;
	vstr G(n);
	for (str &GG : G)
		cin >> GG;
	int k = 0;
	for (int i = 0; i < n; ++i)
		for (int j = 0; j < m; ++j)
		{
			if (G[i][j] == '.')
				continue;
			int i2 = i, j2 = j;
			++k;
			for (;;)
			{
				G[i2][j2] = '.';
				bool found = false;
				for (int i3 = max(i2 - 1, 0); !found && i3 < min(i2 + 2, n); ++i3)
					for (int j3 = max(j2 - 1, 0); !found && j3 < min(j2 + 2, m); ++j3)
						if (G[i3][j3] == '#')
						{
							i2 = i3;
							j2 = j3;
							found = true;
						}
				if (!found)
					break;
			}
		}
	cout << k;
}
