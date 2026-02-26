#include "template.hpp"

using namespace std;
using namespace abbrev;

int main()
{
	int n, k, d;
	cin >> n >> k;
	usi32 S;
	while (n--)
	{
		cin >> d;
		S.insert(d);
	}

	cout << min<int>(k, S.size());
}
