#include "template.hpp"

using namespace std;
using namespace abbrev;

int main()
{
	int n, m;
	cin >> n >> m;
	cout << (n < m ? "Dufur passa" : n == m ? "Dufur passa fullkomlega" : "Dufur passa ekki");
}
