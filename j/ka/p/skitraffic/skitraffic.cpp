#include "template.hpp"

using namespace std;
using namespace abbrev;

int main()
{
	str n, hm, d;
	bool b, r, h;
	getline(cin, n) >> hm >> d >> b >> r >> h;
	auto i = hm.find(':');
	int t = (stoi(hm.substr(0, i)) * 60 + stoi(hm.substr(i + 1))) * ((d[0] == 's') + 1) * (b + 1) * (r * 2 + 1) * (h * 2 + 1);
	cout << t / 60 << ':' << t % 60 / 10 << t % 10;
}
