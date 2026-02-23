#include "template.hpp"

using namespace std;
using namespace abbrev;

int main()
{
	str s;
	cin >> s;
	iz i = s.find('.');
	if (i == s.npos)
	{
		i = s.size();
		s.push_back('.');
	}
	s.resize(i + 5, '0');
	i32 a, b;
	from_chars(data(s), data(s) + i, a);
	from_chars(data(s) + i + 1, data(s) + size(s), b);
	a = 10000 * a + (a < 0 ? -b : b) - 3000;
	b = abs(a) % 10000;
	a /= 10000;
	cout << a;
	if (b)
	{
		cout << '.';
		s = to_string(b);
		s = str(4 - size(s), '0') + s;
		while (s.back() == '0')
			s.pop_back();
		cout << s;
	}
}
