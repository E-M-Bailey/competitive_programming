#include "template.hpp"

using namespace std;
using namespace abbrev;

int main()
{
	int n, m, x, l = 0, r = 0;
	cin >> n >> m;
	while (n--)
	{
		cin >> x;
		l += x;
	}
	while (m--)
	{
		cin >> x;
		r += x;
	}
	cout << (l < r ? "left" : l == r ? "either" : "right");
}
