#include "template.hpp"

using namespace std;
using namespace abbrev;

namespace
{
	constexpr ai32<7> N{ 0x1, 0x4, 0x8, 0x20, 0x80, 0x100, 0x400 };
	constexpr array<char const *, 12> D{ "A ", "A# ", "B ", "C ", "C# ", "D ", "D# ", "E ", "F ", "F# ", "G ", "G# " };
	constexpr int S = 0xab5 ^ 0xfff;
}

int main()
{
	int n, m = 0;
	cin >> n;
	str s;

	while (n--)
	{
		cin >> s;
		m |= N[s[0] - 'A'] << (s.size() - 1);
	}
	bool none = true;
	for (int i = 0; i < 12; ++i)
		if ((m & ((S << i) | (S >> (12 - i)))) == 0)
		{
			none = false;
			cout << D[i];
		}
	if (none)
		cout << "none";
}
