#include "template.hpp"

using namespace std;
using namespace abbrev;

int main()
{
	int n;
	cin >> n;
	str s;
	int k = 0;
	while (n--)
	{
		int a;
		cin >> s >> s >> a;
		k += (s == "IN" ? a : -a);
	}
	if (k)
		cout << k;
	else
		cout << "NO STRAGGLERS";
}
