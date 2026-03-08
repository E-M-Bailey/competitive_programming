#include "template.hpp"

using namespace std;
using namespace abbrev;

int main()
{
	int p, n;
	cin >> p >> n;
	usstr S;
	str s;
	for (int i = 1; i <= n; ++i)
	{
		cin >> s;
		S.insert(s);
		if (S.size() == p)
		{
			cout << i;
			return 0;
		}
	}
	cout << "paradox avoided";
}
