#include "template.hpp"

using namespace std;
using namespace abbrev;

int main()
{
	int n;
	cin >> n;
	usstr S;
	str s;
	while (n--)
	{
		int m;
		cin >> m;
		bool fnd = false;
		while (m--)
		{
			cin >> s;
			if (fnd)
				continue;
			auto [it, ins] = S.insert(std::move(s));
			if (ins)
			{
				fnd = true;
				cout << *it << ' ';
			}
		}
	}
}
