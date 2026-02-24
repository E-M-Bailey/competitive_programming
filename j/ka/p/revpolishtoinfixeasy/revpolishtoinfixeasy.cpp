#include "template.hpp"

using namespace std;
using namespace abbrev;

int main()
{
	vstr S;
	str s;
	while (cin >> s)
	{
		if (s == "+" || s == "-" || s == "*" || s == "/")
		{
			auto b = std::move(S.back());
			S.pop_back();
			S.back() = '(' + S.back() + s + b + ')';
		}
		else
			S.push_back(s);
	}
	cout << S[0];
}
