#include "template.hpp"

using namespace std;
using namespace abbrev;

int main()
{
	str s;
	cin >> s;
	int t = 0, h = 0;
	for (char c : s)
	{
		t += c == 'T';
		h += c == 'H';
		if (max(t, h) >= 11 && abs(t - h) >= 2)
			t = h = 0;
	}
	cout << t << '-' << h;
}
