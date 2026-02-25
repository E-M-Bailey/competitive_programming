#include "template.hpp"

using namespace std;
using namespace abbrev;

int main()
{
	double s, d, t;
	cin >> s >> d >> t;
	cout << (s * t * 22 > d * 15 ? "MADE IT" : "FAILED TEST");
}
