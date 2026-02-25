#include "template.hpp"

using namespace std;
using namespace abbrev;

int main()
{
	u32 m = 0;
	str s;
	cin >> s;
	for (char c : s)
		m |= 1u << (c - 'a');
	if (m == (1u << 26) - 1)
		cout << "Good job!";
	for (char c = 'a'; c <= 'z'; ++c)
		if (~m & (1u << (c - 'a')))
			cout << c;
}
