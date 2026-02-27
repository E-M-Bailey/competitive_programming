#include "template.hpp"

using namespace std;
using namespace abbrev;

int main()
{
	double r;
	cin >> r;
	r *= r;
	cout << fixed << setprecision(7) << 4 * atan(1) * r << '\n' << 2 * r;
}
