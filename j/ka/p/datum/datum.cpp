#include "template.hpp"

using namespace std;
using namespace abbrev;

namespace
{
constexpr astr<7> W{ "Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday" };
constexpr ai32<12> M{ 4, 0, 0, 3, 5, 1, 3, 6, 2, 4, 0, 2 };
}

int main()
{
	int d, m;
	cin >> d >> m;
	cout << W[(M[m - 1] + d - 1) % 7];
}
