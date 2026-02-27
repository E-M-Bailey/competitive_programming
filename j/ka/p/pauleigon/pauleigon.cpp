#include "template.hpp"

using namespace std;
using namespace abbrev;

int main()
{
	int n, p, q;
	cin >> n >> p >> q;
	cout << ((p + q) % (2 * n) < n ? "paul" : "opponent");
}
