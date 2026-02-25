#include "template.hpp"

using namespace std;
using namespace abbrev;

int main()
{
	int n;
	cin >> n;
	while (n--)
	{
		int x;
		cin >> x;
		if (x < 48)
		{
			cout << "False";
			return 0;
		}
	}
	cout << "True";
}
