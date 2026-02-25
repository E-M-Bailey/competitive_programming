#include "template.hpp"

using namespace std;
using namespace abbrev;

int main()
{
	int n, p;
	cin >> n >> p;
	vvi32 P(p);
	for (auto &PP : P)
	{
		int k;
		cin >> k;
		PP.resize(k);
		for (auto &p : PP)
			cin >> p;
	}
	int m;
	cin >> m;
	while (m--)
	{
		int s, d, k;
		cin >> s >> d >> k;
		--s;
		--d;
		auto const rit = cend(P[s]), lit = rit - k;
		P[d].insert(cend(P[d]), lit, rit);
		P[s].erase(lit, rit);
	}
	for (auto const &PP : P)
	{
		for (auto p : PP)
			cout << p << ' ';
		cout << '\n';
	}
}
