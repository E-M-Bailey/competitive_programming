#include "template.hpp"

using namespace std;
using namespace abbrev;

int main()
{
	double d, w, n;
	cin >> d >> w >> n;
	cout << (d * 314159 >= w * n * 100000 ? "YES" : "NO");
}
