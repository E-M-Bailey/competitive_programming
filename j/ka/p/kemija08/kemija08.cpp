#include "template.hpp"

using namespace std;
using namespace abbrev;

int main()
{
	str s, t;
	getline(cin, s);
	t.reserve(s.size());
	for (int i = 0; i < s.size();)
	{
		t.push_back(s[i]);
		i += s[i] >= 'a' && ((1 << (s[i] - 'a')) & 0x104111) ? 3 : 1;
	}
	cout << t;
}
