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
		k += s == "he" || s == "him" || s == "she" || s == "her";
	}
	cout << k;
}
