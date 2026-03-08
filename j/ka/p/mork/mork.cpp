#include "template.hpp"

using namespace std;
using namespace abbrev;

int main()
{
	int n, m;
	cin >> n >> m;
	cout << (n == m && (n == 0 || n == 2) ? "Jebb" : "Neibb");
}
