#include "template.hpp"

using namespace std;
using namespace abbrev;

int main()
{
	string s;
	cin >> s;
	s[s.find('d')] = ' ';
	s[s.find('+')] = ' ';
	istringstream iss(s);
	double a, b, c;
	iss >> a >> b >> c;
	cout << a * (b + 1) / 2 + c;
}
