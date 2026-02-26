#include "template.hpp"

using namespace std;
using namespace abbrev;

int main()
{
	double w, h;
	cin >> w >> h;
	cout << fixed << setprecision(8) << w + h - hypot(w, h);
}
