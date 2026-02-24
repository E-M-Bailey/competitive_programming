#include "template.hpp"

using namespace std;
using namespace abbrev;

int main()
{
	int n;
	str s;
	cin >> n >> s;
	vc S;
	bool ok = true;
	for (char c : s)
	{
		if (c == '(' || c == '[' || c == '{')
		{
			S.push_back(c);
			continue;
		}
		if (S.empty())
		{
			ok = false;
			break;
		}
		if (c == ')')
			ok = S.back() == '(';
		if (c == ']')
			ok = S.back() == '[';
		if (c == '}')
			ok = S.back() == '{';
		S.pop_back();
		if (!ok)
			break;
	}
	cout << (ok && S.empty() ? "Valid" : "Invalid");
}
