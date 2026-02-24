#include "template.hpp"

using namespace std;
using namespace literals;
namespace rng = ranges;
namespace vws = views;
using namespace abbrev;

static const str S[]
{
	"Skrimsli - Venjulegt",
	"Skrimsli - Ahrifa",
	"Skrimsli - Bodunar",
	"Skrimsli - Samruna",
	"Skrimsli - Samstillt",
	"Skrimsli - Thaeo",
	"Skrimsli - Penduls",
	"Skrimsli - Tengis",
	"Galdur - Venjulegur",
	"Galdur - Bunadar",
	"Galdur - Svida",
	"Galdur - Samfelldur",
	"Galdur - Bodunar",
	"Galdur - Hradur",
	"Gildra - Venjuleg",
	"Gildra - Samfelld",
	"Gildra - Mot",
	"Annad",
};

int main()
{
	int n;
	cin >> n;
	vector<astr<4>> A(n);
	str ln;
	getline(cin, ln);
	for (auto &[a, b, c, d] : A)
	{
		getline(cin, ln);
		auto i = ln.find(','), j = ln.find(',', i + 1), k = ln.find(',', j + 1);
		a = ln.substr(0, i);
		b = ln.substr(i + 2, j - i - 2);
		c = {1, static_cast<char>('A' + rng::find(S, ln.substr(j + 2, k - j - 2)) - S) };
		d = ln.substr(k + 2);
	}
	str s;
	ac<4> C;
	for (char &c : C)
	{
		cin >> s;
		c = s[0];
	}
	for (auto c : C | vws::reverse)
		rng::stable_sort(A, {}, [i = "nifd"s.find(c)](astr<4> const &a) { return a[i]; });
	for (auto const &[a, b, c, d] : A)
		cout << a << '\n';
}
