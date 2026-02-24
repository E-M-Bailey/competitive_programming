#include "template.hpp"

using namespace std;
using namespace abbrev;

int main()
{
	int a, b, c;
	cin >> a >> b >> c;
	cout << max(b - a, c - b) - 1;
}
