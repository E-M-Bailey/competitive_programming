#include "template.hpp"

using namespace std;
using namespace abbrev;

int main()
{
	int n;
	string ln;
	cin >> n;
	getline(cin, ln);
	while (n--)
	{
		u32 m = 0;
		getline(cin, ln);
		for (char c : ln)
		{
			c |= 32;
			if ('a' <= c && c <= 'z')
				m |= 1u << (c - 'a');
		}
		if (m == (1u << 26) - 1)
		{
			cout << "pangram\n";
			continue;
		}
		cout << "missing ";
		for (char c = 'a'; c <= 'z'; ++c)
			if (~m & (1u << (c - 'a')))
				cout << c;
		cout << '\n';
	}
}
