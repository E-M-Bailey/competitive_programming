#include "template.hpp"

using namespace std;
using namespace abbrev;

int main()
{
	str s;
	cin >> s;
	cout << (stoi(s.substr(0, 2)) > 12 ? "EU" : stoi(s.substr(3, 2)) > 12 ? "US" : "either");
}
