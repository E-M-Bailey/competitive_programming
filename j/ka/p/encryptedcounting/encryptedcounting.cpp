#include "template.hpp"

using namespace std;
using namespace abbrev;

int main()
{
	str s, t, u;
	cin >> s >> t;
	int k = 0;
	while (s != t)
	{
		++k;
		u.clear();
		for (int i = 0; i < size(t); i += 2)
			u.resize(u.size() + t[i] - '0', t[i + 1]);
		u.swap(t);
	}
	cout << k;
}
