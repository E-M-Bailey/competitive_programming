#include "template.hpp"

using namespace std;
using namespace abbrev;

int main()
{
	int n, w, s = 0;
	cin >> n;
	while (n--)
	{
		cin >> w;
		s += w;
	}
	cout << s;
}
