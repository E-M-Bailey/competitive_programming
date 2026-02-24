#include "template.hpp"

using namespace std;
using namespace abbrev;

int main()
{
	str ln;
	getline(cin, ln);
	getline(cin, ln);
	for (char &c : ln)
		c = c < 'a' ? c : "qwertyuiopasdfghjklzxcvbnm"[c - 'a'];
	cout << ln;
}
