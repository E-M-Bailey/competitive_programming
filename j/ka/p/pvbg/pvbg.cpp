#include "template.hpp"

using namespace std;
using namespace abbrev;

int main()
{
	int n, m = INT_MAX, x;
	cin >> n;
	while (n--)
	{
		cin >> x;
		m = min(m, x);
	}
	cout << m + 1;
}
