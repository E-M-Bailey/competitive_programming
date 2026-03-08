#include "template.hpp"

using namespace std;
using namespace abbrev;

int main()
{
	int n, m, i;
	cin >> n >> m;
	str s(n, '?'), t;
	while (m--)
	{
		cin >> i >> t;
		for (int j = --i; j < i + t.size(); ++j)
		{
			if (s[j] != '?' && s[j] != t[j - i])
			{
				cout << "Villa";
				return 0;
			}
			s[j] = t[j - i];
		}
	}
	cout << s;
}
