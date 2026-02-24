#include "template.hpp"

using namespace std;
using namespace abbrev;

int main()
{
	int k, s;
	cin >> k >> s;
	cout << s / k + s % k;
}
