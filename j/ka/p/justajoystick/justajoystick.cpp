#include "template.hpp"

using namespace std;
using namespace abbrev;

int main()
{
	int n, k = 0;
	// int pos = 0;
	str s, t;
	cin >> n >> s >> t;
	for (int i = 0; i < n; ++i)
	{
		if (s[i] == t[i])
			continue;
		// k += i - exchange(pos, i);
		int d = abs(s[i] - t[i]);
		k += min(d, 26 - d);
	}
	cout << k;
}
