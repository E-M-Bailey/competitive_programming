#include "template.hpp"

using namespace std;
using namespace abbrev;

int main()
{
	i32 n;
	cin >> n;
	for (i32 i = 1; i <= 12; ++i)
		cout << n * i << '\n';
}
