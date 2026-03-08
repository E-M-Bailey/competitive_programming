#include "template.hpp"

using namespace std;
using namespace abbrev;

int main()
{
	cin.tie(0)->sync_with_stdio(0);
	int T;
	cin >> T;
	str s;
	while (T--)
	{
		cin >> s;
		int n = (int)round(sqrt(s.size()));
		for (int i = 0; i * 2 < n; ++i)
			for (int j = 0; j * 2 + 1 < n; ++j)
			{
				char tmp = s[i * n + j];
				s[i * n + j] = s[j * n + n - 1 - i];
				s[j * n + n - 1 - i] = s[(n - 1 - i) * n + n - 1 - j];
				s[(n - 1 - i) * n + n - 1 - j] = s[(n - 1 - j) * n + i];
				s[(n - 1 - j) * n + i] = tmp;
			}
		cout << s << '\n';
	}
}
