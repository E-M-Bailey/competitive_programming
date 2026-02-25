#include "template.hpp"

using namespace std;
using namespace abbrev;

int main()
{
	int n, k = 0;
	cin >> n;
	str s;
	while (n--)
	{
		cin >> s;
		k += (s.size() == 12 || s.size() == 13) && s.substr(0, 3) == "+39";
	}
	cout << k;
}
