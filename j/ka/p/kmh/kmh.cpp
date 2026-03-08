#include "template.hpp"

using namespace std;
using namespace abbrev;

int main()
{
	int n, d = 0, x;
	cin >> n;
	str s;
	while (n--)
	{
		cin >> s;
		if (s == "/")
			cout << d << '\n';
		else
		{
			cout << s << '\n';
			x = stoi(s);
			d = max(d, x + 10 - x % 10);
		}
	}
}
