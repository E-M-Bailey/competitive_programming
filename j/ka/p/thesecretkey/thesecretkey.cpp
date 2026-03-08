#include "template.hpp"

using namespace std;
using namespace abbrev;

int main()
{
	int n;
	cin >> n;
	str s, t;
	t.reserve(n);
	for (int i = 0; i < n; ++i)
	{
		cin >> s;
		t.push_back(s[i] ^ 1);
	}
	cout << t;
}
