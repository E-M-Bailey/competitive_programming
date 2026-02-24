#include "template.hpp"

using namespace std;
using namespace abbrev;

int main()
{
	int n, k;
	cin >> n >> k;
	while (n--)
	{
		int a;
		cin >> a;
		bool w = a <= k;
		k -= w * a;
		cout << w;
	}
}
